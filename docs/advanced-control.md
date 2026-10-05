<p align="right"><a href="https://buymeacoffee.com/raw07" target="_blank"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" height="40" alt="Buy Me A Coffee"></a></p>

# Advanced Control for Several Automation Systems / Erweiterte Regelung für verschiedene Automationssysteme

[English](#english) | [Deutsch](#deutsch)

← [Back to overview / Zurück zur Übersicht](../README.md)

---

## English

*This guide is a best-effort introduction based on personal experience, including subjective impressions and assessments. It makes no claim to completeness or perfection and is offered as a helpful starting point.*

Advanced control scripts and integrations for automating Faikout-based Daikin systems beyond the built-in thermostat mode.

### ioBroker

Modern Daikin units support a **demand control** feature that allows the compressor output to be actively limited — a capability that is neither exposed by the standard Daikin interface nor utilised by the Faikout's built-in thermostat mode. This script unlocks that potential from ioBroker.

The approach keeps the Faikout's Auto-Control running in thermostat mode as usual, handling on/off switching based on room temperature. On top of that, ioBroker continuously adjusts the unit's heating demand (compressor output in %) to achieve the smoothest and most efficient operation possible: the system runs longer at lower output rather than cycling on and off at full power.

The basis for the required heating output is a **characteristic curve (Heizkennlinie)** that maps the current outdoor temperature to a suitable demand value — modelling the individual heating load of the room. This curve can and should be adapted to suit your specific building, insulation, and exposure. Additional boost steps handle situations where the room falls significantly behind the target temperature.

Before using the script, two things need to be aligned:
- The **Faikout base settings** (in particular `autot`, `autor`, `heatback`, `heatover`) must be configured appropriately.
- The **configuration block at the top of the script** contains all adjustable parameters and must be reviewed before the first run.

---

### openHAB

coming soon

---

## Deutsch

*Dieser Leitfaden basiert auf persönlichen Erfahrungen und erhebt keinen Anspruch auf Vollständigkeit oder Fehlerfreiheit.*

Erweiterte Regelungsskripte und Integrationen zur Automatisierung Faikout-basierter Daikin-Systeme über den integrierten Thermostatmodus hinaus.

### ioBroker

Moderne Daikin-Geräte unterstützen eine **Bedarfsregelung (Demand Control)**, mit der die Kompressorleistung aktiv begrenzt werden kann – eine Funktion, die weder über die Standard-Daikin-Schnittstelle zugänglich ist noch vom integrierten Faikout-Thermostatmodus genutzt wird. Dieses Skript erschließt dieses Potenzial aus ioBroker heraus.

Der Ansatz lässt den Faikout-Auto-Control weiterhin im Thermostatmodus arbeiten – er übernimmt wie gewohnt das Ein- und Ausschalten auf Basis der Raumtemperatur. Zusätzlich passt ioBroker den Heiz-Demand (Kompressorleistung in %) kontinuierlich an, um einen möglichst gleichmäßigen und sparsamen Betrieb zu erreichen: Die Anlage läuft länger auf niedrigerer Leistung, anstatt mit voller Leistung zu takten.

Grundlage für den erforderlichen Heizbedarf ist eine **Heizkennlinie**, die die aktuelle Außentemperatur auf einen geeigneten Demand-Wert abbildet und damit den individuellen Wärmebedarf des Raumes nachbildet. Diese Kurve kann und sollte an das jeweilige Gebäude, die Dämmung und die Ausrichtung angepasst werden. Zusätzliche Boost-Stufen greifen ein, wenn die Raumtemperatur deutlich unter den Sollwert fällt.

Vor der Nutzung des Skripts sind zwei Dinge abzustimmen:
- Die **Faikout-Grundeinstellungen** (insbesondere `autot`, `autor`, `heatback`, `heatover`) müssen passend konfiguriert sein.
- Der **Konfigurationsbereich am Anfang des Skripts** enthält alle anpassbaren Parameter und muss vor dem ersten Start geprüft werden.

---

### openHAB

coming soon
