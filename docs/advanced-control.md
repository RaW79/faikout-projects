<p align="right"><a href="https://buymeacoffee.com/raw07" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" height="40" alt="Buy Me A Coffee"></a></p>

# Advanced Control for Several Automation Systems / Erweiterte Regelung für verschiedene Automationssysteme

[English](#english) | [Deutsch](#deutsch)

← [Back to overview / Zurück zur Übersicht](../README.md)

---

## English

*This guide is a best-effort introduction based on personal experience, including subjective impressions and assessments. It makes no claim to completeness or perfection and is offered as a helpful starting point.*

Advanced control scripts and integrations for automating Faikout-based Daikin systems beyond the built-in thermostat mode.

### ioBroker

Modern Daikin units support a **demand control** feature that allows the compressor output to be actively limited — a capability that is neither conveniently nor automatically usable through the standard Daikin interface, nor taken into account by the Faikout in any control loop. This script unlocks that potential from ioBroker.

The approach keeps the Faikout's Auto-Control running in thermostat mode as usual, handling on/off switching based on room temperature. On top of that, ioBroker continuously adjusts the unit's heating demand (compressor output in %) to achieve the smoothest and most efficient operation possible: the system runs longer at lower output rather than cycling on and off at full power.

The basis for the required heating output is a **characteristic curve (Heizkennlinie)** that maps the current outdoor temperature to a suitable demand value — modelling the individual heating load of the room. This curve can and should be adapted to suit your specific building, insulation, and exposure. Additional boost steps handle situations where the room falls significantly behind the target temperature.

#### Faikout Settings Used in This Setup

| Parameter | Value | Effect |
|---|---|---|
| `heatover` | 0°C | No overshoot added to the upper setpoint — Faikout heats exactly to `autot + autor`, no higher |
| `heatback` | 3°C | When idle, the Daikin target temp is set 3°C below the lower band edge — prevents brief re-triggering |
| `tempnoflap` | 0s | No minimum interval between setpoint changes — ioBroker demand updates take effect immediately |
| `lockmode` | active | Faikout thermostat never switches the unit from heat to cool mode automatically — mode control stays with the user |

#### Available Alias Data Points

All data points are created automatically by the [faikout-iobroker](https://codeberg.org/RaW07/faikout-iobroker) alias generator.

---

### openHAB

coming soon

---

## Deutsch

*Dieser Leitfaden basiert auf persönlichen Erfahrungen und erhebt keinen Anspruch auf Vollständigkeit oder Fehlerfreiheit.*

Erweiterte Regelungsskripte und Integrationen zur Automatisierung Faikout-basierter Daikin-Systeme über den integrierten Thermostatmodus hinaus.

### ioBroker

Moderne Daikin-Geräte unterstützen eine **Bedarfsregelung (Demand Control)**, mit der die Kompressorleistung aktiv begrenzt werden kann – eine Funktion, die weder über die Standard-Daikin-Schnittstelle komfortabel und automatisiert nutzbar ist noch vom Faikout in eine Regelung berücksichtigt wird. Dieses Skript erschließt dieses Potenzial aus ioBroker heraus.

Der Ansatz lässt den Faikout-Auto-Control weiterhin im Thermostatmodus arbeiten – er übernimmt wie gewohnt das Ein- und Ausschalten auf Basis der Raumtemperatur. Zusätzlich passt ioBroker den Heiz-Demand (Kompressorleistung in %) kontinuierlich an, um einen möglichst gleichmäßigen und sparsamen Betrieb zu erreichen: Die Anlage läuft länger auf niedrigerer Leistung, anstatt mit voller Leistung zu takten.

Grundlage für den erforderlichen Heizbedarf ist eine **Heizkennlinie**, die die aktuelle Außentemperatur auf einen geeigneten Demand-Wert abbildet und damit den individuellen Wärmebedarf des Raumes nachbildet. Diese Kurve kann und sollte an das jeweilige Gebäude, die Dämmung und die Ausrichtung angepasst werden. Zusätzliche Boost-Stufen greifen ein, wenn die Raumtemperatur deutlich unter den Sollwert fällt.

#### Verwendete Faikout-Einstellungen

| Parameter | Wert | Wirkung |
|---|---|---|
| `heatover` | 0°C | Kein Überschwingen am oberen Sollwert – Faikout heizt genau bis `autot + autor`, nicht darüber hinaus |
| `heatback` | 3°C | Im Ruhezustand wird der Daikin-Sollwert 3°C unter die untere Bandgrenze gesetzt – verhindert kurzzeitiges Wiedereinschalten |
| `tempnoflap` | 0s | Kein Mindestabstand zwischen Sollwertänderungen – ioBroker-Demand-Aktualisierungen wirken sofort |
| `lockmode` | aktiv | Der Faikout-Thermostat wechselt nie selbstständig von Heizen auf Kühlen – die Modussteuerung verbleibt beim Nutzer |

#### Verfügbare Alias-Datenpunkte

Alle Datenpunkte werden automatisch durch den [faikout-iobroker](https://codeberg.org/RaW07/faikout-iobroker) Alias-Generator angelegt.

---

### openHAB

coming soon
