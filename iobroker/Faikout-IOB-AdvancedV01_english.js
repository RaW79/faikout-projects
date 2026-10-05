/***************************************************
 * DAIKIN Alias Control V01 — Suitable for Transitional Seasons
 * ==================================================
 *
 * PURPOSE
 * Higher-level control for a Daikin unit via the Faikout module
 * (ioBroker aliases). The Faikout runs in thermostat mode and
 * makes the switching decision itself (heats at autot - autor,
 * stops at autot + autor). This script only provides the
 * setpoints and limits the output:
 *   - Target temperature (autot) by schedule
 *   - Hysteresis (autor, here DEADBAND)
 *   - Maximum output (demand) based on outdoor temperature and
 *     setpoint/actual deviation
 * Additionally: weekly schedule, comfort functions and respect
 * for manual overrides. Active only in heating mode ("H"),
 * pauses in any other mode (warning in log).
 *
 * FLOW
 * A timer calls checkSchedule() every minute:
 *   1. Detect manual override of setpoint/demand
 *   2. Evaluate schedule triggers (start/end Standard and Luxury)
 *   3. Execute running control (schedule or manual operation)
 *
 * SCHEDULE
 * Two phases per weekday (0 = Sunday):
 *   - Standard operation: setpoint SETPOINT_STANDARD
 *   - Luxury operation:   setpoint SETPOINT_LUXUS
 * At phase start, the unit is switched on, comfort functions
 * activated, setpoint applied and all overrides reset. The end
 * of the Standard phase does not switch off — Luxury follows.
 * The unit is only switched off at the end of Luxury.
 * ENABLE_STANDARD and ENABLE_LUXUS toggle each phase individually.
 *
 * DEMAND CONTROL (maximum output in %)
 *   1. Base from outdoor temperature curve demandCurve
 *      (linearly interpolated, constant outside the data points).
 *      The warmer it is outside, the lower the base, down to
 *      DEMAND_MIN at the end of the curve.
 *   2. Adjustment by diff = setpoint - actual:
 *      - diff <= 0 (setpoint reached/exceeded):
 *          base - DEMAND_REDUCE (not below DEMAND_MIN),
 *          any active auto-swing is ended
 *      - 0 < diff <= TEMP_TOLERANCE (close to setpoint):
 *          base - DEMAND_REDUCE (not below DEMAND_MIN)
 *      - diff > TEMP_TOLERANCE (well below setpoint):
 *          base + boost. Boost is stepped in BOOST_STEPS
 *          (threshold in K, addition in %-points), the step with
 *          the highest reached threshold applies. Result is capped
 *          at BOOST_MAX_DEMAND (base itself is never undercut).
 *          BOOST_ENABLE turns this off.
 *   3. Hold time: demand is only written on change.
 *      Reduction takes effect immediately, increase only after
 *      DEMAND_HOLD_UP_MINUTES since the last script change
 *      (0 = no hold time). The first value of a session is
 *      written without waiting.
 * Setpoint (autot) and hysteresis (autor) are also only written
 * when the device deviates from the target value.
 *
 * MANUAL OVERRIDE
 *   - Setpoint: If autot deviates from the last scheduled setpoint,
 *     the manual value applies until the next schedule start.
 *     The script no longer writes the setpoint but continues to
 *     regulate demand based on the manual value.
 *   - Demand: If demand deviates by more than DEMAND_TOLERANCE from
 *     the last value written by the script, demand control is paused
 *     until a new schedule start or new manual session resets it.
 *   - Reset occurs at schedule phase start, at the end of Luxury,
 *     and at the start/end of a manual session.
 *
 * MANUAL OPERATION (outside schedule)
 * If the unit is switched on outside a phase (remote, app,
 * dashboard) and ENABLE_MANUAL_SUPPORT is active, the script
 * takes over demand control. The setpoint is not touched.
 * Comfort functions are set once per session (MANUAL_TOUCH_COMFORT).
 * The session ends when the unit is switched off.
 *
 * COMFORT FUNCTIONS
 *   - Fan set to Auto ("A")
 *   - Vertical swing (swingAuto): runs for up to swingMaxMinutes
 *     and ends earlier once the setpoint is reached. Comfort mode
 *     is then re-enabled (COMFORT_AFTER_SWING) since the Daikin
 *     disables it when swing is active. A delay of COMFORT_DELAY_SEC
 *     is inserted between swing OFF and comfort ON.
 *   - ECO mode (econoAuto) is enabled if currently off
 *
 * RESTART
 * On script start, the current day state is derived: already
 * passed triggers do not fire again. If the time is within a phase,
 * it is restored (unit on, comfort, control). Nothing is switched
 * outside the schedule.
 *
 * ALIASES / SENSORS
 *   power, mode (H = Heating), fan, swingv, econo, comfort,
 *   setTemp (autot), deadband (autor), demand
 *   Actual temperature: alias.0.WohnzimmerEnv.ACTUAL
 *   Outdoor temperature: Aussentemperatur data point of the Daikin
 ***************************************************/

// CONFIGURATION
var ALIAS = {
    power:    "alias.0.WohnzimmerDaikin.power",
    mode:     "alias.0.WohnzimmerDaikin.modus",
    fan:      "alias.0.WohnzimmerDaikin.fanmodus",
    swingv:   "alias.0.WohnzimmerDaikin.swingv",
    econo:    "alias.0.WohnzimmerDaikin.econo",
    setTemp:  "alias.0.WohnzimmerDaikin.autot",
    deadband: "alias.0.WohnzimmerDaikin.autor",
    demand:   "alias.0.WohnzimmerDaikin.demand",
    comfort:  "alias.0.WohnzimmerDaikin.comfort"
};

var SENSOR = {
    actualTemp:  "alias.0.WohnzimmerEnv.ACTUAL",
    outdoorTemp: "alias.0.WohnzimmerDaikin.Aussentemperatur"
};

var SETPOINT_STANDARD = 21.2;
var SETPOINT_LUXUS    = 21.8;
var DEADBAND          = 0.3;
var DEMAND_MIN        = 30;
var DEMAND_REDUCE     = 5;
var TEMP_TOLERANCE    = 0.5;   // setpoint/actual deviation (K) below which demand is not reduced
var DEMAND_TOLERANCE  = 2;     // % tolerance when comparing curDemand vs lastWrittenDemand
var swingAuto         = true;
var swingMaxMinutes   = 90;
// The Daikin disables comfort mode when swing is active. After auto-swing ends
// (timeout or setpoint reached), comfort is re-enabled.
var COMFORT_AFTER_SWING = true;
var COMFORT_DELAY_SEC   = 2;     // short pause between swing OFF and comfort ON
var econoAuto         = true;
var ENABLE_STANDARD   = false;
var ENABLE_LUXUS      = true;

// BOOST for large setpoint/actual deviation (only when actual < setpoint)
// The step with the highest reached threshold applies ("diff" in K, "add" in %-points
// on top of the outdoor temperature demand). Both steps freely adjustable, more steps possible.
var BOOST_ENABLE     = true;
var BOOST_STEPS = [
    { diff: 0.5, add: 5  },   // Step 1: from > 0.5 K below setpoint
    { diff: 1.0, add: 10 }    // Step 2: from > 1.0 K below setpoint
];
var BOOST_MAX_DEMAND = 95;    // cap for boost (there is reportedly a large jump between 95 and 100)

// HOLD TIME for demand increases
// Reduction takes effect immediately, increase only after this time since last demand change.
// 0 = disabled (increase immediately).
var DEMAND_HOLD_UP_MINUTES = 5;

// Manual operation outside schedule
var ENABLE_MANUAL_SUPPORT = true;   // demand + comfort also during manual operation
var MANUAL_TOUCH_COMFORT  = true;   // set fan=A, swing, ECO once per session

var scheduleConfig = {
     // Index        0=Sun, 1=Mon,   2=Tue,   3=Wed,   4=Thu,  5=Fri, 6=Sat (getDay())
    startStandard: ["10:00","10:00","10:00","11:00","10:00","10:00","10:00"],
    stopStandard:  ["16:00","16:00","16:00","16:00","16:00","16:00","16:00"],
    startLuxus:    ["16:00","16:00","16:00","16:00","16:00","16:00","16:00"],
    stopLuxus:     ["21:45","21:45","21:45","21:45","21:45","22:00","22:00"]
};

var demandCurve = [
    { temp: -5, demand: 60 },
    { temp:  0, demand: 55 },
    { temp:  5, demand: 50 },
    { temp: 10, demand: 45 },
    { temp: 15, demand: DEMAND_MIN }
];

// STATE
var lastScheduledSetpoint = null;
var manualOverrideActive  = false;   // setpoint override
var manualSetpoint        = null;
var manualDemandOverride  = false;   // demand override
var lastWrittenDemand     = null;    // last demand value written by this script
var lastDemandChangeTs    = 0;       // timestamp of last demand change by this script
var swingTimer            = null;
var activeSchedule        = null;
var manualSessionActive   = false;
var manualComfortApplied  = false;
var lastStdOn  = "";
var lastStdOff = "";
var lastLuxOn  = "";
var lastLuxOff = "";

// HELPER FUNCTIONS
function isHeatingMode() {
    var s = getState(ALIAS.mode);
    var mode = s ? s.val : "H";
    if (mode !== "H") {
        log("Mode " + mode + " - control paused", "warn");
        return false;
    }
    return true;
}

function isPowerOn() {
    var s = getState(ALIAS.power);
    return s && s.val === true;
}

// Only write if the device deviates from the target value
function setIfChanged(id, val) {
    var s = getState(id);
    var cur = s ? s.val : null;
    var same;
    if (typeof val === "number" && cur !== null && !isNaN(parseFloat(cur))) {
        same = Math.abs(parseFloat(cur) - val) < 0.001;
    } else {
        same = (cur === val);
    }
    if (!same) setState(id, val, false);
}

function clearSwingTimer() {
    if (swingTimer) {
        clearTimeout(swingTimer);
        swingTimer = null;
    }
}

// Re-enable comfort mode (Daikin disables it automatically when swing is active)
function enableComfortMode() {
    if (!COMFORT_AFTER_SWING || !ALIAS.comfort) return;
    if (!existsState(ALIAS.comfort)) {
        log("Comfort alias not found: " + ALIAS.comfort, "warn");
        return;
    }
    setTimeout(function() {
        var ss = getState(ALIAS.swingv);
        if (ss && ss.val === true) return;   // swing was re-activated in the meantime
        if (!isPowerOn()) return;            // unit switched off in the meantime
        var sc = getState(ALIAS.comfort);
        if (!sc || sc.val !== true) {
            setState(ALIAS.comfort, true, false);
            log("Comfort mode enabled after swing");
        }
    }, COMFORT_DELAY_SEC * 1000);
}

// End swing, but only once (while timer is still running)
function stopSwing() {
    if (swingTimer) {
        clearSwingTimer();
        setState(ALIAS.swingv, false, false);
        enableComfortMode();
    }
}

function ensureEcono() {
    var s = getState(ALIAS.econo);
    if (econoAuto && (!s || s.val !== true)) {
        setState(ALIAS.econo, true, false);
        log("ECO mode enabled");
    }
}

function activateComfortFeatures() {
    var sf = getState(ALIAS.fan);
    if (!sf || sf.val !== "A") {
        setState(ALIAS.fan, "A", false);
    }

    var ss = getState(ALIAS.swingv);
    if (swingAuto && (!ss || ss.val !== true)) {
        setState(ALIAS.swingv, true, false);
        clearSwingTimer();
        swingTimer = setTimeout(function() {
            swingTimer = null;
            setState(ALIAS.swingv, false, false);
            log("Swing timeout - deactivated");
            enableComfortMode();
        }, swingMaxMinutes * 60 * 1000);
    }

    ensureEcono();
}

function calcBaseDemand(outTemp) {
    var first = demandCurve[0];
    var last  = demandCurve[demandCurve.length - 1];
    if (outTemp <= first.temp) return first.demand;
    if (outTemp >= last.temp)  return last.demand;
    for (var i = 0; i < demandCurve.length - 1; i++) {
        var a = demandCurve[i];
        var b = demandCurve[i + 1];
        if (outTemp >= a.temp && outTemp <= b.temp) {
            var ratio = (outTemp - a.temp) / (b.temp - a.temp);
            return Math.round(a.demand + ratio * (b.demand - a.demand));
        }
    }
    return DEMAND_MIN;
}

// Boost addition (%-points) for a deviation diff = setpoint - actual
function calcBoost(diff) {
    if (!BOOST_ENABLE) return 0;
    var bestDiff = -1;
    var add = 0;
    for (var i = 0; i < BOOST_STEPS.length; i++) {
        var st = BOOST_STEPS[i];
        if (diff > st.diff && st.diff > bestDiff) {
            bestDiff = st.diff;
            add = st.add;
        }
    }
    return add;
}

function adjustDemand(base, actual, target) {
    var diff = target - actual;
    if (diff <= 0) {
        stopSwing();
        return Math.max(base - DEMAND_REDUCE, DEMAND_MIN);
    }
    if (diff > TEMP_TOLERANCE) {
        // well below setpoint: outdoor demand + boost, capped
        var boosted = base + calcBoost(diff);
        return Math.min(boosted, Math.max(base, BOOST_MAX_DEMAND));
    }
    return Math.max(base - DEMAND_REDUCE, DEMAND_MIN);
}

function checkManualOverride() {
    // Setpoint override
    var s = getState(ALIAS.setTemp);
    var cur = s ? parseFloat(s.val) : null;
    if (cur !== null &&
        lastScheduledSetpoint !== null &&
        cur !== lastScheduledSetpoint &&
        !manualOverrideActive) {
        manualOverrideActive = true;
        manualSetpoint = cur;
        log("Manual setpoint override detected: " + manualSetpoint + "°C");
    }

    // Demand override
    var sd = getState(ALIAS.demand);
    var curDemand = sd ? parseInt(sd.val, 10) : null;
    if (curDemand !== null &&
        lastWrittenDemand !== null &&
        Math.abs(curDemand - lastWrittenDemand) > DEMAND_TOLERANCE &&
        !manualDemandOverride) {
        manualDemandOverride = true;
        log("Manual demand override detected: " + curDemand + "% (script had written " + lastWrittenDemand + "%) - control paused");
    }
}

// Write demand + tracking + hold time
// - same value: do not write
// - reduction: immediate
// - increase: not before DEMAND_HOLD_UP_MINUTES since last change
function writeDemand(val) {
    var now = Date.now();
    if (lastWrittenDemand !== null) {
        if (val === lastWrittenDemand) return;
        if (val > lastWrittenDemand &&
            DEMAND_HOLD_UP_MINUTES > 0 &&
            (now - lastDemandChangeTs) < DEMAND_HOLD_UP_MINUTES * 60 * 1000) {
            log("Demand increase " + lastWrittenDemand + "% -> " + val + "% held back (hold time)", "debug");
            return;
        }
    }
    setState(ALIAS.demand, val, false);
    lastWrittenDemand  = val;
    lastDemandChangeTs = now;
}

// Log text: effective demand (+ target if held back)
function demandText(target) {
    if (lastWrittenDemand === null || lastWrittenDemand === target) return target + "%";
    return lastWrittenDemand + "% (target " + target + "%, hold time)";
}

// Reset overrides (on schedule change or power reset)
function resetOverrides() {
    manualOverrideActive = false;
    manualSetpoint       = null;
    manualDemandOverride = false;
    lastWrittenDemand    = null;
    lastDemandChangeTs   = 0;
}

// Regular schedule control with override detection
function applyControlWithManual(setpoint) {
    if (!isHeatingMode()) return;
    var sa = getState(SENSOR.actualTemp);
    var so = getState(SENSOR.outdoorTemp);
    var actual  = sa ? parseFloat(sa.val) : setpoint;
    var outdoor = so ? parseFloat(so.val) : 10;
    if (isNaN(actual))  actual  = setpoint;
    if (isNaN(outdoor)) outdoor = 10;

    // Setpoint
    if (manualOverrideActive) {
        log("Schedule (setpoint manual): keeping " + manualSetpoint + "°C");
        setpoint = manualSetpoint;
    } else {
        lastScheduledSetpoint = setpoint;
        setIfChanged(ALIAS.setTemp, setpoint);
    }
    setIfChanged(ALIAS.deadband, DEADBAND);

    // Demand
    if (manualDemandOverride) {
        var sd = getState(ALIAS.demand);
        var cur = sd ? parseInt(sd.val, 10) : null;
        log("Schedule: target=" + setpoint + "°C actual=" + actual + "°C outdoor=" + outdoor + "°C demand=" + cur + "% (manual, not touched)");
        return;
    }

    var baseDemand = calcBaseDemand(outdoor);
    var demand     = adjustDemand(baseDemand, actual, setpoint);
    writeDemand(demand);

    log("Schedule: target=" + setpoint + "°C actual=" + actual + "°C outdoor=" + outdoor + "°C demand=" + demandText(demand));
}

// Control in manual operation — do NOT touch setpoint
function applyManualSupport() {
    if (!isHeatingMode()) return;
    var st = getState(ALIAS.setTemp);
    var sa = getState(SENSOR.actualTemp);
    var so = getState(SENSOR.outdoorTemp);

    var setpoint = st ? parseFloat(st.val) : null;
    if (setpoint === null || isNaN(setpoint)) {
        log("Manual: no valid setpoint readable, skipped", "warn");
        return;
    }
    var actual  = sa ? parseFloat(sa.val) : setpoint;
    var outdoor = so ? parseFloat(so.val) : 10;
    if (isNaN(actual))  actual  = setpoint;
    if (isNaN(outdoor)) outdoor = 10;

    // Comfort features once per manual session
    if (MANUAL_TOUCH_COMFORT && !manualComfortApplied) {
        activateComfortFeatures();
        manualComfortApplied = true;
        log("Manual: comfort features set initially");
    }

    setIfChanged(ALIAS.deadband, DEADBAND);

    // Respect demand override
    if (manualDemandOverride) {
        var sd = getState(ALIAS.demand);
        var cur = sd ? parseInt(sd.val, 10) : null;
        log("Manual: target=" + setpoint + "°C actual=" + actual + "°C outdoor=" + outdoor + "°C demand=" + cur + "% (manual, not touched)");
        return;
    }

    var baseDemand = calcBaseDemand(outdoor);
    var demand     = adjustDemand(baseDemand, actual, setpoint);
    writeDemand(demand);

    log("Manual: target=" + setpoint + "°C actual=" + actual + "°C outdoor=" + outdoor + "°C demand=" + demandText(demand));
}

// SCHEDULE CONTROL
function checkSchedule() {
    var now = new Date();
    var wd  = now.getDay();
    var hm  = now.toTimeString().slice(0, 5);
    var day = now.toDateString();

    checkManualOverride();

    // --- Schedule triggers ---
    if (ENABLE_STANDARD && hm >= scheduleConfig.startStandard[wd] && lastStdOn !== day) {
        resetOverrides();
        manualSessionActive  = false;
        manualComfortApplied = false;
        setState(ALIAS.power, true, false);
        activateComfortFeatures();
        applyControlWithManual(SETPOINT_STANDARD);
        activeSchedule = "standard";
        lastStdOn = day;
        log("Standard operation started");
    }

    if (ENABLE_STANDARD && hm >= scheduleConfig.stopStandard[wd] && lastStdOff !== day) {
        if (activeSchedule === "standard") activeSchedule = null;
        lastStdOff = day;
        log("Standard operation ended");
    }

    if (ENABLE_LUXUS && hm >= scheduleConfig.startLuxus[wd] && lastLuxOn !== day) {
        resetOverrides();
        manualSessionActive  = false;
        manualComfortApplied = false;
        setState(ALIAS.power, true, false);
        activateComfortFeatures();
        applyControlWithManual(SETPOINT_LUXUS);
        activeSchedule = "luxus";
        lastLuxOn = day;
        log("Luxury operation started");
    }

    if (ENABLE_LUXUS && hm >= scheduleConfig.stopLuxus[wd] && lastLuxOff !== day) {
        setState(ALIAS.power, false, false);
        clearSwingTimer();
        activeSchedule = null;
        manualSessionActive  = false;
        manualComfortApplied = false;
        resetOverrides();
        lastLuxOff = day;
        log("Luxury operation ended - unit OFF");
    }

    // --- Running control ---
    if (activeSchedule === "standard") {
        applyControlWithManual(SETPOINT_STANDARD);
        return;
    }
    if (activeSchedule === "luxus") {
        applyControlWithManual(SETPOINT_LUXUS);
        return;
    }

    // --- Outside schedule: manual operation? ---
    if (!ENABLE_MANUAL_SUPPORT) return;

    if (isPowerOn()) {
        if (!manualSessionActive) {
            manualSessionActive  = true;
            manualComfortApplied = false;
            // Reset override tracking for new session
            lastScheduledSetpoint = null;
            resetOverrides();
            log("Manual operation detected - demand control activated");
        }
        applyManualSupport();
    } else if (manualSessionActive) {
        // Switched off manually
        manualSessionActive  = false;
        manualComfortApplied = false;
        resetOverrides();
        clearSwingTimer();
        log("Manual operation ended (power OFF)");
    }
}

// STARTUP INIT
function initOnStart() {
    var now = new Date();
    var wd  = now.getDay();
    var hm  = now.toTimeString().slice(0, 5);
    var day = now.toDateString();

    if (hm >= scheduleConfig.startStandard[wd]) lastStdOn  = day;
    if (hm >= scheduleConfig.stopStandard[wd])  lastStdOff = day;
    if (hm >= scheduleConfig.startLuxus[wd])    lastLuxOn  = day;
    if (hm >= scheduleConfig.stopLuxus[wd])     lastLuxOff = day;

    if (ENABLE_LUXUS &&
        hm >= scheduleConfig.startLuxus[wd] &&
        hm <  scheduleConfig.stopLuxus[wd]) {
        activeSchedule = "luxus";
        setState(ALIAS.power, true, false);
        activateComfortFeatures();
        applyControlWithManual(SETPOINT_LUXUS);
        log("Restart mid-luxury (" + hm + ") - operation restored");
    } else if (ENABLE_STANDARD &&
               hm >= scheduleConfig.startStandard[wd] &&
               hm <  scheduleConfig.stopStandard[wd]) {
        activeSchedule = "standard";
        setState(ALIAS.power, true, false);
        activateComfortFeatures();
        applyControlWithManual(SETPOINT_STANDARD);
        log("Restart mid-standard (" + hm + ") - operation restored");
    } else {
        activeSchedule = null;
        log("Restart outside schedule (" + hm + ")");
    }
}

initOnStart();
schedule("* * * * *", checkSchedule);
log("DAIKIN Control V01 started");
