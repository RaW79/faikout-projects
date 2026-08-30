# Faikout – Projects & Integrations / Projekte & Integrationen

[English](#english) | [Deutsch](#deutsch)

---

## English

This page provides an overview of personal projects built around the **Faikout** – an ESP32 board that controls Daikin air conditioners locally via the S21 service connector, without any cloud dependency.

More information about the Faikout itself: [codeberg.org/RevK/ESP32-Faikout](https://codeberg.org/RevK/ESP32-Faikout)

### Guides & Resources

#### [Getting started with Faikout](docs/getting-started.md)
[Operating modes](docs/getting-started.md#operating-modes) · [WiFi setup](docs/getting-started.md#wifi-setup) · [Home Assistant integration](docs/getting-started.md#home-assistant-integration)

---

### Projects

#### faikout-iobroker
Automatic **ioBroker alias generator**: a JavaScript adapter script that connects to the Faikout via HTTP, detects active features, and creates all data points under `alias.0.*` – including read/write converters for the MQTT JSON.

→ [codeberg.org/RaW07/faikout-iobroker](https://codeberg.org/RaW07/faikout-iobroker)

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

Diese Seite gibt einen Überblick über eigene Projekte rund um den **Faikout** – ein ESP32-Board zur lokalen Steuerung von Daikin-Klimaanlagen über den S21-Serviceanschluss, ohne Cloud.

Weitere Informationen zum Faikout selbst: [codeberg.org/RevK/ESP32-Faikout](https://codeberg.org/RevK/ESP32-Faikout)

### Guides & Resources

#### [Einstieg mit dem Faikout](docs/getting-started.md#deutsch)
[Betriebsmodi](docs/getting-started.md#betriebsmodi) · [WLAN-Einrichtung](docs/getting-started.md#wlan-einrichtung) · [Home Assistant Integration](docs/getting-started.md#home-assistant-integration-1)

---

### Projekte

#### faikout-iobroker
Automatischer **ioBroker Alias-Generator**: Ein JavaScript-Adapter-Script das sich per HTTP mit dem Faikout verbindet, aktive Features erkennt und alle Datenpunkte unter `alias.0.*` anlegt – inklusive Lese-/Schreibkonvertierung für das MQTT-JSON.

→ [codeberg.org/RaW07/faikout-iobroker](https://codeberg.org/RaW07/faikout-iobroker)

#### faikout-openccu
**Homematic-Integration** via openCCU. Enthält einen CCU-Flow zur Feuchtigkeits- und Taupunktregelung mit dem Faikout als Aktor.

→ [codeberg.org/RaW07/faikout-openccu](https://codeberg.org/RaW07/faikout-openccu)

#### ESP32-Faikout-ETH01EVO
Firmware-Fork mit früher Ethernet-Unterstützung via **ESP32-C3 ETH01 EVO**. Entstand zu einem Zeitpunkt, als der Faikout noch keine Ethernet-Lösung bot.

→ [codeberg.org/RaW07/ESP32-Faikout-ETH01EVO](https://codeberg.org/RaW07/ESP32-Faikout-ETH01EVO)

#### ESP32-Faikushi
Firmware-Port für **Mitsubishi Electric** Klimaanlagen (CN105-Anschluss) auf der Faikout-Hardware. Basiert auf mitsubishi2MQTT, angepasst auf den Faikout-Pinout.

→ [codeberg.org/RaW07/ESP32-Faikushi](https://codeberg.org/RaW07/ESP32-Faikushi)
