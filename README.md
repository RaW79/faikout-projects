<p align="right"><a href="https://buymeacoffee.com/raw07" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" height="40" alt="Buy Me A Coffee"></a></p>

# Faikout – Projects & Integrations / Projekte & Integrationen

[English](#english) | [Deutsch](#deutsch)

---

## English

This page provides an overview of personal projects built and experiences made around the **Faikout** – an ESP32 board that controls Daikin air conditioners locally via the S21 service connector, without any cloud dependency.

More information about the Faikout itself: [codeberg.org/RevK/ESP32-Faikout](https://codeberg.org/RevK/ESP32-Faikout)

### Guides & Resources

<table><tr><td valign="top">

**Getting started with Faikout**
- [Operating modes](docs/getting-started.md#operating-modes)
- [WiFi setup](docs/getting-started.md#wifi-setup)
- [Home Assistant integration](docs/getting-started.md#home-assistant-integration)
- [External temperature sensor](docs/getting-started.md#external-temperature-sensor)
- <a href="https://RaW07.codeberg.page/faikout-projects/" target="_blank">Cable & Plug Reference</a>

</td><td valign="top">

**Disassembly & Installation Hints**
- [Daikin Stylish (FTXA / FTXTA)](docs/disassembly-stylish.md)
- [Daikin Perfera (FTXM-A / CTXM / ATXM)](docs/disassembly-perfera.md)
- [Daikin Comfora (FTXP-N)](docs/disassembly-comfora.md)
- [Daikin Emura 3 (FTXJ-A2)](docs/disassembly-emura3.md)
- [Daikin Emura 2 (FTXJ-M / FTXG-L)](docs/disassembly-emura2.md)

</td><td valign="top">

**BLE Temperature Sensors – Flashing Guides**
- [Xiaomi Mijia T&H Monitor 2 (LYWSD03MMC)](docs/ble-sensor.md#english)
- [Xiaomi Mijia T&H Monitor 3 Mini (MJWSD06MMC)](docs/ble-sensor.md#mjwsd06mmc-english)

**More Advanced Control**
- [Advanced control for several automation systems](docs/advanced-control.md)

</td></tr></table>

---

### Projects

#### faikout-iobroker
Automatic **ioBroker alias generator**: a JavaScript adapter script that connects to the Faikout via HTTP, detects active features, and creates all data points under `alias.0.*` – including read/write converters for the MQTT JSON.

→ [codeberg.org/RaW07/faikout-iobroker](https://codeberg.org/RaW07/faikout-iobroker)

#### faikout-NodeRed
Ready-to-import **Node-RED flow** for universal MQTT integration. Covers all status fields and control commands, structured in six groups: configuration, status, commands, settings, external temperature sensor, and diagnostics.

→ [codeberg.org/RaW07/faikout-NodeRed](https://codeberg.org/RaW07/faikout-NodeRed)

#### faikout-openccu
**Homematic integration** via openCCU. Provides a CCU flow for humidity and dew point control using the Faikout as actuator.

→ [codeberg.org/RaW07/faikout-openccu](https://codeberg.org/RaW07/faikout-openccu)

#### ESP32-Faikout-ETH01EVO
Firmware fork adding early Ethernet support via the **ESP32-C3 ETH01 EVO** board. Created at a time when the Faikout had no Ethernet solution yet.

→ [codeberg.org/RaW07/ESP32-Faikout-ETH01EVO](https://codeberg.org/RaW07/ESP32-Faikout-ETH01EVO)

#### ESP32-Faikushi
Firmware port for **Mitsubishi Electric** air conditioners (CN105 connector) running on Faikout hardware. Based on mitsubishi2MQTT, adapted to the Faikout pinout.

→ [codeberg.org/RaW07/ESP32-Faikushi](https://codeberg.org/RaW07/ESP32-Faikushi)

---

## Deutsch

Diese Seite gibt einen Überblick über eigene Projekte und gesammelte Erfahrungen rund um den **Faikout** – ein ESP32-Board zur lokalen Steuerung von Daikin-Klimaanlagen über den S21-Serviceanschluss, ohne Cloud.

Weitere Informationen zum Faikout selbst: [codeberg.org/RevK/ESP32-Faikout](https://codeberg.org/RevK/ESP32-Faikout)

### Guides & Resources

<table><tr><td valign="top">

**Einstieg mit dem Faikout**
- [Betriebsmodi](docs/getting-started.md#betriebsmodi)
- [WLAN-Einrichtung](docs/getting-started.md#wlan-einrichtung)
- [Home Assistant Integration](docs/getting-started.md#home-assistant-integration-1)
- [Externer Temperatursensor](docs/getting-started.md#externer-temperatursensor)
- <a href="https://RaW07.codeberg.page/faikout-projects/" target="_blank">Kabel- & Stecker-Referenz</a>

</td><td valign="top">

**Montagehinweise**
- [Daikin Stylish (FTXA / FTXTA)](docs/disassembly-stylish.md#deutsch)
- [Daikin Perfera (FTXM-A / CTXM / ATXM)](docs/disassembly-perfera.md#deutsch)
- [Daikin Comfora (FTXP-N)](docs/disassembly-comfora.md#deutsch)
- [Daikin Emura 3 (FTXJ-A2)](docs/disassembly-emura3.md#deutsch)
- [Daikin Emura 2 (FTXJ-M / FTXG-L)](docs/disassembly-emura2.md#deutsch)

</td><td valign="top">

**BLE-Temperatursensoren – Flashing Guides**
- [Xiaomi Mijia T&H Monitor 2 (LYWSD03MMC)](docs/ble-sensor.md#deutsch)
- [Xiaomi Mijia T&H Monitor 3 Mini (MJWSD06MMC)](docs/ble-sensor.md#mjwsd06mmc-deutsch)

**Erweiterte Regelung**
- [Erweiterte Regelung für verschiedene Automationssysteme](docs/advanced-control.md)

</td></tr></table>

---

### Projekte

#### faikout-iobroker
Automatischer **ioBroker Alias-Generator**: Ein JavaScript-Adapter-Script das sich per HTTP mit dem Faikout verbindet, aktive Features erkennt und alle Datenpunkte unter `alias.0.*` anlegt – inklusive Lese-/Schreibkonvertierung für das MQTT-JSON.

→ [codeberg.org/RaW07/faikout-iobroker](https://codeberg.org/RaW07/faikout-iobroker)

#### faikout-NodeRed
Importfertiger **Node-RED Flow** für universelle MQTT-Anbindung. Enthält alle Statusfelder und Steuerbefehle, strukturiert in sechs Gruppen: Konfiguration, Statusempfang, Befehle, Einstellungen, Externer Temperatursensor und Diagnose.

→ [codeberg.org/RaW07/faikout-NodeRed](https://codeberg.org/RaW07/faikout-NodeRed)

#### faikout-openccu
**Homematic-Integration** via openCCU. Enthält einen CCU-Flow zur Feuchtigkeits- und Taupunktregelung mit dem Faikout als Aktor.

→ [codeberg.org/RaW07/faikout-openccu](https://codeberg.org/RaW07/faikout-openccu)

#### ESP32-Faikout-ETH01EVO
Firmware-Fork mit früher Ethernet-Unterstützung via **ESP32-C3 ETH01 EVO**. Entstand zu einem Zeitpunkt, als der Faikout noch keine Ethernet-Lösung bot.

→ [codeberg.org/RaW07/ESP32-Faikout-ETH01EVO](https://codeberg.org/RaW07/ESP32-Faikout-ETH01EVO)

#### ESP32-Faikushi
Firmware-Port für **Mitsubishi Electric** Klimaanlagen (CN105-Anschluss) auf der Faikout-Hardware. Basiert auf mitsubishi2MQTT, angepasst auf den Faikout-Pinout.

→ [codeberg.org/RaW07/ESP32-Faikushi](https://codeberg.org/RaW07/ESP32-Faikushi)

---

<small><em>All information is provided for educational purposes based on community experience. No liability is accepted for errors, omissions, or any damage resulting from the use of this information. Always follow applicable local regulations, standards, and safety requirements. Work on electrical installations must only be carried out by qualified personnel. / Alle Informationen basieren auf Erfahrungen aus der Community und dienen ausschließlich zu Informationszwecken. Es wird keine Haftung für Fehler, Auslassungen oder Schäden übernommen, die aus der Nutzung entstehen. Einschlägige lokale Vorschriften, Normen und Sicherheitsanforderungen sind stets einzuhalten. Arbeiten an elektrischen Anlagen dürfen nur von qualifiziertem Fachpersonal durchgeführt werden.</em></small>
