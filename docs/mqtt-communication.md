<p align="right"><a href="https://buymeacoffee.com/raw07" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" height="40" alt="Buy Me A Coffee"></a></p>

# MQTT Communication / MQTT-Kommunikation

[English](#english) | [Deutsch](#deutsch)

← [Back to overview / Zurück zur Übersicht](../README.md)

---

## English

> **Important:** The Faikout uses completely different MQTT topics for reading and writing. Status is received on a single JSON topic. Commands are sent to separate topics per function — and the topic structure differs depending on the type of command. This is the most common source of confusion when integrating the Faikout.

> The topic structure shown here is the default. Topic prefixes can be customized in the Faikout web interface under Settings, but this guide refers to the defaults.

### Reading: Status Topic

| Topic | Direction | Payload |
|-------|-----------|---------|
| `state/<Hostname>/status` | ← receive | JSON object containing all current AC values |

The Faikout publishes the complete status as a single JSON message. Every piece of information — temperatures, operating mode, switch states, energy data — arrives in this one message and must be extracted from it.

Example payload:
```json
{
  "protocol": "S21",
  "online": true,
  "power": true,
  "mode": "H",
  "temp": 22.5,
  "fan": "A",
  "swingv": false,
  "swingh": false,
  "econo": true,
  "powerful": false,
  "comfort": false,
  "home": 22.5,
  "env": 21.2,
  "outside": 11.0,
  "inlet": 18.0,
  "liquid": 33.0,
  "comp": 26,
  "fanrpm": 940,
  "consumption": 280,
  "demand": 37,
  "hum": 50.0,
  "anglev": 72,
  "angleh": 0,
  "Whheating": 1539700,
  "Whcooling": 46100,
  "Whoutside": 1587900,
  "autot": 21.5,
  "autor": 0.3,
  "autoe": true,
  "autop": false,
  "auto0": "23:00",
  "auto1": "00:00",
  "antifreeze": false,
  "heat": true,
  "control": true,
  "slave": false
}
```

**Status fields:**

| Field | Type | Unit | Description |
|-------|------|------|-------------|
| `protocol` | string | – | Protocol in use (e.g. `S21`) |
| `online` | boolean | – | AC unit reachable via S21 |
| `control` | boolean | – | External temperature control active (env value valid) |
| `heat` | boolean | – | Currently heating |
| `slave` | boolean | – | Slave mode active |
| `antifreeze` | boolean | – | Anti-freeze protection active |
| `power` | boolean | – | AC on/off |
| `mode` | string | – | Operating mode: `H` Heat · `C` Cool · `F` Fan · `D` Dry · `A` Auto |
| `temp` | number | °C | Daikin internal setpoint (read-only) |
| `fan` | string | – | Fan speed: `1`–`5` · `A` Auto · `Q` Quiet |
| `swingv` | boolean | – | Vertical swing active |
| `swingh` | boolean | – | Horizontal swing active |
| `econo` | boolean | – | Economy mode |
| `powerful` | boolean | – | Powerful mode |
| `comfort` | boolean | – | Comfort airflow mode |
| `demand` | number | % | Compressor load limit |
| `home` | number | °C | Return air temperature (inlet of indoor unit) |
| `env` | number | °C | Room temperature (external reference, if sent) |
| `outside` | number | °C | Outdoor temperature |
| `inlet` | number | °C | Inlet temperature |
| `liquid` | number | °C | Refrigerant liquid temperature |
| `comp` | number | Hz | Compressor speed |
| `fanrpm` | number | RPM | Fan speed |
| `consumption` | number | W | Current power consumption |
| `hum` | number | % | Humidity (if supported) |
| `anglev` | number | ° | Vertical vane angle |
| `angleh` | number | ° | Horizontal vane angle |
| `Whheating` | number | Wh | Cumulative heating energy |
| `Whcooling` | number | Wh | Cumulative cooling energy |
| `Whoutside` | number | Wh | Outdoor unit energy meter |
| `autot` | number | °C | Faikout target temperature (auto mode) |
| `autor` | number | °C | Faikout hysteresis |
| `autoe` | boolean | – | Faikout auto mode enabled |
| `autop` | boolean | – | Auto power on/off enabled |
| `auto0` | string | – | Timer off time (e.g. `23:00`) |
| `auto1` | string | – | Timer on time (e.g. `06:30`) |

> Not all fields are present on every device. Optional features (streamer, humidifier, BLE sensor etc.) only appear if enabled on the device.

---

### Writing: Command Topics

The Faikout uses three different topic types for writing, depending on the function:

| Topic | Payload | Used for |
|-------|---------|---------|
| `command/<Hostname>/control` | JSON object | Power, swing, external temperature |
| `command/<Hostname>/<key>` | Direct value | Operating mode, fan speed, special modes |
| `setting/<Hostname>/<key>` | Direct value | Target temperature, device configuration |
| `setting/<Hostname>` | JSON object | Timer times |

#### `command/<Hostname>/control`

Payload is a JSON object with exactly one key:

| Key | Payload example | Description |
|-----|-----------------|-------------|
| `power` | `{"power":true}` | AC on/off |
| `swingv` | `{"swingv":true}` | Vertical swing on/off |
| `swingh` | `{"swingh":true}` | Horizontal swing on/off |
| `env` | `{"env":21.5}` | External room temperature reference (°C) |

> **Note on `env`:** The Faikout uses this value as its temperature reference for control as long as updates keep arriving. If no update is received for longer than the configured `tcontrol` timeout (seconds), the Faikout falls back to its internal sensor and clears the `control` flag in the status.

#### `command/<Hostname>/<key>`

One topic per key. Boolean fields use `1` for on, `0` for off.

| Key | Values | Description |
|-----|--------|-------------|
| `mode` | `H` · `C` · `F` · `D` · `A` | Operating mode |
| `fan` | `1`–`5` · `A` · `Q` | Fan speed |
| `econo` | `1` / `0` | Economy mode |
| `powerful` | `1` / `0` | Powerful mode |
| `comfort` | `1` / `0` | Comfort airflow |
| `demand` | `0`–`100` | Compressor load limit (%) |
| `autoe` | `1` / `0` | Faikout auto mode on/off |
| `autop` | `1` / `0` | Auto power on/off |
| `restart` | `1` | Restart Faikout device |

Optional (only available if the feature is active on the device):

| Key | Values | Description |
|-----|--------|-------------|
| `streamer` | `1` / `0` | Streamer air purifier |
| `led` | `1` / `0` | Display LEDs |
| `quiet` | `1` / `0` | Quiet mode (outdoor unit) |
| `humidify` | `X` · `L` · `S` · `H` · `C` | Humidifier mode |

#### `setting/<Hostname>/<key>`

Direct value. Settings persist across device restarts.

| Key | Unit | Description |
|-----|------|-------------|
| `autot` | °C | Target temperature for auto mode |
| `autor` | °C | Hysteresis |
| `heatback` | °C | Heat pull-back offset |
| `coolback` | °C | Cool pull-back offset |
| `tcontrol` | s | External temperature control timeout |

#### `setting/<Hostname>` – Timer times

Timer on/off times are written as a JSON object to the **base setting topic** (no key suffix). The time value must be provided **without colon**:

| Key | Payload example | Description |
|-----|-----------------|-------------|
| `auto0` | `{"auto0":"2300"}` | Timer off time (`23:00` → `2300`) |
| `auto1` | `{"auto1":"0630"}` | Timer on time (`06:30` → `0630`) |

---

## Deutsch

> **Wichtig:** Der Faikout verwendet für Lesen und Schreiben vollständig unterschiedliche MQTT-Topics. Der Status wird über ein einziges JSON-Topic empfangen. Befehle werden über separate Topics je Funktion gesendet — und die Topic-Struktur unterscheidet sich je nach Befehlstyp. Das ist die häufigste Fehlerquelle bei der Faikout-Integration.

> Die hier beschriebene Topic-Struktur gilt für die Standardeinstellung. Die Topic-Präfixe können im Faikout-Webinterface unter Einstellungen angepasst werden, dieses Dokument bezieht sich auf die Standardwerte.

### Lesen: Status-Topic

| Topic | Richtung | Payload |
|-------|----------|---------|
| `state/<Hostname>/status` | ← empfangen | JSON-Objekt mit allen aktuellen AC-Werten |

Der Faikout veröffentlicht den kompletten Status als einzelne JSON-Nachricht. Alle Informationen — Temperaturen, Betriebsmodus, Schaltzustände, Energiedaten — kommen in dieser einen Nachricht an und müssen daraus extrahiert werden.

Beispiel-Payload:
```json
{
  "protocol": "S21",
  "online": true,
  "power": true,
  "mode": "H",
  "temp": 22.5,
  "fan": "A",
  "swingv": false,
  "swingh": false,
  "econo": true,
  "powerful": false,
  "comfort": false,
  "home": 22.5,
  "env": 21.2,
  "outside": 11.0,
  "inlet": 18.0,
  "liquid": 33.0,
  "comp": 26,
  "fanrpm": 940,
  "consumption": 280,
  "demand": 37,
  "hum": 50.0,
  "anglev": 72,
  "angleh": 0,
  "Whheating": 1539700,
  "Whcooling": 46100,
  "Whoutside": 1587900,
  "autot": 21.5,
  "autor": 0.3,
  "autoe": true,
  "autop": false,
  "auto0": "23:00",
  "auto1": "00:00",
  "antifreeze": false,
  "heat": true,
  "control": true,
  "slave": false
}
```

**Status-Felder:**

| Feld | Typ | Einheit | Beschreibung |
|------|-----|---------|--------------|
| `protocol` | string | – | Verwendetes Protokoll (z.B. `S21`) |
| `online` | boolean | – | Klimagerät über S21 erreichbar |
| `control` | boolean | – | Externe Temperaturregelung aktiv (env-Wert gültig) |
| `heat` | boolean | – | Heizbetrieb aktiv |
| `slave` | boolean | – | Slave-Modus aktiv |
| `antifreeze` | boolean | – | Frostschutz aktiv |
| `power` | boolean | – | Klimagerät ein/aus |
| `mode` | string | – | Betriebsmodus: `H` Heizen · `C` Kühlen · `F` Lüften · `D` Trocknen · `A` Auto |
| `temp` | number | °C | Daikin-interner Sollwert (nur lesend) |
| `fan` | string | – | Lüfterstufe: `1`–`5` · `A` Auto · `Q` Leise |
| `swingv` | boolean | – | Vertikale Lamellenbewegung aktiv |
| `swingh` | boolean | – | Horizontale Lamellenbewegung aktiv |
| `econo` | boolean | – | Eco-Modus |
| `powerful` | boolean | – | Powerful-Modus |
| `comfort` | boolean | – | Comfort-Airflow-Modus |
| `demand` | number | % | Begrenzte Verdichterleistung |
| `home` | number | °C | Rücklufttemperatur (Ansaug des Innengeräts) |
| `env` | number | °C | Raumtemperatur (externer Referenzwert, falls gesendet) |
| `outside` | number | °C | Außentemperatur |
| `inlet` | number | °C | Einlasstemperatur |
| `liquid` | number | °C | Kältemittel-Flüssigtemperatur |
| `comp` | number | Hz | Verdichterdrehzahl |
| `fanrpm` | number | RPM | Lüfterdrehzahl |
| `consumption` | number | W | Aktueller Stromverbrauch |
| `hum` | number | % | Luftfeuchtigkeit (falls unterstützt) |
| `anglev` | number | ° | Vertikaler Lamellenwinkel |
| `angleh` | number | ° | Horizontaler Lamellenwinkel |
| `Whheating` | number | Wh | Kumulierter Heizenergieverbrauch |
| `Whcooling` | number | Wh | Kumulierter Kühlenergieverbrauch |
| `Whoutside` | number | Wh | Energiezähler Außengerät |
| `autot` | number | °C | Faikout-Solltemperatur (Auto-Modus) |
| `autor` | number | °C | Faikout-Hysterese |
| `autoe` | boolean | – | Faikout Auto-Modus aktiviert |
| `autop` | boolean | – | Automatisches Ein-/Ausschalten aktiviert |
| `auto0` | string | – | Timer Ausschaltzeit (z.B. `23:00`) |
| `auto1` | string | – | Timer Einschaltzeit (z.B. `06:30`) |

> Nicht alle Felder sind auf jedem Gerät vorhanden. Optionale Features (Streamer, Befeuchter, BLE-Sensor usw.) erscheinen nur, wenn sie am Gerät aktiviert sind.

---

### Schreiben: Befehls-Topics

Der Faikout verwendet je nach Funktion drei unterschiedliche Topic-Typen zum Schreiben:

| Topic | Payload | Verwendet für |
|-------|---------|--------------|
| `command/<Hostname>/control` | JSON-Objekt | Einschalten, Schwingen, Außentemperatur |
| `command/<Hostname>/<key>` | Direktwert | Betriebsmodus, Lüfterstufe, Sondermodi |
| `setting/<Hostname>/<key>` | Direktwert | Solltemperatur, Gerätekonfiguration |
| `setting/<Hostname>` | JSON-Objekt | Timer-Zeiten |

#### `command/<Hostname>/control`

Payload ist ein JSON-Objekt mit genau einem Schlüssel:

| Key | Payload-Beispiel | Beschreibung |
|-----|-----------------|--------------|
| `power` | `{"power":true}` | Klimagerät ein/aus |
| `swingv` | `{"swingv":true}` | Vertikales Schwingen ein/aus |
| `swingh` | `{"swingh":true}` | Horizontales Schwingen ein/aus |
| `env` | `{"env":21.5}` | Externe Raumtemperatur-Referenz (°C) |

> **Hinweis zu `env`:** Der Faikout verwendet diesen Wert als Temperaturreferenz für die Regelung, solange regelmäßig Updates eintreffen. Bleibt ein Update länger aus als der konfigurierte `tcontrol`-Timeout (Sekunden), fällt der Faikout auf seinen internen Sensor zurück und löscht das `control`-Flag im Status.

#### `command/<Hostname>/<key>`

Ein Topic pro Schlüssel. Boolesche Felder: `1` = ein, `0` = aus.

| Key | Werte | Beschreibung |
|-----|-------|--------------|
| `mode` | `H` · `C` · `F` · `D` · `A` | Betriebsmodus |
| `fan` | `1`–`5` · `A` · `Q` | Lüfterstufe |
| `econo` | `1` / `0` | Eco-Modus |
| `powerful` | `1` / `0` | Powerful-Modus |
| `comfort` | `1` / `0` | Comfort-Airflow |
| `demand` | `0`–`100` | Begrenzte Verdichterleistung (%) |
| `autoe` | `1` / `0` | Faikout Auto-Modus ein/aus |
| `autop` | `1` / `0` | Automatisches Ein-/Ausschalten ein/aus |
| `restart` | `1` | Faikout-Gerät neu starten |

Optional (nur verfügbar, wenn das Feature am Gerät aktiv ist):

| Key | Werte | Beschreibung |
|-----|-------|--------------|
| `streamer` | `1` / `0` | Streamer-Luftreiniger |
| `led` | `1` / `0` | Display-LEDs |
| `quiet` | `1` / `0` | Quiet-Modus (Außengerät leise) |
| `humidify` | `X` · `L` · `S` · `H` · `C` | Befeuchter-Modus |

#### `setting/<Hostname>/<key>`

Direktwert. Einstellungen bleiben über Neustarts hinweg erhalten.

| Key | Einheit | Beschreibung |
|-----|---------|--------------|
| `autot` | °C | Solltemperatur für Auto-Modus |
| `autor` | °C | Hysterese |
| `heatback` | °C | Heat-pull-back-Offset |
| `coolback` | °C | Cool-pull-back-Offset |
| `tcontrol` | s | Timeout für externe Temperaturregelung |

#### `setting/<Hostname>` – Timer-Zeiten

Timer-Ein- und Ausschaltzeiten werden als JSON-Objekt an das **Basis-Setting-Topic** gesendet (kein Key-Suffix). Die Zeitangabe muss **ohne Doppelpunkt** übergeben werden:

| Key | Payload-Beispiel | Beschreibung |
|-----|-----------------|--------------|
| `auto0` | `{"auto0":"2300"}` | Timer-Ausschaltzeit (`23:00` → `2300`) |
| `auto1` | `{"auto1":"0630"}` | Timer-Einschaltzeit (`06:30` → `0630`) |

---

<small><em>All information is provided for educational purposes based on community experience. No liability is accepted for errors, omissions, or any damage resulting from the use of this information. Always follow applicable local regulations, standards, and safety requirements. Work on electrical installations must only be carried out by qualified personnel. / Alle Informationen basieren auf Erfahrungen aus der Community und dienen ausschließlich zu Informationszwecken. Es wird keine Haftung für Fehler, Auslassungen oder Schäden übernommen, die aus der Nutzung entstehen. Einschlägige lokale Vorschriften, Normen und Sicherheitsanforderungen sind stets einzuhalten. Arbeiten an elektrischen Anlagen dürfen nur von qualifiziertem Fachpersonal durchgeführt werden.</em></small>
