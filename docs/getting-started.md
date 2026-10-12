<p align="right"><a href="https://buymeacoffee.com/raw07" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" height="40" alt="Buy Me A Coffee"></a></p>

# Getting started with Faikout / Einstieg mit dem Faikout

[English](#english) | [Deutsch](#deutsch)

← [Back to overview / Zurück zur Übersicht](../README.md)

---

## English

*This guide is a best-effort introduction based on personal experience, including subjective impressions and assessments. It makes no claim to completeness or perfection and is offered as a helpful starting point.*

- [Operating modes](#operating-modes)
  - [Mode 1: Interface mode](#mode-1-interface-mode)
  - [Mode 2: Control mode](#mode-2-control-mode)
- [WiFi setup](#wifi-setup)
  - [Via Android smartphone](#via-android-smartphone)
  - [Via Windows PC](#via-windows-pc)
- [Home Assistant integration](#home-assistant-integration)
- [External temperature sensor](#external-temperature-sensor)
- <a href="https://raw07.codeberg.page/faikout-projects/" target="_blank">Cable & Plug Reference</a>

> Note: The module was renamed from "Faikin" to "Faikout" in November 2025. Older sources or screenshots may still show "Faikin" – it is the same module.

### Operating modes

The Faikout module can be operated in two modes that differ in configuration and behaviour.

#### Mode 1: Interface mode

In interface mode the Faikout provides access to the Daikin air conditioner via its web interface and the standardised MQTT interface. The module itself makes no automatic interventions – this is an important distinction from Mode 2.

Communication with the Daikin unit is bidirectional via S21 (the serial interface used by Daikin units to communicate with their own control components). Settings from other sources (e.g. the Onecta app or the remote control) are also reflected by the Faikout.

This mode is recommended when you want to continue using the original remote control. It is also the right choice for advanced setups where an external automation system provides additional control logic on top of the Daikin's own regulation.

The upper part of the Faikout web interface represents Interface mode:

![Faikout web interface](img/webui-overview.jpeg)

#### Mode 2: Control mode

Control mode adds extra regulation functions that run "piggyback" on top of the Daikin's own regulation (which cannot be disabled). There are two sub-modes:

##### A) AutoControl

The Faikout uses its own control algorithm, which can be parameterised in the module. This makes it possible to connect an external temperature sensor so that the air conditioner reacts more realistically to the actual room temperature.

Note that because this is a second-instance controller on top of the Daikin's own regulation, relatively large setpoint jumps of several °C may be necessary before the Daikin responds at all.

As a result, the original Daikin regulation parameters are automatically overridden by the Faikout, and manual adjustments via the remote control are counterproductive. Switching on/off can still be done via the remote control, but the setpoint temperature should be adjusted exclusively via the Faikout parameters.

The lower part of the Faikout web interface represents Control mode (AutoControl):

![AutoControl mode](img/webui-autocontrol.jpeg)

##### B) Thermostat mode

In addition to AutoControl, a simpler thermostat mode is available in Mode 2. This is a basic two-point controller that regulates the setpoint (`autot`) within a band/hysteresis (`autor`), also taking an external temperature sensor into account.

<a href="img/thermostat-diagram-en.svg"><img src="img/thermostat-diagram-en.svg" width="410"></a>

The thermostat mode is often described as easier to understand and more predictable in use. To use it instead of the more complex AutoControl function, activate it in the Faikout configuration menu:

<img src="img/thermostat-switch.jpeg" width="410">

---

### WiFi setup

On first boot the Faikout opens a WiFi access point. Connect any device to this access point to enter your WiFi credentials.

#### Via Android smartphone

The Faikout access point appears in the WiFi list as `Faikin-XXXXXXXX` (or `Faikout-XXXXXXXX`):

![Android WiFi list with Faikout access point](img/android-wifi-list.jpeg)

Connect to it. The login page usually opens automatically:

![Faikout login page on Android](img/android-login-page.jpeg)

If the login page does not appear, Android may show a "Sign in to network" notification – tap it. Alternatively open the WiFi connection details:

![WiFi connection with Sign in prompt](img/android-wifi-signin.jpeg)

Then tap the **Sign in** button in the network details:

![Network details with Sign in button](img/android-network-details.jpeg)

Enter SSID and passphrase of your home network and save.

> **Tip:** If Android reports "no internet" and asks whether to keep the connection – confirm to keep it.

#### Via Windows PC

Connect to the Faikout access point in the Windows WiFi settings:

![Windows WiFi list with Faikout](img/windows-wifi-connect.jpeg)

Once connected, click the info icon (ⓘ) next to the network:

![Windows WiFi connected, info button](img/windows-wifi-info.jpeg)

In the network details, the **IPv4 default gateway** is the Faikout's IP address:

![Windows network details showing gateway IP](img/windows-network-details.jpeg)

Open that IP in a browser to reach the Faikout WiFi configuration page:

![Faikout WiFi configuration in browser](img/windows-browser-config.jpeg)

Enter SSID and passphrase, save. The Faikout restarts and is available in your network at its new IP or hostname (e.g. `34CDB038131C.local`).

> **Note:** The Faikout responds poorly to simultaneous requests from multiple devices or browser tabs. Always use only one browser tab when accessing the web interface.

---

### Home Assistant integration

In the Faikout web interface, enable the **Home Assistant** toggle:

![Home Assistant toggle in Faikout](img/ha-toggle.jpeg)

Then enter your MQTT broker details:

![MQTT settings in Faikout](img/ha-mqtt-settings.jpeg)

> **Tip:** When using the Mosquitto broker add-on, you can use your Home Assistant username and password as MQTT credentials.

Save – the Faikout registers itself automatically in Home Assistant via MQTT autodiscovery and appears as a climate entity with sensors:

![Faikout in Home Assistant](img/ha-entity.jpeg)

---

### External temperature sensor

The Faikout offers the option to use an external temperature sensor in [Mode 2: Control mode](#mode-2-control-mode) – both in **AutoControl** and **Thermostat mode**. Due to its design, the temperature sensor built into the indoor unit can only provide an approximation and rarely reflects the actual and highly individual room conditions.

There are three ways to provide an external temperature:
- **Bluetooth**: Various BLE sensors can be paired directly with the Faikout module.
- **MQTT push**: If you already have a room sensor connected to your MQTT broker, you can send its temperature value directly to the Faikout via an automation (ioBroker, Home Assistant, etc.).
- **MQTT subscribe (auto.topic)**: The Faikout subscribes directly to the sensor's MQTT topic itself – no external automation needed.

#### MQTT push

**Important:** The temperature must be sent **cyclically** (interval < 1 minute), not event-triggered. If no update arrives within that interval (configured tcontrol setting), the Faikout will stop using the external temperature and fall back to its internal sensor.

You need the hostname of your Faikout module and publish via your MQTT broker (to which the Faikout is also connected):

- **Topic:** `command/FaikoutHostname/control`
- **Payload:** `{"env": 20}` *(replace 20 with the actual temperature value)*

Even minor differences or errors in the topic or payload spelling will silently prevent this from working.

##### Example: ioBroker Blockly

![ioBroker Blockly external temperature](img/ext-temp-iobroker.png)

> **Note:** If you are using the [ioBroker Integration / Alias Generator](https://codeberg.org/RaW07/faikout-iobroker), this is already fully implemented. Simply set the alias point `ENV_SET` periodically – MQTT handling is included.

##### Example: Home Assistant

Go to **Settings → Automations & Scenes** and create a new automation:

![Home Assistant automation external temperature](img/ext-temp-ha.png)

#### MQTT subscribe (auto.topic / auto.payload)

With this method the Faikout subscribes to the sensor's MQTT topic directly – no automation layer is needed to forward the value.

Configure the following two Faikout settings:

| Setting | Value | Description |
|---|---|---|
| `auto.topic` | e.g. `zigbee2mqtt/room-sensor` | The MQTT topic the sensor publishes to |
| `auto.payload` | e.g. `temperature` | The JSON field name containing the temperature value |

If the sensor publishes a plain number (not JSON), leave `auto.payload` empty.

> **Note:** In all MQTT-based cases, the actual room temperature sensor must be available, a central MQTT broker must be installed, and the Faikout must be connected to it – this is a prerequisite for any MQTT-based function.

---

## Deutsch

*Diese Beschreibung entstand nach bestem Wissen und Gewissen inklusive möglicher subjektiver Erfahrungen und Wertungen. Sie erhebt keinen Anspruch auf Vollständigkeit oder Perfektion und versteht sich als Angebot zur Orientierung.*

- [Betriebsmodi](#betriebsmodi)
  - [Modus 1: Interfacemodus](#modus-1-interfacemodus)
  - [Modus 2: Regelbetrieb](#modus-2-regelbetrieb)
- [WLAN-Einrichtung](#wlan-einrichtung)
  - [Weg über Smartphone (Android)](#weg-über-smartphone-android)
  - [Weg über Windows-PC](#weg-über-windows-pc)
- [Home Assistant Integration](#home-assistant-integration-1)
- [Externer Temperatursensor](#externer-temperatursensor)
- <a href="https://raw07.codeberg.page/faikout-projects/" target="_blank">Kabel- & Stecker-Referenz</a>

> Hinweis: Das Modul wurde im November 2025 von "Faikin" in "Faikout" umbenannt. In älteren Quellen oder Screenshots kann noch "Faikin" auftauchen – gemeint ist dasselbe Modul.

### Betriebsmodi

Das Faikout-Modul lässt sich in zwei Modi betreiben, die man in ihrer Konfiguration und Bedienung unterscheiden sollte.

#### Modus 1: Interfacemodus

Im Interfacemodus bietet das Faikout-Modul eine ergänzende Möglichkeit auf die Daikin-Klimaanlage zuzugreifen – über die Weboberfläche und die standardisierte MQTT-Schnittstelle. Das Modul selbst führt dabei keine automatisierten Eingriffe aus – das ist ein wesentlicher Unterschied zu Modus 2.

Die Kommunikation zur Daikin-Anlage findet bidirektional über S21 statt. Auch Einstellungen, die von einer anderen Quelle stammen (z. B. der Onecta-App oder der Fernbedienung), werden vom Faikout dargestellt.

Dieser Modus ist empfehlenswert, wenn man die originale Fernbedienung weiterhin nutzen möchte. Er eignet sich auch für ausgeprägte Lösungen, bei denen eine externe Regelung zusätzlich auf die Daikin-Regelung aufgeschaltet wird.

Der obere Teil der Faikout-Weboberfläche repräsentiert den Interfacemodus:

![Faikout-Weboberfläche](img/webui-overview.jpeg)

#### Modus 2: Regelbetrieb

Das Faikout-Modul bietet die Möglichkeit, zusätzliche Regelfunktionen „huckepack" zur Daikin-Regelung (nicht abschaltbar) zu nutzen. Es gibt zwei Untermodi:

##### A) AutoControl

In dieser Regelfunktion nutzt das Faikout einen eigenen Regelalgorithmus, der im Modul parametriert werden kann. Dadurch besteht die Möglichkeit, einen externen Temperatursensor einzubinden, damit die Klimaanlage realistischer auf die tatsächliche Raumtemperatur reagiert.

Zu beachten ist, dass der Faikout-Regler teils stark eingreifen muss, damit die Daikin-Regelung überhaupt reagiert. Die Solltemperatur sollte daher ausschließlich über die Faikout-Parameter eingestellt werden – manuelle Änderungen per Fernbedienung sind kontraproduktiv.

Der untere Teil der Faikout-Weboberfläche repräsentiert den Regelbetrieb (AutoControl):

![AutoControl-Modus](img/webui-autocontrol.jpeg)

##### B) Thermostatmodus

Ergänzend zum AutoControl-Betrieb ist im Modus 2 auch ein einfacherer Thermostatmodus nutzbar. Hierbei handelt es sich um einen simplen Zweipunktregler, der den Sollwert (`autot`) in einem Band/Hysterese (`autor`) regelt.

<a href="img/thermostat-diagram.svg"><img src="img/thermostat-diagram.svg" width="410"></a>

Der Thermostatmodus wird oft als leichter verständlich und besser vorhersehbar beschrieben. Um ihn anstelle der komplexeren AutoControl-Funktion zu nutzen, ist er im Konfigurationsmenü zu aktivieren:

<img src="img/thermostat-switch.jpeg" width="410">

---

### WLAN-Einrichtung

Bei Erstinbetriebnahme öffnet das Faikout-Modul einen WLAN-Access-Point. Man verbindet sich mit einem beliebigen Gerät damit, um die WLAN-Zugangsdaten einzutragen.

#### Weg über Smartphone (Android)

Der Faikout Access Point erscheint in der WLAN-Liste als `Faikin-XXXXXXXX` (oder `Faikout-XXXXXXXX`):

![Android WLAN-Liste mit Faikout Access Point](img/android-wifi-list.jpeg)

Verbindung herstellen. Im Normalfall öffnet sich die Anmeldeseite automatisch:

![Faikout-Anmeldeseite auf Android](img/android-login-page.jpeg)

Falls die Anmeldeseite nicht erscheint, zeigt Android ggf. eine Benachrichtigung „Im WLAN anmelden". Alternativ die WLAN-Verbindungsdetails aufrufen:

![WLAN-Verbindung mit Anmelden-Hinweis](img/android-wifi-signin.jpeg)

In den Netzwerkdetails den **Anmelden**-Button antippen:

![Netzwerkdetails mit Anmelden-Button](img/android-network-details.jpeg)

SSID und Passwort des Heimnetzwerks eintragen und speichern.

> **Hinweis:** Meldet Android „keine Internetverbindung" – die Verbindung dennoch bestätigen und aufrechterhalten.

#### Weg über Windows-PC

Verbindung zum Faikout Access Point in den Windows WLAN-Einstellungen herstellen:

![Windows WLAN-Liste mit Faikout](img/windows-wifi-connect.jpeg)

Nach der Verbindung das Info-Symbol (ⓘ) neben dem Netzwerk anklicken:

![Windows WLAN verbunden, Info-Symbol](img/windows-wifi-info.jpeg)

In den Netzwerkdetails ist der **IPv4-Standardgateway** die IP-Adresse des Faikout:

![Windows Netzwerkdetails mit Gateway-IP](img/windows-network-details.jpeg)

Diese IP im Browser aufrufen – die Faikout-WLAN-Konfigurationsseite erscheint:

![Faikout WLAN-Konfiguration im Browser](img/windows-browser-config.jpeg)

SSID und Passwort eintragen, speichern. Das Faikout startet neu und ist im Netzwerk unter seiner neuen IP oder dem Hostnamen erreichbar (z. B. `34CDB038131C.local`).

> **Hinweis:** Das Faikout reagiert bei gleichzeitigen Zugriffen von mehreren Geräten oder Browser-Tabs sensibel. Immer nur einen Webzugriff gleichzeitig verwenden.

---

### Home Assistant Integration

Im Faikout-Webinterface den **Home Assistant**-Schalter aktivieren:

![Home Assistant Schalter im Faikout](img/ha-toggle.jpeg)

Anschließend die MQTT-Broker-Daten eintragen:

![MQTT-Einstellungen im Faikout](img/ha-mqtt-settings.jpeg)

> **Hinweis:** Beim Mosquitto-Broker-Add-on können die Home Assistant Zugangsdaten (Benutzername und Passwort) direkt als MQTT-Credentials verwendet werden.

Speichern – das Faikout registriert sich automatisch in Home Assistant über MQTT-Autodiscovery und erscheint als Klimaentität mit Sensoren:

![Faikout in Home Assistant](img/ha-entity.jpeg)

---

### Externer Temperatursensor

Das Faikout-Modul bietet die Möglichkeit, im Modus 2: Regelbetrieb – sowohl im **AutoControl** als auch im **Thermostatmodus** – einen externen Temperatursensor zu verwenden. Bauartbedingt kann der Temperatursensor im Innengerät nur eine Annäherung sein und entspricht selten den tatsächlichen und höchst individuellen räumlichen Gegebenheiten.

Es gibt drei Wege, eine externe Temperatur bereitzustellen:
- **Bluetooth**: Diverse BLE-Sensoren können direkt mit dem Faikout-Modul gekoppelt werden.
- **MQTT Push**: Hat man bereits einen Raumsensor am MQTT-Broker, kann man dessen Temperaturwert per Automation (ioBroker, Home Assistant etc.) direkt zum Faikout schicken.
- **MQTT Subscribe (auto.topic)**: Das Faikout abonniert das MQTT-Topic des Sensors selbst – keine externe Automation notwendig.

#### MQTT Push

**Wichtig:** Die Temperatur muss **zyklisch** gesendet werden (Intervall < 1 Minute), nicht eventgetriggert. Bleibt ein Update aus (konfigurierbare tcontrol-Einstellung), hört das Faikout eigenständig auf, die externe Temperatur zu verwenden, und fällt auf seinen internen Sensor zurück.

Dazu braucht man den Hostnamen des Faikout-Moduls und veröffentlicht über den MQTT-Broker (mit dem das Faikout verbunden ist):

- **Topic:** `command/FaikoutHostname/control`
- **Payload:** `{"env": 20}` *(20 durch den tatsächlichen Temperaturwert ersetzen)*

Kleinste Unterschiede oder Fehler in der Schreibweise von Topic oder Payload führen zum Misserfolg.

##### Beispiel: ioBroker Blockly

![ioBroker Blockly externer Temperatursensor](img/ext-temp-iobroker.png)

> **Hinweis:** Wer die [ioBroker Integration / den Alias Generator](https://codeberg.org/RaW07/faikout-iobroker) verwendet, muss nichts weiter tun – das ist bereits vollständig implementiert. Einfach den Alias-Punkt `ENV_SET` zyklisch setzen, die MQTT-Verarbeitung ist enthalten.

##### Beispiel: Home Assistant

Unter **Einstellungen → Automationen & Szenen** eine neue Automation erstellen:

![Home Assistant Automation externer Temperatursensor](img/ext-temp-ha.png)

#### MQTT Subscribe (auto.topic / auto.payload)

Bei dieser Methode abonniert das Faikout das MQTT-Topic des Sensors selbst – kein Automations-Layer zum Weiterleiten des Werts notwendig.

Folgende zwei Faikout-Einstellungen konfigurieren:

| Einstellung | Wert | Beschreibung |
|---|---|---|
| `auto.topic` | z.B. `zigbee2mqtt/raum-sensor` | Das MQTT-Topic, auf dem der Sensor veröffentlicht |
| `auto.payload` | z.B. `temperature` | Der JSON-Feldname, der den Temperaturwert enthält |

Veröffentlicht der Sensor eine reine Zahl (kein JSON), `auto.payload` leer lassen.

> **Hinweis:** In allen MQTT-basierten Fällen muss der tatsächliche Raumsensor verfügbar sein, ein zentraler MQTT-Broker installiert sein und das Faikout dort verbunden sein – das ist obligatorisch für jede MQTT-Funktion.

