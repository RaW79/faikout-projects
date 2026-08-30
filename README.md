# Faikout – Projekte & Integrationen

Diese Seite gibt einen Überblick über eigene Projekte rund um den **Faikout** – ein ESP32-Board zur lokalen Steuerung von Daikin-Klimaanlagen über den S21-Serviceanschluss, ohne Cloud.

Weitere Informationen zum Faikout selbst: [codeberg.org/RevK/ESP32-Faikout](https://codeberg.org/RevK/ESP32-Faikout)

---

## Projekte

### ESP32-Faikout-ETH01EVO
Firmware-Fork mit früher Ethernet-Unterstützung via **ESP32-C3 ETH01 EVO**. Entstand zu einem Zeitpunkt, als der Faikout noch keine Ethernet-Lösung bot.

→ [codeberg.org/RaW07/ESP32-Faikout-ETH01EVO](https://codeberg.org/RaW07/ESP32-Faikout-ETH01EVO)

---

### ESP32-Faikushi
Firmware-Port für **Mitsubishi Electric** Klimaanlagen (CN105-Anschluss) auf der Faikout-Hardware. Basiert auf mitsubishi2MQTT, angepasst auf den Faikout-Pinout.

→ [codeberg.org/RaW07/ESP32-Faikushi](https://codeberg.org/RaW07/ESP32-Faikushi)

---

### faikout-iobroker
Automatischer **ioBroker Alias-Generator**: Ein JavaScript-Adapter-Script das sich per HTTP mit dem Faikout verbindet, aktive Features erkennt und alle Datenpunkte unter `alias.0.*` anlegt – inklusive Lese-/Schreibkonvertierung für das MQTT-JSON.

→ [codeberg.org/RaW07/faikout-iobroker](https://codeberg.org/RaW07/faikout-iobroker)

---

### faikout-openccu
**Homematic-Integration** via openCCU. Enthält einen CCU-Flow zur Feuchtigkeits- und Taupunktregelung mit dem Faikout als Aktor.

→ [codeberg.org/RaW07/faikout-openccu](https://codeberg.org/RaW07/faikout-openccu)
