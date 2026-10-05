/***************************************************
 * DAIKIN Alias-Regelung V01 — Übergangszeit-tauglich
 * ==================================================
 *
 * ZWECK
 * Übergeordnete Regelung für die Wohnzimmer-Daikin über das
 * Faikout-Modul (ioBroker-Aliase). Das Faikout läuft im
 * Thermostatmodus und trifft die Schaltentscheidung selbst
 * (heizt bei autot - autor, stoppt bei autot + autor). Dieses
 * Skript gibt ihm nur die Vorgaben und begrenzt die Leistung:
 *   - Zieltemperatur (autot) nach Zeitplan
 *   - Hysterese (autor, hier DEADBAND)
 *   - maximale Leistung (Demand) nach Außentemperatur und
 *     Soll/Ist-Abweichung
 * Zusätzlich: Wochen-Zeitplan, Komfortfunktionen und Respekt vor
 * manuellen Eingriffen. Aktiv nur im Heizmodus ("H"), in jedem
 * anderen Modus pausiert die Regelung (Warnung im Log).
 *
 * ABLAUF
 * Ein Timer ruft jede Minute checkSchedule() auf:
 *   1. Manuelle Übersteuerung von Sollwert/Demand erkennen
 *   2. Zeitplan-Trigger auswerten (Start/Ende Standard und Luxus)
 *   3. Laufende Regelung ausführen (Zeitplan oder manueller Betrieb)
 *
 * ZEITPLAN
 * Pro Wochentag (0 = Sonntag) gibt es zwei Phasen:
 *   - Standardbetrieb: Sollwert SETPOINT_STANDARD
 *   - Luxusbetrieb:    Sollwert SETPOINT_LUXUS
 * Beim Start einer Phase wird das Gerät eingeschaltet, die
 * Komfortfunktionen aktiviert, der Sollwert gesetzt und alle
 * Übersteuerungen zurückgesetzt. Das Ende der Standardphase
 * schaltet nicht ab, die Luxusphase schließt sich an. Abgeschaltet
 * wird erst am Ende des Luxusbetriebs. ENABLE_STANDARD und
 * ENABLE_LUXUS schalten die Phasen einzeln ab.
 *
 * DEMAND-REGELUNG (maximale Leistung in %)
 *   1. Basis aus der Außentemperaturkennlinie demandCurve
 *      (linear interpoliert, außerhalb der Stützpunkte konstant).
 *      Je wärmer es draußen ist, desto niedriger die Basis, am
 *      Ende der Kennlinie DEMAND_MIN.
 *   2. Anpassung nach diff = Soll - Ist:
 *      - diff <= 0 (Soll erreicht/überschritten):
 *          Basis - DEMAND_REDUCE (nicht unter DEMAND_MIN),
 *          ein laufender Auto-Swing wird beendet
 *      - 0 < diff <= TEMP_TOLERANCE (nahe am Soll):
 *          Basis - DEMAND_REDUCE (nicht unter DEMAND_MIN)
 *      - diff > TEMP_TOLERANCE (weit unter Soll):
 *          Basis + Boost. Der Boost ist in BOOST_STEPS gestuft
 *          (Schwelle in K, Aufschlag in %-Punkten), es gilt die
 *          Stufe mit der größten erreichten Schwelle. Das Ergebnis
 *          ist auf BOOST_MAX_DEMAND gedeckelt (die Basis selbst
 *          wird nie unterschritten). BOOST_ENABLE schaltet ab.
 *   3. Haltezeit: Demand wird nur bei Änderung geschrieben.
 *      Absenken wirkt sofort, Anheben frühestens
 *      DEMAND_HOLD_UP_MINUTES nach der letzten Änderung des
 *      Skripts (0 = keine Haltezeit). Der erste Wert einer
 *      Session wird ohne Wartezeit geschrieben.
 * Sollwert (autot) und Hysterese (autor) werden ebenfalls nur
 * geschrieben, wenn das Gerät vom Zielwert abweicht.
 *
 * MANUELLE ÜBERSTEUERUNG
 *   - Sollwert: Weicht autot vom zuletzt gesetzten Zeitplan-Sollwert
 *     ab, gilt der manuelle Wert bis zum nächsten Zeitplanstart.
 *     Das Skript schreibt den Sollwert dann nicht mehr, regelt den
 *     Demand aber auf Basis des manuellen Werts.
 *   - Demand: Weicht der Demand um mehr als DEMAND_TOLERANCE von
 *     dem zuletzt vom Skript geschriebenen Wert ab, wird die
 *     Demand-Regelung pausiert, bis ein neuer Zeitplanstart oder
 *     eine neue manuelle Session die Übersteuerung zurücksetzt.
 *   - Zurückgesetzt wird bei Start einer Zeitplanphase, am Ende
 *     des Luxusbetriebs sowie bei Beginn/Ende einer manuellen Session.
 *
 * MANUELLER BETRIEB (außerhalb des Zeitplans)
 * Wird das Gerät außerhalb einer Phase eingeschaltet (Fernbedienung,
 * App, Dashboard) und ENABLE_MANUAL_SUPPORT ist aktiv, übernimmt
 * das Skript die Demand-Regelung. Der Sollwert wird dabei nicht
 * angefasst. Die Komfortfunktionen werden einmal pro Session
 * gesetzt (MANUAL_TOUCH_COMFORT). Die Session endet, wenn das
 * Gerät ausgeschaltet wird.
 *
 * KOMFORTFUNKTIONEN
 *   - Lüfter auf Auto ("A")
 *   - Vertikaler Swing (swingAuto): läuft maximal swingMaxMinutes
 *     und endet früher, sobald der Sollwert erreicht ist. Danach
 *     wird der Comfort-Modus wieder eingeschaltet
 *     (COMFORT_AFTER_SWING), da der Daikin ihn beim Swing selbst
 *     ausschaltet. Zwischen Swing AUS und Comfort EIN liegt
 *     COMFORT_DELAY_SEC.
 *   - ECO-Modus (econoAuto) wird eingeschaltet, falls aus
 *
 * NEUSTART
 * Beim Skriptstart wird der Zustand des Tages abgeleitet: Bereits
 * vergangene Trigger lösen nicht erneut aus. Liegt die Uhrzeit in
 * einer Phase, wird sie wiederhergestellt (Gerät an, Komfort,
 * Regelung). Außerhalb des Zeitplans wird nichts geschaltet.
 *
 * ALIASE / SENSOREN
 *   power, mode (H = Heizen), fan, swingv, econo, comfort,
 *   setTemp (autot), deadband (autor), demand
 *   Ist-Temperatur: alias.0.WohnzimmerEnv.ACTUAL
 *   Außentemperatur: Aussentemperatur-Datenpunkt der Daikin
 ***************************************************/

// KONFIGURATION
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
var TEMP_TOLERANCE    = 0.5;   // Soll/Ist-Abweichung (K), ab der nicht mehr abgesenkt wird
var DEMAND_TOLERANCE  = 2;     // % Toleranz beim Vergleich curDemand vs lastWrittenDemand
var swingAuto         = true;
var swingMaxMinutes   = 90;
// Daikin schaltet den Comfort-Modus beim Swing selbstständig aus. Nach Ende des Auto-Swings
// (Timeout oder Sollwert erreicht) wird Comfort wieder eingeschaltet.
var COMFORT_AFTER_SWING = true;
var COMFORT_DELAY_SEC   = 2;     // kurze Pause zwischen Swing AUS und Comfort EIN
var econoAuto         = true;
var ENABLE_STANDARD   = false;
var ENABLE_LUXUS      = true;

// BOOST bei großer Soll/Ist-Abweichung (nur wenn Ist < Soll)
// Es gilt die Stufe mit der größten erreichten Schwelle ("diff" in K, "add" in %-Punkten
// auf den Außentemperatur-Demand). Beide Stufen frei anpassbar, weitere Stufen möglich.
var BOOST_ENABLE     = true;
var BOOST_STEPS = [
    { diff: 0.5, add: 5  },   // Stufe 1: ab > 0,5 K unter Soll
    { diff: 1.0, add: 10 }    // Stufe 2: ab > 1,0 K unter Soll
];
var BOOST_MAX_DEMAND = 95;    // Deckel für den Boost (zw. 95 und 100 gibt es laut Forum einen großen Sprung)

// HALTEZEIT für Demand-Änderungen
// Absenken wirkt sofort, Anheben erst nach dieser Zeit seit der letzten Demand-Änderung.
// 0 = deaktiviert (Anheben sofort).
var DEMAND_HOLD_UP_MINUTES = 5;

// Manueller Betrieb außerhalb Schedule
var ENABLE_MANUAL_SUPPORT = true;   // Demand+Komfort auch bei manuellem Einschalten
var MANUAL_TOUCH_COMFORT  = true;   // einmalig Fan=A, Swing, ECO setzen

var scheduleConfig = {
     // Index        0=So,  1=Mo,    2=Di,    3=Mi,   4=Do,   5=Fr,  6=Sa (entspricht getDay())
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

/***************************************************
 * =================================================
 *   AB HIER NICHTS MEHR ÄNDERN
 * =================================================
 ***************************************************/

// ZUSTÄNDE
var lastScheduledSetpoint = null;
var manualOverrideActive  = false;   // Sollwert-Override
var manualSetpoint        = null;
var manualDemandOverride  = false;   // Demand-Override
var lastWrittenDemand     = null;    // zuletzt vom Skript geschriebener Demand
var lastDemandChangeTs    = 0;       // Zeitpunkt der letzten Demand-Änderung durch das Skript
var swingTimer            = null;
var activeSchedule        = null;
var manualSessionActive   = false;
var manualComfortApplied  = false;
var lastStdOn  = "";
var lastStdOff = "";
var lastLuxOn  = "";
var lastLuxOff = "";

// HILFSFUNKTIONEN
function isHeatingMode() {
    var s = getState(ALIAS.mode);
    var mode = s ? s.val : "H";
    if (mode !== "H") {
        log("Modus " + mode + " - Regelung pausiert", "warn");
        return false;
    }
    return true;
}

function isPowerOn() {
    var s = getState(ALIAS.power);
    return s && s.val === true;
}

// Nur schreiben, wenn das Gerät vom Zielwert abweicht
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

// Comfort-Modus einschalten (der Daikin deaktiviert ihn beim Swing selbstständig)
function enableComfortMode() {
    if (!COMFORT_AFTER_SWING || !ALIAS.comfort) return;
    if (!existsState(ALIAS.comfort)) {
        log("Comfort-Alias nicht gefunden: " + ALIAS.comfort, "warn");
        return;
    }
    setTimeout(function() {
        var ss = getState(ALIAS.swingv);
        if (ss && ss.val === true) return;   // Swing wurde zwischenzeitlich wieder aktiviert
        if (!isPowerOn()) return;            // Gerät inzwischen aus
        var sc = getState(ALIAS.comfort);
        if (!sc || sc.val !== true) {
            setState(ALIAS.comfort, true, false);
            log("Comfort-Modus nach Swing aktiviert");
        }
    }, COMFORT_DELAY_SEC * 1000);
}

// Swing beenden, aber nur einmal (solange der Timer noch läuft)
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
        log("ECO-Modus aktiviert");
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
            log("Swing Timeout - deaktiviert");
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

// Boost-Aufschlag (%-Punkte) für eine Abweichung diff = Soll - Ist
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
        // weit unter Soll: Außentemperatur-Demand + Boost, gedeckelt
        var boosted = base + calcBoost(diff);
        return Math.min(boosted, Math.max(base, BOOST_MAX_DEMAND));
    }
    return Math.max(base - DEMAND_REDUCE, DEMAND_MIN);
}

function checkManualOverride() {
    // Sollwert-Override
    var s = getState(ALIAS.setTemp);
    var cur = s ? parseFloat(s.val) : null;
    if (cur !== null &&
        lastScheduledSetpoint !== null &&
        cur !== lastScheduledSetpoint &&
        !manualOverrideActive) {
        manualOverrideActive = true;
        manualSetpoint = cur;
        log("Manuelle Sollwert-Übersteuerung erkannt: " + manualSetpoint + "°C");
    }

    // Demand-Override
    var sd = getState(ALIAS.demand);
    var curDemand = sd ? parseInt(sd.val, 10) : null;
    if (curDemand !== null &&
        lastWrittenDemand !== null &&
        Math.abs(curDemand - lastWrittenDemand) > DEMAND_TOLERANCE &&
        !manualDemandOverride) {
        manualDemandOverride = true;
        log("Manuelle Demand-Übersteuerung erkannt: " + curDemand + "% (Skript hatte " + lastWrittenDemand + "% geschrieben) - Regelung pausiert");
    }
}

// Demand schreiben + Tracking + Haltezeit
// - gleicher Wert: nicht schreiben
// - Absenken: sofort
// - Anheben: frühestens DEMAND_HOLD_UP_MINUTES nach der letzten Änderung
function writeDemand(val) {
    var now = Date.now();
    if (lastWrittenDemand !== null) {
        if (val === lastWrittenDemand) return;
        if (val > lastWrittenDemand &&
            DEMAND_HOLD_UP_MINUTES > 0 &&
            (now - lastDemandChangeTs) < DEMAND_HOLD_UP_MINUTES * 60 * 1000) {
            log("Demand-Anhebung " + lastWrittenDemand + "% -> " + val + "% zurückgehalten (Haltezeit)", "debug");
            return;
        }
    }
    setState(ALIAS.demand, val, false);
    lastWrittenDemand  = val;
    lastDemandChangeTs = now;
}

// Text für das Log: tatsächlich gültiger Demand (+ Ziel, falls zurückgehalten)
function demandText(target) {
    if (lastWrittenDemand === null || lastWrittenDemand === target) return target + "%";
    return lastWrittenDemand + "% (Ziel " + target + "%, Haltezeit)";
}

// Reset Übersteuerungen (bei Schedule-Wechsel oder Power-Reset)
function resetOverrides() {
    manualOverrideActive = false;
    manualSetpoint       = null;
    manualDemandOverride = false;
    lastWrittenDemand    = null;
    lastDemandChangeTs   = 0;
}

// Reguläre Schedule-Regelung mit Override-Erkennung
function applyControlWithManual(setpoint) {
    if (!isHeatingMode()) return;
    var sa = getState(SENSOR.actualTemp);
    var so = getState(SENSOR.outdoorTemp);
    var actual  = sa ? parseFloat(sa.val) : setpoint;
    var outdoor = so ? parseFloat(so.val) : 10;
    if (isNaN(actual))  actual  = setpoint;
    if (isNaN(outdoor)) outdoor = 10;

    // Sollwert
    if (manualOverrideActive) {
        log("Schedule (Sollwert manuell): bleibt " + manualSetpoint + "°C");
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
        log("Schedule: Soll=" + setpoint + "°C Ist=" + actual + "°C Außen=" + outdoor + "°C Demand=" + cur + "% (manuell, nicht angetastet)");
        return;
    }

    var baseDemand = calcBaseDemand(outdoor);
    var demand     = adjustDemand(baseDemand, actual, setpoint);
    writeDemand(demand);

    log("Schedule: Soll=" + setpoint + "°C Ist=" + actual + "°C Außen=" + outdoor + "°C Demand=" + demandText(demand));
}

// Regelung im manuellen Betrieb — Sollwert NICHT anfassen
function applyManualSupport() {
    if (!isHeatingMode()) return;
    var st = getState(ALIAS.setTemp);
    var sa = getState(SENSOR.actualTemp);
    var so = getState(SENSOR.outdoorTemp);

    var setpoint = st ? parseFloat(st.val) : null;
    if (setpoint === null || isNaN(setpoint)) {
        log("Manuell: kein gültiger Sollwert lesbar, übersprungen", "warn");
        return;
    }
    var actual  = sa ? parseFloat(sa.val) : setpoint;
    var outdoor = so ? parseFloat(so.val) : 10;
    if (isNaN(actual))  actual  = setpoint;
    if (isNaN(outdoor)) outdoor = 10;

    // Komfort einmalig pro manueller Session
    if (MANUAL_TOUCH_COMFORT && !manualComfortApplied) {
        activateComfortFeatures();
        manualComfortApplied = true;
        log("Manuell: Komfortfeatures initial gesetzt");
    }

    setIfChanged(ALIAS.deadband, DEADBAND);

    // Demand-Override respektieren
    if (manualDemandOverride) {
        var sd = getState(ALIAS.demand);
        var cur = sd ? parseInt(sd.val, 10) : null;
        log("Manuell: Soll=" + setpoint + "°C Ist=" + actual + "°C Außen=" + outdoor + "°C Demand=" + cur + "% (manuell, nicht angetastet)");
        return;
    }

    var baseDemand = calcBaseDemand(outdoor);
    var demand     = adjustDemand(baseDemand, actual, setpoint);
    writeDemand(demand);

    log("Manuell: Soll=" + setpoint + "°C Ist=" + actual + "°C Außen=" + outdoor + "°C Demand=" + demandText(demand));
}

// ZEITPLANSTEUERUNG
function checkSchedule() {
    var now = new Date();
    var wd  = now.getDay();
    var hm  = now.toTimeString().slice(0, 5);
    var day = now.toDateString();

    checkManualOverride();

    // --- Schedule-Trigger ---
    if (ENABLE_STANDARD && hm >= scheduleConfig.startStandard[wd] && lastStdOn !== day) {
        resetOverrides();
        manualSessionActive  = false;
        manualComfortApplied = false;
        setState(ALIAS.power, true, false);
        activateComfortFeatures();
        applyControlWithManual(SETPOINT_STANDARD);
        activeSchedule = "standard";
        lastStdOn = day;
        log("Standardbetrieb gestartet");
    }

    if (ENABLE_STANDARD && hm >= scheduleConfig.stopStandard[wd] && lastStdOff !== day) {
        if (activeSchedule === "standard") activeSchedule = null;
        lastStdOff = day;
        log("Standardbetrieb beendet");
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
        log("Luxusbetrieb gestartet");
    }

    if (ENABLE_LUXUS && hm >= scheduleConfig.stopLuxus[wd] && lastLuxOff !== day) {
        setState(ALIAS.power, false, false);
        clearSwingTimer();
        activeSchedule = null;
        manualSessionActive  = false;
        manualComfortApplied = false;
        resetOverrides();
        lastLuxOff = day;
        log("Luxusbetrieb beendet - Gerät AUS");
    }

    // --- Laufende Regelung ---
    if (activeSchedule === "standard") {
        applyControlWithManual(SETPOINT_STANDARD);
        return;
    }
    if (activeSchedule === "luxus") {
        applyControlWithManual(SETPOINT_LUXUS);
        return;
    }

    // --- Außerhalb Schedule: manueller Betrieb? ---
    if (!ENABLE_MANUAL_SUPPORT) return;

    if (isPowerOn()) {
        if (!manualSessionActive) {
            manualSessionActive  = true;
            manualComfortApplied = false;
            // Override-Tracking für neue Session zurücksetzen
            lastScheduledSetpoint = null;
            resetOverrides();
            log("Manueller Betrieb erkannt - Demand-Regelung aktiviert");
        }
        applyManualSupport();
    } else if (manualSessionActive) {
        // Manuell wieder ausgeschaltet
        manualSessionActive  = false;
        manualComfortApplied = false;
        resetOverrides();
        clearSwingTimer();
        log("Manueller Betrieb beendet (Power AUS)");
    }
}

// NEUSTART-INIT
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
        log("Neustart mid-Luxus (" + hm + ") - Betrieb wiederhergestellt");
    } else if (ENABLE_STANDARD &&
               hm >= scheduleConfig.startStandard[wd] &&
               hm <  scheduleConfig.stopStandard[wd]) {
        activeSchedule = "standard";
        setState(ALIAS.power, true, false);
        activateComfortFeatures();
        applyControlWithManual(SETPOINT_STANDARD);
        log("Neustart mid-Standard (" + hm + ") - Betrieb wiederhergestellt");
    } else {
        activeSchedule = null;
        log("Neustart ausserhalb Zeitplan (" + hm + ")");
    }
}

initOnStart();
schedule("* * * * *", checkSchedule);
log("DAIKIN Regelung V01 gestartet");