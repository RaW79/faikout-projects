# MQTT Generic Device Schema Publication Specification

**Document identifier:** FAIKOUT-SPEC-MQTT-SCHEMA-001  
**Revision:** Draft 0.2  
**Date:** September 2026  
**Author:** RaW07  
**Status:** Draft – For Review  

---

## Table of Contents

1. Abstract
2. Introduction
3. Scope and Applicability
4. Referenced Documents and Standards
5. Terminology and Definitions
6. Requirements Overview
7. Schema Topic Specification
8. Schema Payload Format
9. Field Descriptor Specification
10. Data Type Definitions
11. Command Interface Specification
12. Feature Enablement and Configuration Parameters
13. Deployment Scenarios and Use Cases
14. Test Scenarios and Acceptance Criteria
15. Implementation Considerations
16. Interoperability Guidelines
17. Security Considerations
18. Error Handling and Edge Cases
19. Appendix A – Prototype Evidence
20. Appendix B – Complete Field Reference
21. Appendix C – Example Payloads
22. Appendix D – Glossary

---

## 1. Abstract

This document specifies a mechanism by which MQTT-connected embedded devices may publish a machine-readable description of their operational capabilities, available data fields, data types, value constraints, and command interface to a well-known retained MQTT topic hereinafter referred to as the Schema Topic.

The primary objective of this specification is to enable automation platforms, integration frameworks, and third-party software systems to autonomously discover and configure device integrations at runtime, without prior knowledge of device-specific topic structures, payload schemas, or field semantics. A conforming implementation eliminates the requirement for static, manually maintained configuration in consumer software and provides a robust foundation for dynamic integration assembly.

This specification is explicitly platform-agnostic. While the motivating use case is the Faikout HVAC controller firmware (ESP32-based, RevK framework), the schema format defined herein is applicable to any MQTT-publishing device without modification.

The need for this specification arises directly from real-world deployments: without a machine-readable schema, each automation platform requires its own dedicated integration generator. As of this writing, working generators exist for **ioBroker** (`faikout_alias_generator_en.js`), **openHAB** (`faikout_generator.js`), **Node-RED** (`faikout-nodered-flow.json`), and **Homematic CCU / openCCU** (`faikout-flow.json`). All four independently query the Faikout HTTP API or parse its web interface to detect active features — a fragile workaround that a published schema topic would eliminate.

---

## 2. Introduction

### 2.1 Background

The MQTT protocol has become a de facto standard transport layer for IoT device communication. Its publish-subscribe architecture, lightweight framing, and broad broker availability have driven adoption across a wide range of embedded device categories, from environmental sensors to complex HVAC controllers. However, the MQTT specification itself defines only the transport mechanism and makes no provision for describing the semantic content of messages. Device vendors are therefore free to define their own topic hierarchies, payload formats, and field naming conventions, resulting in a deeply fragmented ecosystem.

In practice, this fragmentation imposes a recurring cost on integration authors. For each combination of device firmware and automation platform, a dedicated integration must be developed, tested, and maintained. When firmware updates alter field names, add new capabilities, or deprecate existing ones, integrations break silently — devices continue to publish on the MQTT broker but consumers receive data they cannot interpret or miss data they do not know to request.

### 2.2 The Fragmentation Problem in Practice

The Faikout HVAC controller (ESP32-based firmware by RevK, https://codeberg.org/RevK/ESP32-Faikout) is a concrete example of this problem. The device publishes status data as a JSON object to `state/<device-id>/status` and accepts commands on multiple `command/<device-id>/<topic>` paths. It also supports Home Assistant MQTT Discovery via a separately toggleable setting.

As of September 2026, integration with non-Home-Assistant platforms requires manual effort:

| Platform | Integration approach | Source |
|---|---|---|
| **ioBroker** | Generator script queries Faikout HTTP interface, detects active fields, creates alias data points | `faikout_alias_generator_en.js` |
| **openHAB** | Generator rule runs on startup, queries HTTP API, creates Things/Items/Links via REST API | `faikout_generator.js` |
| **Node-RED** | Import-ready flow with manual device ID configuration, includes diagnostics group | `faikout-nodered-flow.json` |
| **Homematic CCU (openCCU)** | Node-RED flow on Redmatic, maps MQTT fields to CCU system variables, idempotent setup | `faikout-flow.json` |

Every one of these integrations implements its own feature-detection logic. The ioBroker generator (lines 102–141 of `faikout_alias_generator_en.js`) performs two HTTP requests to the device — one to the root page to scrape field names from JavaScript source (`o.fieldname` pattern), one to the extras settings page to detect disabled features and BLE availability. The openHAB generator queries the Faikout HTTP API endpoint `/api`. This coupling to the HTTP interface means any firmware change to the web UI can silently break all generator scripts.

A published MQTT schema topic eliminates this dependency entirely.

### 2.3 The Home Assistant Discovery Problem

Home Assistant's MQTT Discovery protocol has achieved widespread adoption and represents the most mature attempt to address this fragmentation within the home automation space. However, it is fundamentally unsuitable as a generic device description mechanism for the following reasons:

**Tight coupling to Home Assistant entity model:** The discovery payload references Home Assistant-specific entity types (`climate`, `sensor`, `switch`, `select`) and their configuration keys. These concepts have no direct equivalent in other platforms and cannot be mechanically translated without platform-specific mapping logic.

**Component-centric rather than field-centric:** Home Assistant discovery requires one discovery message per entity component. A single device with 17+ fields requires 17+ separate discovery publications. The schema mechanism proposed here publishes a single document describing the complete field set.

**HA-specific transformations:** Discovery payloads reference `value_template` expressions using Home Assistant's Jinja2 template syntax. These are not portable to other platforms.

**No intrinsic writability declaration:** Writability is implied through the presence or absence of a `command_topic` field per entity. There is no normative field stating "this field is read-only" in a machine-parseable way applicable outside HA.

### 2.4 Existing Standards Evaluated

The following existing specifications were evaluated as potential bases for this work:

#### 2.4.1 Homie Convention (v4.0)

The Homie Convention defines a structured MQTT topic hierarchy under which device properties, nodes, and attributes are published via mandatory `$` prefix attributes at device, node, and property levels. For a device with 35 fields, a fully conforming Homie implementation would require publication to approximately 175 distinct topics. This overhead is disproportionate for constrained firmware environments. Furthermore, Homie adoption in production firmware remains limited.

#### 2.4.2 W3C Web of Things (WoT) Thing Description

The W3C WoT Thing Description specification provides a comprehensive semantic device model with JSON-LD encoding. Its scope and expressiveness exceed the requirements of the present use case by a significant margin. The JSON-LD dependency requires a conforming consumer to implement or embed a JSON-LD processor, which is unreasonable for lightweight automation platform integrations.

#### 2.4.3 AsyncAPI

AsyncAPI is a specification format for event-driven APIs analogous to OpenAPI for REST interfaces. It is designed as a design-time documentation format rather than a runtime discovery mechanism and is not intended to be published to MQTT topics by devices themselves.

#### 2.4.4 Conclusion

None of the evaluated standards provides a suitable basis for a runtime, MQTT-native, firmware-embeddable device capability description. This specification defines a minimal, self-contained format optimised for low payload size, implementation simplicity, and immediate consumer utility.

### 2.5 Design Principles

1. **Minimal payload size:** Compact enough for practical retention and repeated transmission over constrained MQTT connections.
2. **Implementation simplicity:** A conforming firmware implementation should require fewer than 150 lines of C code.
3. **Consumer self-sufficiency:** A consumer receiving only the schema payload and the status payload must have sufficient information to build a complete integration without additional queries or documentation.
4. **No external dependencies:** The schema format must not reference external schemas, namespaces, or registries.
5. **Deterministic behaviour:** The schema must accurately reflect the device's current capabilities. Fields not present in the schema must not appear in status or command payloads.

### 2.6 Prototype Evidence

This specification is grounded in a working prototype. As documented in Codeberg issue revk/ESP32-Faikout#1085 (opened 2026-08-23), a `send_mqtt_schema()` function was implemented in the Faikout firmware and validated on real hardware. The firmware settings page of the prototype device shows the resulting configuration toggle:

> **"MQTT schema topic"** — "Publish MQTT schema topic" [toggle: enabled]

The toggle name corresponds to the firmware configuration parameter `mqttschema` defined in Section 12. See Appendix A for the prototype firmware settings screenshot and the prototype JSON payload as proposed in the issue.

---

## 3. Scope and Applicability

### 3.1 In Scope

This specification defines:

- The MQTT topic structure for schema publication
- The retention and QoS requirements for schema messages
- The JSON payload format for the schema document
- The structure and semantics of field descriptor objects
- The enumeration and definition of supported data types
- The command payload format as it relates to schema-described fields
- Configuration parameters governing schema publication behaviour
- Acceptance test scenarios for conformance validation
- Interoperability guidelines for consumer implementations

### 3.2 Out of Scope

This specification does not define:

- The content or format of status payloads (device-specific)
- Broker authentication or authorisation mechanisms
- Device provisioning or network configuration
- Firmware update mechanisms
- Any aspect of the Home Assistant MQTT Discovery protocol
- Consumer-side integration logic beyond what is necessary to interpret the schema

### 3.3 Applicability

This specification is applicable to any MQTT-publishing embedded device that satisfies the following prerequisites:

- The device publishes status data as a JSON object to a single MQTT topic
- The device accepts commands as JSON objects or plain strings on one or more MQTT topics
- The device has a stable unique identifier suitable for use as a topic path segment

---

## 4. Referenced Documents and Standards

| Reference | Title | Source |
|-----------|-------|--------|
| RFC 2119  | Key words for use in RFCs to Indicate Requirement Levels | IETF |
| RFC 8259  | The JavaScript Object Notation (JSON) Data Interchange Format | IETF |
| MQTT 3.1.1 | MQTT Version 3.1.1 | OASIS |
| MQTT 5.0  | MQTT Version 5.0 | OASIS |
| IEEE 754  | Standard for Floating-Point Arithmetic | IEEE |
| revk/ESP32-Faikout | Faikout firmware source | https://codeberg.org/revk/ESP32-Faikout |
| Issue #1085 | Generic MQTT Schema/Discovery Topic | https://codeberg.org/revk/ESP32-Faikout/issues/1085 |

---

## 5. Terminology and Definitions

For the purposes of this specification the following terms and definitions apply.

**5.1 Automation Platform**  
A software system that integrates multiple IoT devices and provides automation, monitoring, and control capabilities. Examples: openHAB, ioBroker, Node-RED, Home Assistant, Homematic CCU (via Redmatic/openCCU).

**5.2 Broker**  
An MQTT message broker. Examples: Mosquitto, EMQX, HiveMQ.

**5.3 Channel**  
The representation of a single device field within an automation platform's data model. In openHAB: a Thing Channel linked to an Item. In ioBroker: a State object under `alias.0`. In Node-RED: a message property.

**5.4 Command**  
A JSON object or plain string value published by a consumer to a device command topic to change a writable field value.

**5.5 Command Topic**  
The MQTT topic on which the device subscribes to receive command payloads. May be a single JSON control topic or individual per-field topics — see Section 11.

**5.6 Consumer**  
Any software system that subscribes to the Schema Topic to read and interpret the schema payload. Typically an automation platform integration generator or adapter.

**5.7 Device**  
An embedded system that connects to the MQTT broker, publishes status data, and optionally accepts command messages.

**5.8 Device Identifier**  
A string uniquely identifying the device across all its MQTT topics. Typically the MAC address in uppercase hexadecimal without delimiters (e.g. `9C139EEF6D28`) or a configured hostname.

**5.9 Feature Detection**  
The process of determining which fields are active on a specific device unit. Without a schema topic, consumers perform feature detection by querying the device's HTTP interface — a brittle workaround this specification replaces.

**5.10 Field**  
A discrete data point exposed by the device. Each field has a key, a data type, a writability attribute, and optionally a set of permitted values or numeric constraints.

**5.11 Field Descriptor**  
A JSON object within the schema payload's `fields` array that describes a single field.

**5.12 Integration Generator**  
A software component, typically running on the automation platform, that reads the schema payload and automatically creates the platform-specific configuration objects required to integrate the device.

**5.13 Key**  
The JSON property name used to identify a field in the status payload and command payload. Keys are case-sensitive ASCII strings.

**5.14 MQTT**  
Message Queuing Telemetry Transport. A lightweight publish-subscribe messaging protocol.

**5.15 QoS**  
Quality of Service. MQTT delivery guarantee: QoS 0 (at most once), QoS 1 (at least once), QoS 2 (exactly once).

**5.16 Retained Message**  
An MQTT message published with the `retain` flag set to `true`. The broker stores and delivers it immediately to any new subscriber.

**5.17 Schema Topic**  
The MQTT topic to which the device publishes its schema payload.

**5.18 Status Topic**  
The MQTT topic on which the device publishes status JSON objects. For Faikout firmware: `state/<device-id>/status`.

**5.19 Writability**  
The attribute of a field indicating whether it accepts commands. `rw: true` = writable; `rw: false` = read-only.

---

## 6. Requirements Overview

### 6.1 Device Requirements (D-REQ)

| ID | Requirement | Priority |
|----|-------------|----------|
| D-REQ-001 | The device MUST publish a schema payload to the Schema Topic upon MQTT broker connection | MANDATORY |
| D-REQ-002 | The schema payload MUST be published with the MQTT retained flag set | MANDATORY |
| D-REQ-003 | The schema payload MUST be valid UTF-8 encoded JSON | MANDATORY |
| D-REQ-004 | The schema MUST include only fields currently active on the device | MANDATORY |
| D-REQ-005 | The device MUST republish the schema on each MQTT reconnection | MANDATORY |
| D-REQ-006 | Schema publication MUST occur before the first status payload publication | MANDATORY |
| D-REQ-007 | The device SHOULD support a configuration parameter to disable schema publication | RECOMMENDED |
| D-REQ-008 | The device MAY republish the schema when its active field set changes | OPTIONAL |
| D-REQ-009 | The schema payload SHOULD NOT exceed 4096 bytes | RECOMMENDED |
| D-REQ-010 | Schema publication MUST use QoS 1 or higher | MANDATORY |

### 6.2 Consumer Requirements (C-REQ)

| ID | Requirement | Priority |
|----|-------------|----------|
| C-REQ-001 | A consumer MUST NOT assume the presence of any field not listed in the schema | MANDATORY |
| C-REQ-002 | A consumer MUST treat unknown field types gracefully without aborting | MANDATORY |
| C-REQ-003 | A consumer MUST NOT issue commands to fields where `rw` is `false` | MANDATORY |
| C-REQ-004 | A consumer SHOULD validate command values against `values`, `min`, and `max` constraints | RECOMMENDED |
| C-REQ-005 | A consumer MUST handle schema updates delivered via retained message republication | MANDATORY |

---

## 7. Schema Topic Specification

### 7.1 Topic Structure

A conforming device MUST publish its schema to the following topic path:

```
state/<device-identifier>/schema
```

The `<device-identifier>` segment MUST be identical to the identifier used in the device's status and command topics.

**Examples:**

| Device Identifier | Schema Topic |
|---|---|
| `9C139EEF6D28` | `state/9C139EEF6D28/schema` |
| `90706931486C` | `state/90706931486C/schema` |
| `faikout-kitchen` | `state/faikout-kitchen/schema` |

**Rationale for `state/<id>/schema`:** The Faikout firmware publishes its status payload to `state/<device-id>/status`. Placing the schema under the same `state/<device-id>/` prefix makes wildcard subscriptions straightforward: a consumer subscribing to `state/+/schema` automatically discovers all devices, while a subscription to `state/+/status` delivers all status data. Both are consistent subtopics of the same device namespace.

### 7.2 Retention Requirement

The schema message MUST be published with the MQTT `retain` flag set to `1`. This guarantees that consumers subscribing after the device has connected receive the schema immediately without requiring a reconnection event.

### 7.3 Publication Sequence

Required publication sequence upon broker connection:

```
1. Device establishes TCP connection to broker
2. Device sends MQTT CONNECT packet
3. Broker acknowledges with CONNACK
4. Device publishes schema payload (retained, QoS ≥ 1) → state/<id>/schema
5. Device begins publishing status payloads             → state/<id>/status
6. Device subscribes to command topics                  → command/<id>/control
                                                           command/<id>/mode
                                                           command/<id>/fan
                                                           ... (per active writable fields)
```

### 7.4 Quality of Service

Schema publication MUST use QoS 1. QoS 0 MUST NOT be used.

### 7.5 Payload Size Constraints

Implementations SHOULD constrain the schema payload to a maximum of 4096 bytes. Based on the full Faikout field set (35 active fields), the serialised schema payload is approximately 2800 bytes — well within this limit.

---

## 8. Schema Payload Format

### 8.1 Top-Level Structure

The schema payload MUST be a JSON object with the following top-level properties:

```json
{
  "status":  "<status-topic>",
  "command": "<command-topic>",
  "fields":  [ <field-descriptor>, ... ]
}
```

#### 8.1.1 Property: `status`

- **Type:** string
- **Required:** MANDATORY
- **Description:** The full MQTT topic on which the device publishes its status JSON object.
- **Faikout value:** `state/<device-id>/status`
- **Constraints:** MUST be a valid MQTT topic string. MUST NOT contain wildcard characters. MUST NOT be empty.

#### 8.1.2 Property: `command`

- **Type:** string
- **Required:** MANDATORY
- **Description:** The primary MQTT command topic. For devices that use individual per-field command topics (see Section 11.2), this SHOULD be the JSON control topic (`command/<id>/control`). Additional per-field topics are documented in each field descriptor's `commandTopic` property.
- **Faikout value:** `command/<device-id>/control`
- **Constraints:** MUST be a valid MQTT topic string. MUST NOT contain wildcard characters.

#### 8.1.3 Property: `fields`

- **Type:** array of field descriptor objects
- **Required:** MANDATORY
- **Description:** An ordered array of field descriptor objects, one per active field. Only fields currently active on the device are included — the same set used in the status payload.
- **Constraints:** MUST contain at least one element. MUST NOT contain duplicate `key` values.

### 8.2 Recommended Additional Properties

Implementations MAY include additional top-level properties. Consumers MUST ignore unknown properties without error.

#### 8.2.1 Property: `version` (RECOMMENDED)

- **Type:** string
- **Description:** The firmware version string, enabling consumers to detect updates and trigger schema re-evaluation.
- **Example:** `"version": "1.4.2"`

#### 8.2.2 Property: `model` (RECOMMENDED)

- **Type:** string
- **Description:** Human-readable device model or product family identifier.
- **Example:** `"model": "Faikout-S3-MINI-N8"`

#### 8.2.3 Property: `spec` (RECOMMENDED)

- **Type:** string
- **Description:** Version identifier of this specification.
- **Example:** `"spec": "FAIKOUT-SPEC-MQTT-SCHEMA-001/0.2"`

---

## 9. Field Descriptor Specification

### 9.1 Field Descriptor Object Structure

```json
{
  "key":          "<field-key>",
  "type":         "<data-type>",
  "rw":           <boolean>,
  "label":        "<human-readable-label>",
  "commandTopic": "<full-mqtt-topic>",
  "values":       [ "<value>", ... ],
  "min":          <number>,
  "max":          <number>,
  "unit":         "<unit-string>"
}
```

### 9.2 Property Definitions

#### 9.2.1 Property: `key`

- **Type:** string
- **Required:** MANDATORY
- **Description:** The JSON property name identifying this field in the status payload and command payload. Must exactly match the key as it appears in the published JSON.
- **Constraints:** Non-empty ASCII string. No whitespace. Unique within the `fields` array. Case-sensitive.
- **Source:** All keys in this specification are derived from the FIELDS table in `faikout_alias_generator_en.js` (lines 46–92) which reflects the actual field names published by Faikout firmware.
- **Examples:** `"power"`, `"temp"`, `"fan"`, `"comp"`, `"Whheating"`

#### 9.2.2 Property: `type`

- **Type:** string (enumerated)
- **Required:** MANDATORY
- **Description:** Data type of the field value. See Section 10 for complete definitions.
- **Permitted values:** `"bool"`, `"number"`, `"string"`
- **Note:** The ioBroker generator uses `"mixed"` for fields that can be either string or number depending on the model. Consumers encountering unknown type values MUST treat the field as opaque without raising a fatal error.

#### 9.2.3 Property: `rw`

- **Type:** boolean (JSON `true` or `false`)
- **Required:** MANDATORY
- **Description:** `true` = field is writable (commands accepted). `false` = field is read-only.
- **Source:** Directly corresponds to the presence of a `writeTopic` property in the ioBroker FIELDS definitions (`faikout_alias_generator_en.js`, lines 47–91). Read-only fields have no `writeTopic`.

#### 9.2.4 Property: `label`

- **Type:** string
- **Required:** RECOMMENDED
- **Description:** Human-readable label for display in automation platform UIs.
- **Source:** Directly corresponds to the `label` property in `faikout_alias_generator_en.js` FIELDS definitions. Example: `"Fan mode (e.g. 1-5/A/Q)"` → simplify to `"Fan Speed"`.

#### 9.2.5 Property: `commandTopic`

- **Type:** string
- **Required:** CONDITIONAL — MUST be present for writable fields that use an individual per-field command topic rather than the JSON control topic.
- **Description:** The specific MQTT topic to which commands for this field are published. For fields using the JSON control topic (`command/<id>/control`), this property SHOULD be omitted (the top-level `command` property applies). For fields with individual topics, this MUST be the full topic path.
- **Source:** Derived from the `writeTopic` property in `faikout_alias_generator_en.js`:
  - `writeTopic: 'control'` → uses top-level command topic (no `commandTopic` needed)
  - `writeTopic: 'mode'` → `commandTopic: "command/<id>/mode"`
  - `writeTopic: 'fan'` → `commandTopic: "command/<id>/fan"`
  - `writeTopic: 'econo'` → `commandTopic: "command/<id>/econo"` (payload: `0` or `1`)
  - `writeTopic: 'setting:autot'` → `commandTopic: "setting/<id>/autot"`
- **See also:** Section 11.2 for the complete command topic matrix.

#### 9.2.6 Property: `values`

- **Type:** array of strings
- **Required:** CONDITIONAL (RECOMMENDED for `"string"` type fields with a finite value set)
- **Description:** Enumerated list of all permitted values. Consumers MUST restrict command values to this set and SHOULD display it as a selection control.
- **Constraints:** Only on `"string"` type fields. At least two elements if present. Values must exactly match the strings used in status and command payloads.
- **Examples from actual implementations:**
  - `mode`: `["H","C","A","D","F"]` — Heat, Cool, Auto, Dry, Fan (openCCU README, Node-RED README)
  - `fan`: `["A","1","2","3","4","5","Q"]` — Auto, Speed 1–5, Quiet (openCCU system variable definition)
  - `humidify`: `["X","L","S","H","C"]` — Off, Low, Standard, High, Continuous (Node-RED flow documentation)

#### 9.2.7 Property: `min`

- **Type:** number
- **Required:** OPTIONAL (RECOMMENDED for `"number"` type fields with a defined lower bound)
- **Constraints:** Only on `"number"` fields. Must be strictly less than `max` if both are present.
- **Examples from actual implementations:**
  - `temp`: `min: 16` — minimum setpoint temperature (openCCU system variable, ioBroker FIELDS)
  - `demand`: `min: 0` — minimum compressor load (Node-RED documentation: `0–100`)

#### 9.2.8 Property: `max`

- **Type:** number
- **Required:** OPTIONAL (RECOMMENDED for `"number"` type fields with a defined upper bound)
- **Examples from actual implementations:**
  - `temp`: `max: 30` — maximum setpoint, per openCCU (`Temp_Soll: Float 16–30°C`); prototype issue JSON shows `max: 30`
  - `demand`: `max: 100` — maximum compressor load percentage

#### 9.2.9 Property: `unit`

- **Type:** string
- **Required:** OPTIONAL
- **Description:** SI unit symbol for numeric fields.
- **Source:** Directly corresponds to the `unit` property in `faikout_alias_generator_en.js` FIELDS definitions.
- **Values observed in implementations:** `"°C"`, `"%"`, `"Hz"`, `"RPM"`, `"W"`, `"Wh"`, `"V"`, `"°"`

---

## 10. Data Type Definitions

### 10.1 Type: `bool`

#### 10.1.1 Definition

Binary state: `true` (active/on) or `false` (inactive/off).

#### 10.1.2 JSON Representation in Status Payload

Boolean fields appear as JSON boolean literals in the status payload:

```json
{ "power": true, "econo": false, "swingh": true }
```

#### 10.1.3 Command Payload Variants

The Faikout firmware accepts boolean commands in two forms depending on the command topic:

**JSON control topic** (`command/<id>/control`): JSON boolean
```json
{ "power": true }
{ "swingv": false }
```

**Individual command topics** (`command/<id>/econo`, `command/<id>/powerful`, etc.): plain integer
```
0       ← false / off
1       ← true / on
```

This dual format is documented in `faikout_alias_generator_en.js` lines 52–73: fields using `writeTopic: 'control'` use `writeConv: 'JSON.stringify({key:val})'` while fields using individual topics use `writeConv: 'val?1:0'`.

#### 10.1.4 Consumer Behaviour

Render as binary toggle. Where the `commandTopic` property is absent: send JSON boolean via the top-level command topic. Where `commandTopic` is present: send `1` or `0` as plain string.

---

### 10.2 Type: `number`

#### 10.2.1 Definition

Quantitative measurement or setpoint expressed as integer or floating-point.

#### 10.2.2 JSON Representation in Status Payload

```json
{ "temp": 23, "home": 22.5, "comp": 48, "consumption": 1250 }
```

#### 10.2.3 Precision by Field Category

| Category | Precision | Example |
|---|---|---|
| Temperature setpoints | Integer (°C) | `"temp": 23` |
| Temperature sensors | One decimal (°C) | `"home": 22.5`, `"outside": 21.0` |
| BLE sensor readings | Two decimals | `"ble_temp": 22.19`, `"ble_hum": 47.04` |
| Energy counters | Integer (Wh) | `"Whheating": 14780` |
| Compressor speed | Integer (Hz) | `"comp": 48` |
| Fan speed | Integer (RPM) | `"fanrpm": 850` |
| Power consumption | Integer (W) | `"consumption": 1250` |
| Demand / load | Integer (%) | `"demand": 0` |

#### 10.2.4 Command Payload

Numeric command payloads are sent as plain numbers, unquoted:

**JSON control topic:**
```json
{ "temp": 22 }
{ "env": 21.5 }
```

**Individual setting topic** (`setting/<id>/autot`, `setting/<id>/autor`):
```
22.0
0.5
```

---

### 10.3 Type: `string`

#### 10.3.1 Definition

A value from a named set of states or identifiers. String fields with a `values` array have a closed enumerated value set; those without accept free-form input.

#### 10.3.2 JSON Representation in Status Payload

```json
{ "mode": "C", "fan": "A", "humidify": "X" }
```

#### 10.3.3 Command Payload Variants

**Individual command topics** (`command/<id>/mode`, `command/<id>/fan`, etc.): plain string value (not JSON-encoded)
```
H
C
A
```

**JSON control topic** (where applicable):
```json
{ "mode": "H" }
```

The ioBroker generator uses individual topics for `mode` and `fan` (lines 50–51: `writeTopic: 'mode'`, `writeTopic: 'fan'`). The openCCU flow and Node-RED flow also publish to individual command subtopics.

---

## 11. Command Interface Specification

### 11.1 Command Architecture Overview

The Faikout firmware supports two parallel command mechanisms:

**Mechanism A — JSON control topic:** A single topic `command/<device-id>/control` accepts JSON objects with one or more field/value pairs. Used for: `power`, `swingv`, `swingh`, `env` (external temperature injection).

**Mechanism B — Individual per-field topics:** Each controllable field has its own topic. Used for: `mode`, `fan`, `econo`, `powerful`, `comfort`, `streamer`, `led`, `quiet`, `demand`, `humidify`, `autoe`, `autop`, `auto0`, `auto1`.

**Mechanism C — Setting topics:** Faikout-internal automation settings use a `setting/<device-id>/` prefix. Used for: `autot`, `autor`, and timer JSON (`auto0`, `auto1` as JSON).

### 11.2 Command Topic Matrix

This table is derived from the `writeTopic` and `writeConv` definitions in `faikout_alias_generator_en.js` (lines 47–91) and cross-validated against the Node-RED flow documentation and openCCU README.

| Field | Command Topic | Payload Format | Example |
|---|---|---|---|
| `power` | `command/<id>/control` | JSON bool | `{"power":true}` |
| `swingv` | `command/<id>/control` | JSON bool | `{"swingv":true}` |
| `swingh` | `command/<id>/control` | JSON bool | `{"swingh":false}` |
| `env` (write) | `command/<id>/control` | JSON number | `{"env":21.5}` |
| `mode` | `command/<id>/mode` | plain string | `H` / `C` / `A` / `D` / `F` |
| `fan` | `command/<id>/fan` | plain string | `A` / `1`–`5` / `Q` |
| `econo` | `command/<id>/econo` | plain int | `0` or `1` |
| `powerful` | `command/<id>/powerful` | plain int | `0` or `1` |
| `comfort` | `command/<id>/comfort` | plain int | `0` or `1` |
| `streamer` | `command/<id>/streamer` | plain int | `0` or `1` |
| `led` | `command/<id>/led` | plain int | `0` or `1` |
| `quiet` | `command/<id>/quiet` | plain int | `0` or `1` |
| `demand` | `command/<id>/demand` | plain number | `0`–`100` |
| `humidify` | `command/<id>/humidify` | plain string | `X` / `L` / `S` / `H` / `C` |
| `autoe` | `command/<id>/autoe` | plain int | `0` or `1` |
| `autop` | `command/<id>/autop` | plain int | `0` or `1` |
| `autot` | `setting/<id>/autot` | plain number | `22.0` |
| `autor` | `setting/<id>/autor` | plain number | `0.5` |
| `auto0` | `setting/<id>` | JSON string | `{"auto0":"2300"}` |
| `auto1` | `setting/<id>` | JSON string | `{"auto1":"0600"}` |

### 11.3 `env` — External Temperature Injection

The `env` field requires special attention. It is read-only from the status perspective (reports the current control reference temperature) but also writable via `command/<id>/control` to inject an external sensor reading.

**Critical timing requirement:** The injected `env` value expires after `tcontrol` seconds (Faikout firmware setting, default: 600 s). If no update arrives within this window, the Faikout falls back to its internal sensor. Consumers MUST send `env` cyclically — recommended interval: 30–60 seconds.

This requirement is explicitly documented in:
- `faikout_alias_generator_en.js` lines 82–86 (comment block on `env_set` field)
- `faikout-nodered-flow.json` Group ⑤ documentation: "Must be sent cyclically — every 30–60 seconds"

The schema represents this as two distinct field descriptors: `env` (read-only, current value) and `env_set` (write-only, injection alias).

### 11.4 Timer Fields (`auto0`, `auto1`)

Timer values use HHMM format — a four-digit string without colon. Examples: `"2300"` = 23:00, `"0630"` = 06:30. Consumers presenting a time picker MUST convert to/from HHMM on publish.

Source: `faikout_alias_generator_en.js` line 77: `writeConv: 'JSON.stringify({auto0:String(val).replace(":","")})'`

---

## 12. Feature Enablement and Configuration Parameters

### 12.1 Schema Publication Enable/Disable

The firmware configuration parameter governing schema publication is:

| Parameter name | Type | Default | UI label |
|---|---|---|---|
| `mqttschema` | bool | `true` | "MQTT schema topic" |
| | | | Description: "Publish MQTT schema topic" |

The firmware settings page (Faikout tab → Extra settings) exposes this as a toggle. As demonstrated in the prototype (Appendix A, Screenshot A.1), the toggle was implemented and confirmed active on hardware device `90706931486C`.

When `mqttschema = false`, the device MUST NOT publish to the Schema Topic. If a retained schema from a previous session exists, the device SHOULD publish an empty retained message to clear it.

### 12.2 Interaction with Home Assistant Discovery

Schema publication is independent of the Home Assistant discovery setting (`haenable`). Both may be active simultaneously. They serve distinct consumer audiences and operate on distinct topic paths. Disabling one MUST NOT affect the other.

The prototype firmware settings page (Appendix A, Screenshot A.1) shows both toggles independently present: "Home Assistant" (disabled) and "MQTT schema topic" (enabled), confirming independent operation.

---

## 13. Deployment Scenarios and Use Cases

### 13.1 Scenario A: ioBroker Alias Generator

**Source file:** `faikout_alias_generator_en.js`  
**Repository:** https://codeberg.org/RaW07/faikout-iobroker  

**Description:** A script run once in the ioBroker JavaScript adapter. It queries the Faikout HTTP interface to detect active fields, then creates ioBroker alias data points under `alias.0.<ALIAS_NAME>.*`.

**Current feature detection (without schema topic):**

The generator performs three HTTP requests (lines 102–141):
1. `GET http://<ip>/` — scrapes field names from the JavaScript source (`o.fieldname` pattern)
2. `GET http://<ip>/revk-settings?_page=-2` — detects disabled features (`id="no<key>"`) and BLE status (`id="bleenable"`)
3. Reads the current MQTT status state to detect energy meter fields (`Whoutside`, `Whheating`, `Whcooling`)

Additionally, the device ID is fetched from `GET http://<ip>/revk-settings?_page=0` by parsing the `<h1>DEVICE_ID` tag (lines 147–167).

**With schema topic:** All three HTTP requests and the web-scraping logic become unnecessary. The schema payload delivers the complete active field set with types and constraints via MQTT.

**Schema fields consumed:**

| Schema property | ioBroker usage |
|---|---|
| `key` | State ID under `alias.0.<name>.<key>` |
| `type` | ioBroker state type (`boolean`, `number`, `string`) |
| `rw` | `common.write` attribute |
| `label` | `common.name` |
| `unit` | `common.unit` |
| `commandTopic` | `native.topic` on the publish state object |
| `values` | `common.states` mapping (enum) |
| `min` / `max` | `common.min` / `common.max` |

**MQTT adapter variants:** The generator supports both `mqtt-client` (lines 180–206, requires explicit `custom` block with `publish: true`) and the standard `mqtt` adapter. This distinction is transparent to schema consumers.

**Alias creation example** (from `buildAliases()`, lines 212–318):
```javascript
// Read source: mqtt-client.0.state.<deviceId>.status
// Write target: mqtt-client.0.command.<deviceId>.control  (JSON fields)
//               mqtt-client.0.command.<deviceId>.mode     (plain string fields)
```

---

### 13.2 Scenario B: openHAB Integration Generator

**Source file:** `faikout-openhab/automation/js/faikout_generator.js`  
**Repository:** https://codeberg.org/RaW07/faikout-projects  

**Description:** A GraalVM JS rule that runs at openHAB startup (SystemStartlevelTrigger level 100). It queries the Faikout HTTP API, detects active features, and creates a MQTT Broker Thing, a Generic MQTT Topic Thing with channels, Items, and channel links via the openHAB REST API. Re-running is safe — existing entries are updated.

**Current feature detection (without schema topic):**

The generator queries `GET http://<FAIKOUT_HOST>/api` and filters the CHANNELS definition array against the returned JSON keys (lines 248–259 of `faikout_generator.js`):
```javascript
activeChannels = CHANNELS.filter(ch => ch.key in status && status[ch.key] !== null);
```
Fallback: if the device is unreachable at startup, all 17 defined channels are created.

**With schema topic:** The HTTP API query is replaced by a single MQTT schema subscription. The schema payload provides the active field set with types, eliminating the need for the HTTP call and the hardcoded CHANNELS array.

**Channel configuration** (from `channelConfig()`, lines 163–184):

The generator builds per-channel MQTT configuration including:
- `stateTopic` → `status/<device-id>` *(currently)*
- `transformationPattern` → `JSONPATH:$.<key>`
- `commandTopic` → `command/<device-id>/control`
- `formatBeforePublish` → `{"<key>": %s}` (Switch/Number) or `{"<key>": "%s"}` (String)

**Note on current topic:** The existing generator uses `status/<id>` and `command/<id>/control`. The schema topic path `state/<id>/schema` and status topic `state/<id>/status` as used in ioBroker and Node-RED should be verified against the firmware version in use.

**Schema fields consumed:**

| Schema property | openHAB usage |
|---|---|
| `key` | Channel ID, JSONPath key, Item name suffix |
| `type` | openHAB Item type: `bool`→`Switch`, `number`→`Number`, `string`→`String` |
| `rw` | Presence of `commandTopic` and `formatBeforePublish` on channel |
| `label` | Channel label and Item label |
| `status` | Channel `stateTopic` |
| `command` | Channel `commandTopic` (for JSON-control fields) |

---

### 13.3 Scenario C: Homematic CCU via openCCU / Redmatic

**Source file:** `faikout-flow.json`  
**Repository:** https://codeberg.org/RaW07/openCCU  

**Description:** A Node-RED flow running on Redmatic (Node-RED embedded in the Homematic CCU3). It subscribes to the Faikout MQTT status topic, parses the JSON payload, and writes values to CCU system variables. When a system variable is changed in the CCU (e.g. from a CCU program or visualisation), the flow immediately publishes the corresponding MQTT command.

**Setup mechanism:** The flow includes an idempotent ► Setup button that creates all CCU system variables via the local ReGa endpoint on port 8181. Variables are created using ReGa script (HomeMatic scripting language) — no CCU restart required.

**System variables created (from openCCU README, system variables table):**

| Variable | CCU type | Schema field | Schema type |
|---|---|---|---|
| `Faikout_<Device>_Power` | Bool | `power` | `bool` |
| `Faikout_<Device>_Mode` | Enum | `mode` | `string`, values: H/C/A/D/F |
| `Faikout_<Device>_Fan` | Enum | `fan` | `string`, values: A/1/2/3/4/5/Q |
| `Faikout_<Device>_Temp_Soll` | Float (°C) | `temp` | `number`, min:16, max:30, unit:°C |
| `Faikout_<Device>_Econo` | Bool | `econo` | `bool` |
| `Faikout_<Device>_Comfort` | Bool | `comfort` | `bool` |
| `Faikout_<Device>_Powerful` | Bool | `powerful` | `bool` |
| `Faikout_<Device>_Quiet` | Bool | `quiet` | `bool` |
| `Faikout_<Device>_SwingH` | Bool | `swingh` | `bool` |
| `Faikout_<Device>_SwingV` | Bool | `swingv` | `bool` |
| `Faikout_<Device>_Bedarf` | Float (%) | `demand` | `number`, min:0, max:100, unit:% |
| `Faikout_<Device>_Raum` | Float (°C) | `env` / `ble_temp` | `number`, unit:°C |
| `Faikout_<Device>_Online` | Bool | *(synthetic)* | — |

**Humidity control extension:** The flow includes an optional Humidity Control tab that reads BLE sensor data (`ble.temp`, `ble.hum` from the MQTT status payload) and activates the Faikout in DRY mode when the dew point margin falls below configured thresholds. Parameters and control logic are documented in the openCCU README. Relevant schema fields: `ble_temp`, `ble_hum`.

**With schema topic:** The flow's configuration step could be automated: on startup, subscribe to `state/+/schema`, read the field list, and selectively create/update only the system variables for fields actually present on the device. This eliminates the need for the manual ► Setup button and the hardcoded variable list.

---

### 13.4 Scenario D: Node-RED Standalone Flow

**Source file:** `faikout-nodered-flow.json`  
**Repository:** https://codeberg.org/RaW07/faikout-NodeRed  

**Description:** An import-ready Node-RED flow for controlling Faikout devices. Structured in six groups (tabs within a single flow tab named "Faikout MQTT"):

| Group | Function | Key nodes |
|---|---|---|
| ① Configuration | Stores device ID in flow context | Inject node, function node |
| ② Receive Status | Subscribe `state/+/status`, filter by ID, parse JSON | MQTT-in, filter, JSON parse, split |
| ③ Commands | Manual test inject nodes + shared "Befehl senden" function | Multiple inject nodes, MQTT-out |
| ④ Settings | Faikout automation (`autot`, `autor`, timers) | Inject nodes, MQTT-out |
| ⑤ External Temperature | Cyclic 30s injection of room temperature to `env` | Inject (30s repeat), MQTT-out |
| ⑥ Diagnostics | After first status: show which fields are active on this model | Inject, function, debug |

**Diagnostics group (⑥)** is particularly relevant: it already implements a manual version of schema discovery — after receiving the first status payload, pressing ► displays which fields the device actually reports (✓ active, ✗ unsupported). A schema topic would make this automatic and available before the first status arrives.

**Status subscription:** Uses `state/+/status` (wildcard) for multi-device support. Each message is filtered by device ID stored in flow context. This is consistent with the schema topic structure `state/+/schema`.

**External temperature cycle (Group ⑤):** The inject node is pre-configured with a 30-second repeat interval, publishing `{"env": <value>}` to `command/<id>/control`. This implements the cyclic requirement described in Section 11.3.

**With schema topic:** Group ① configuration could be eliminated. On startup, the flow subscribes to `state/+/schema`, parses the returned field list, and dynamically configures MQTT subscription topics, output message routing, and dashboard widgets based on the schema — without any manual device ID entry.

---

### 13.5 Scenario E: Multi-Device Wildcard Discovery

**Description:** A consumer subscribes to `state/+/schema` and maintains a registry of all discovered devices. Each schema message registers a new device or updates an existing registration.

```
Consumer subscribes to state/+/schema
Broker delivers all retained schema messages matching wildcard
Consumer builds device registry: device-id → schema
Consumer creates integrations for all discovered devices
New device connects → publishes schema → consumer auto-discovers
```

This is the intended end state for all four existing integrations. Currently, each integration requires manual device ID configuration (ioBroker: `FAIKOUT_IP` constant; openHAB: `CFG.faikoutHost`; Node-RED: ① Configuration group; openCCU: flow tab configuration). With a schema topic, a single wildcard subscription discovers all devices automatically.

---

### 13.6 Scenario F: Firmware Update Robustness

**Description:** A consumer compares the `version` property in successive schema publications. On detection of a version change, the consumer re-evaluates the field set and updates its integration configuration.

**Practical example:** The ioBroker generator already handles this case: "Re-running the script compares against the currently active features of the Faikout – alias data points for features that are known but no longer active are automatically removed" (ioBroker README). With a schema topic, this comparison happens automatically on firmware update without manual re-execution of the generator script.

---

## 14. Test Scenarios and Acceptance Criteria

### 14.1 Test Suite Overview

The following test scenarios define acceptance criteria for a conforming device implementation.

---

### 14.2 T-001: Schema Publication on Connection

**Category:** Basic conformance | **Priority:** CRITICAL

**Preconditions:** Broker running; `mqttschema = true`; no retained schema present.

**Steps:**
1. Subscribe to `state/<id>/schema`
2. Power on or restart the device
3. Observe CONNACK, then observe message delivery

**Expected outcome:** Retained message delivered to `state/<id>/schema` within 5 seconds of CONNACK. Valid JSON. Retain flag set.

**Pass criteria:** Message received, retained, valid JSON.

---

### 14.3 T-002: Schema Before Status

**Category:** Publication sequence | **Priority:** HIGH

**Steps:**
1. Subscribe to both `state/<id>/schema` and `state/<id>/status`
2. Restart device; record timestamps of first message on each topic

**Expected outcome:** `T(schema) ≤ T(first_status)`

---

### 14.4 T-003: Retained Delivery to Late Subscriber

**Category:** Retention behaviour | **Priority:** CRITICAL

**Steps:**
1. Wait 60 seconds after device connection
2. Subscribe a new client to `state/<id>/schema`
3. Observe delivery

**Expected outcome:** Schema delivered within 2 seconds of subscription without device reconnection.

---

### 14.5 T-004: Field Set Matches Status Payload

**Category:** Field set correctness | **Priority:** HIGH

**Steps:**
1. Parse `fields` array from schema; collect `key` values
2. Parse status payload; collect JSON property keys
3. Compare sets

**Expected outcome:** Every status key appears in the schema. No phantom fields in schema.

---

### 14.6 T-005: JSON Type Correctness in Status

**Category:** Type conformance | **Priority:** HIGH

**Steps:** For each field in the schema, verify the status payload value is the correct JSON type:
- `"bool"` → JSON `true` or `false` (not string `"true"`)
- `"number"` → JSON number (not quoted)
- `"string"` → JSON string

**Pass criteria:** Zero type mismatches.

---

### 14.7 T-006: Writable Field Command — JSON Control Topic

**Category:** Command interface | **Priority:** HIGH

**Steps:**
1. Select a writable `bool` field without `commandTopic` (e.g. `power`)
2. Read current value from status
3. Publish `{"power": <inverted>}` to `command/<id>/control`
4. Wait up to 10 seconds; verify status reflects commanded value

**Pass criteria:** Status field value matches commanded value.

---

### 14.8 T-007: Writable Field Command — Individual Topic

**Category:** Command interface | **Priority:** HIGH

**Steps:**
1. Select a writable string field with `commandTopic` (e.g. `mode`)
2. Read current value from status
3. Publish a different mode string (e.g. `C`) to `command/<id>/mode`
4. Wait up to 10 seconds; verify status `mode` reflects new value

**Pass criteria:** Status field value matches commanded value.

---

### 14.9 T-008: Read-Only Field Immutability

**Category:** Writability enforcement | **Priority:** MEDIUM

**Steps:**
1. Select a read-only field (e.g. `home` — indoor temperature sensor)
2. Attempt to publish a command targeting this field
3. Wait 10 seconds; observe status

**Expected outcome:** Field value unchanged (reflects sensor reading).

---

### 14.10 T-009: Enumerated String Field Validation

**Category:** Value constraint | **Priority:** MEDIUM

**Steps:**
1. Select `mode` field (values: `["H","C","A","D","F"]`)
2. Publish `INVALID` to `command/<id>/mode`
3. Wait 10 seconds; verify mode unchanged

**Pass criteria:** Status `mode` unaffected.

---

### 14.11 T-010: Numeric Range — Temperature Setpoint

**Category:** Value constraint | **Priority:** MEDIUM

**Steps:**
1. Publish `{"temp": 5}` (below min:16) to control topic
2. Wait; verify `temp` unchanged
3. Publish `{"temp": 45}` (above max:30)
4. Wait; verify `temp` unchanged

**Pass criteria:** Both out-of-range commands ignored.

---

### 14.12 T-011: `env` Cyclic Requirement

**Category:** Special fields | **Priority:** HIGH

**Steps:**
1. Inject `{"env": 22.0}` to `command/<id>/control`
2. Verify `env` appears in status payload
3. Wait `tcontrol + 30` seconds without sending further updates
4. Verify status payload `env` field is absent or returns to internal sensor value

**Expected outcome:** `env` expires and device falls back to internal reference.

**Pass criteria:** `env` value absent from status or changes to internal sensor reading after timeout.

**Note:** This test validates the cyclic injection requirement documented in `faikout_alias_generator_en.js` lines 82–86 and Node-RED Group ⑤ documentation.

---

### 14.13 T-012: `mqttschema` Disable Parameter

**Category:** Configuration | **Priority:** MEDIUM

**Steps:**
1. Set `mqttschema = false` via firmware settings UI (Faikout tab → Extra → "MQTT schema topic" toggle off)
2. Restart device; subscribe to `state/<id>/schema`
3. Wait 30 seconds

**Expected outcome:** No schema payload published. Prior retained message cleared.

---

### 14.14 T-013: Multi-Device Wildcard Discovery

**Category:** Interoperability | **Priority:** MEDIUM

**Steps:**
1. Connect two or more devices; each with distinct device IDs
2. Subscribe to `state/+/schema`
3. Observe delivery

**Expected outcome:** One schema payload per connected device. `status` and `command` topics in each payload correctly reference the respective device ID.

---

### 14.15 T-014: BLE Field Presence Conditional on BLE Enable

**Category:** Feature detection | **Priority:** MEDIUM

**Preconditions:** Faikout device with `bleenable = false` (Extra settings).

**Steps:**
1. Receive schema payload
2. Verify `ble_temp`, `ble_hum`, `ble_bat`, `ble_volt` are NOT present in `fields` array

**Expected outcome:** BLE fields absent from schema.

**Then:** Enable BLE, restart, receive new schema.

**Expected outcome:** BLE fields present in schema if a BLE sensor is in range.

**Note:** This corresponds to the BLE detection logic in `faikout_alias_generator_en.js` lines 121–128.

---

## 15. Implementation Considerations

### 15.1 Firmware Implementation

A conforming firmware implementation requires:

1. **Schema builder function:** Constructs the JSON schema payload from the device's runtime state. Iterates over the device's field definitions and includes only currently active fields. This function shares field definitions with the existing HA discovery and status publication logic.

2. **MQTT connection hook:** Calls the schema builder and publishes the result to `state/<id>/schema` (retained, QoS 1) on each successful MQTT connection, before any status publication.

3. **Configuration parameter handling:** Checks `mqttschema` before publication; publishes empty retained message to clear schema on disable.

Estimated implementation size: 80–120 lines of C code. The prototype implementation (revk/ESP32-Faikout#1085, 2026-08-23) demonstrated approximately 80 lines for `send_mqtt_schema()`.

### 15.2 Field Definition Reuse

All three existing publication mechanisms (status payload, HA discovery, schema) share the same underlying field definitions in the firmware. The schema builder SHOULD iterate the same field definition table to avoid duplication. Only the output format differs.

### 15.3 Dynamic Field Set

The Faikout firmware supports optional features that can be enabled or disabled per device (streamer, LED, humidifier, BLE sensors, quiet mode, etc.). The schema MUST reflect only currently active fields — identical to the set used in the status payload. This dynamic nature is the primary reason static documentation is insufficient and the schema topic is necessary.

The current ioBroker generator detects this dynamic set at lines 113–141 via HTTP scraping. The openHAB generator uses HTTP API response filtering at lines 248–259. Both approaches are superseded by the schema topic.

### 15.4 Consumer Implementation Pattern

```
1. Subscribe to state/+/schema
2. On schema message receipt:
   a. Parse JSON payload
   b. Validate mandatory properties present (status, command, fields)
   c. Extract status and command topics
   d. Iterate fields array
   e. For each field: create platform-specific integration object
   f. Store schema (version, field set) for update detection
3. On subsequent schema receipt for same device-id:
   a. Compare field set with stored schema
   b. Remove integration objects for fields no longer present
   c. Add integration objects for newly added fields
   d. Update integration objects for changed type/constraints
```

Step 3b (removal of stale data points) is already implemented in the ioBroker generator (lines 300–312: "Remove stale data points").

---

## 16. Interoperability Guidelines

### 16.1 Consumer Robustness

Consumers MUST handle gracefully:
- Additional top-level properties not in this specification
- Additional field descriptor properties not in this specification
- Unknown `type` values — treat field as opaque
- Missing RECOMMENDED properties (`label`, `unit`, `values`, `min`, `max`)
- Empty `fields` array
- Schema payload that is valid JSON but non-conforming

### 16.2 Forward Compatibility

The `spec` property (Section 8.2.3) enables version-specific parsing logic. Future revisions introducing breaking changes MUST increment the version suffix.

### 16.3 Coexistence with Home Assistant Discovery

Both publication mechanisms MUST operate independently. The firmware settings page (Appendix A, Screenshot A.1) confirms both "Home Assistant" and "MQTT schema topic" toggles are independently controllable.

---

## 17. Security Considerations

### 17.1 Information Disclosure

The schema topic reveals the device's complete field structure and command interface to any MQTT client with read access. In sensitive environments, access to `state/<id>/schema` SHOULD be restricted via broker ACLs.

### 17.2 Command Injection

The command topic is pre-existing. This specification introduces no additional attack surface. Broker ACLs SHOULD restrict write access to `command/<id>/*` and `setting/<id>/*` to authorised clients.

### 17.3 Schema Spoofing

Malicious overwrite of the retained schema could redirect consumers to incorrect topics. Broker ACLs SHOULD restrict write access to `state/<id>/schema` to the device itself.

---

## 18. Error Handling and Edge Cases

### 18.1 Device Offline

The retained schema remains available after device disconnection. Consumers SHOULD NOT issue commands to confirmed-offline devices. The openCCU integration tracks this via the `Faikout_<Device>_Online` system variable (set `true` on each status update, not reset on disconnect — consumers detect offline by absence of status updates).

### 18.2 Schema-Status Mismatch

If the status payload contains a field not in the schema, consumers SHOULD ignore the unexpected field and log a warning. This may occur when a retained schema from a previous firmware version remains after a firmware update. The `version` property (Section 8.2.1) enables consumers to detect this condition.

### 18.3 Buffering Status Before Schema

Consumers subscribing to both `state/<id>/schema` and `state/<id>/status` simultaneously may receive a status payload before schema processing completes (broker delivery ordering is not guaranteed across subscriptions). Consumers SHOULD buffer incoming status payloads until the schema is processed.

### 18.4 `env` Expiry Without Schema

Without the schema, consumers have no machine-readable indication that `env` requires cyclic injection. With the schema, the `env_set` write-only field descriptor (or a `cyclic: true` flag extension) could convey this requirement explicitly.

---

## 19. Appendix A – Prototype Evidence

### A.1 Firmware Settings Screenshot

The following screenshot (from revk/ESP32-Faikout#1085, posted 2026-08-29, device `90706931486C`) shows the Faikout firmware settings page with the MQTT schema topic toggle implemented and enabled:

```
Device: 90706931486C  [MQTT connected]

Settings: Basic | [Faikout] | Extra | Library

Fahrenheit              ○  Web shows Fahrenheit
Text rather than icons  ●  Do not show icons on web UI
Home Assistant          ○  Home Assistant
MQTT schema topic       ●  Publish MQTT schema topic    ← prototype setting, enabled
Dark mode LED           ○  Default LED off
Debug                   ○  Debug - logs summary of status responses
Hide Faikout auto mode  ○  Do not show Faikout auto controls
BLE Sensors             ○  Enable BLE for sensors or remote
```

Key observations:
- The toggle label matches the parameter name `mqttschema`
- Home Assistant toggle is disabled; MQTT schema topic is enabled — confirming independent operation
- The device is connected to the MQTT broker at the time of the screenshot

### A.2 Prototype JSON Structure (from Issue Comment, 2026-08-23 16:50)

The prototype used a hierarchical structure separating topics, commands, and status fields:

```json
{
  "topics": {
    "status":  "state/GuestAC/status",
    "command": "command/GuestAC"
  },
  "commands": {
    "control":  { "payload": "json" },
    "temp":     { "payload": "float", "min": 16, "max": 30 },
    "mode":     { "payload": "string", "values": ["H","C","A","D","F"] }
  },
  "status_fields": {
    "power":    { "type": "bool",  "writable": true },
    "temp":     { "type": "float", "unit": "C", "writable": true }
  }
}
```

**Note on format difference:** This specification adopts a flat `fields` array (rather than separate `commands` and `status_fields` objects) as the primary format, as it is more natural for consumer iteration. The topic structure (`state/<id>/status`, `command/<id>`) is consistent with the prototype. Both formats are conceptually equivalent; the flat format reduces nesting depth for consumers iterating all fields.

---

## 20. Appendix B – Complete Field Reference

This table is derived from the FIELDS definition in `faikout_alias_generator_en.js` (lines 46–92) — the most complete field inventory of any existing integration. Fields are ordered by category.

### B.1 Control Fields

| Key | Type | RW | Label | Command topic | Payload | Values | Min | Max | Unit |
|---|---|---|---|---|---|---|---|---|---|
| `power` | bool | yes | Power on/off | `/control` (JSON) | `{"power":true}` | — | — | — | — |
| `mode` | string | yes | Operating mode | `/mode` (plain) | `H`/`C`/`A`/`D`/`F` | H,C,A,D,F | — | — | — |
| `fan` | string | yes | Fan speed | `/fan` (plain) | `A`/`1`–`5`/`Q` | A,1,2,3,4,5,Q | — | — | — |
| `temp` | number | yes | Setpoint (Daikin) | `/control` (JSON) | `{"temp":22}` | — | 16 | 30 | °C |
| `swingv` | bool | yes | Vertical swing | `/control` (JSON) | `{"swingv":true}` | — | — | — | — |
| `swingh` | bool | yes | Horizontal swing | `/control` (JSON) | `{"swingh":true}` | — | — | — | — |
| `econo` | bool | yes | Economy mode | `/econo` (int) | `0`/`1` | — | — | — | — |
| `powerful` | bool | yes | Powerful mode | `/powerful` (int) | `0`/`1` | — | — | — | — |
| `comfort` | bool | yes | Comfort mode | `/comfort` (int) | `0`/`1` | — | — | — | — |
| `quiet` | bool | yes | Quiet mode | `/quiet` (int) | `0`/`1` | — | — | — | — |
| `streamer` | bool | yes | Air purifier | `/streamer` (int) | `0`/`1` | — | — | — | — |
| `led` | bool | yes | LED | `/led` (int) | `0`/`1` | — | — | — | — |
| `demand` | number | yes | Compressor load | `/demand` (int) | `0`–`100` | — | 0 | 100 | % |
| `humidify` | string | yes | Humidifier | `/humidify` (plain) | `X`/`L`/`S`/`H`/`C` | X,L,S,H,C | — | — | — |

### B.2 Faikout Automation Fields

| Key | Type | RW | Label | Command topic | Min | Max | Unit |
|---|---|---|---|---|---|---|---|
| `autoe` | bool | yes | Auto mode active | `/autoe` (int) | — | — | — |
| `autop` | bool | yes | Auto power active | `/autop` (int) | — | — | — |
| `autot` | number | yes | Target temp (Faikout) | `setting/<id>/autot` | — | — | °C |
| `autor` | number | yes | Hysteresis | `setting/<id>/autor` | — | — | °C |
| `auto0` | string | yes | Timer off time | `setting/<id>` (JSON) | — | — | — |
| `auto1` | string | yes | Timer on time | `setting/<id>` (JSON) | — | — | — |

### B.3 Sensor / Status Fields (Read-Only)

| Key | Type | RW | Label | Unit |
|---|---|---|---|---|
| `home` | number | no | Indoor temperature | °C |
| `outside` | number | no | Outdoor temperature | °C |
| `liquid` | number | no | Refrigerant temperature | °C |
| `inlet` | number | no | Inlet temperature | °C |
| `env` | number | no | Room temperature (ext. ref.) | °C |
| `hum` | number | no | Humidity | % |
| `comp` | number | no | Compressor speed | Hz |
| `fanrpm` | number | no | Fan speed | RPM |
| `consumption` | number | no | Power consumption | W |
| `Whheating` | number | no | Heating energy (cumulative) | Wh |
| `Whcooling` | number | no | Cooling energy (cumulative) | Wh |
| `Whoutside` | number | no | Outdoor unit energy meter | Wh |
| `anglev` | number | no | Vertical vane angle | ° |
| `antifreeze` | bool | no | Anti-freeze active | — |
| `autob` | string | no | BLE reference device (MAC) | — |

### B.4 Write-Only Fields

| Key | Type | RW | Label | Command topic | Note |
|---|---|---|---|---|---|
| `env_set` | number | yes | Room temp (control injection) | `/control` (JSON: `{"env":val}`) | **Must be sent cyclically (30–60 s)** |

### B.5 BLE Sensor Fields (Conditional — only if `bleenable = true` and sensor in range)

| Key | Type | RW | Label | Unit |
|---|---|---|---|---|
| `ble_temp` | number | no | BLE sensor temperature | °C |
| `ble_hum` | number | no | BLE sensor humidity | % |
| `ble_bat` | number | no | BLE sensor battery | % |
| `ble_volt` | number | no | BLE sensor battery voltage | V |

---

## 21. Appendix C – Example Payloads

### C.1 Full Schema Payload (Device with BLE, All Standard Fields Active)

Based on actual hardware device `3eb5ebcd` (Faikout-S3-MINI-N8, from openCCU screenshot 2026-08-24):

```json
{
  "spec":    "FAIKOUT-SPEC-MQTT-SCHEMA-001/0.2",
  "model":   "Faikout-S3-MINI-N8",
  "version": "2026-08-14T16:21:44",
  "status":  "state/3eb5ebcd/status",
  "command": "command/3eb5ebcd/control",
  "fields": [
    { "key": "power",       "type": "bool",   "rw": true,  "label": "Power" },
    { "key": "mode",        "type": "string", "rw": true,  "label": "Mode",              "commandTopic": "command/3eb5ebcd/mode",     "values": ["H","C","A","D","F"] },
    { "key": "fan",         "type": "string", "rw": true,  "label": "Fan Speed",         "commandTopic": "command/3eb5ebcd/fan",      "values": ["A","1","2","3","4","5","Q"] },
    { "key": "temp",        "type": "number", "rw": true,  "label": "Setpoint",          "min": 16, "max": 30, "unit": "°C" },
    { "key": "swingv",      "type": "bool",   "rw": true,  "label": "Vertical Swing" },
    { "key": "swingh",      "type": "bool",   "rw": true,  "label": "Horizontal Swing" },
    { "key": "econo",       "type": "bool",   "rw": true,  "label": "Economy Mode",      "commandTopic": "command/3eb5ebcd/econo" },
    { "key": "powerful",    "type": "bool",   "rw": true,  "label": "Powerful Mode",     "commandTopic": "command/3eb5ebcd/powerful" },
    { "key": "comfort",     "type": "bool",   "rw": true,  "label": "Comfort Mode",      "commandTopic": "command/3eb5ebcd/comfort" },
    { "key": "quiet",       "type": "bool",   "rw": true,  "label": "Quiet Mode",        "commandTopic": "command/3eb5ebcd/quiet" },
    { "key": "demand",      "type": "number", "rw": true,  "label": "Compressor Load",   "commandTopic": "command/3eb5ebcd/demand",   "min": 0, "max": 100, "unit": "%" },
    { "key": "autoe",       "type": "bool",   "rw": true,  "label": "Auto Mode",         "commandTopic": "command/3eb5ebcd/autoe" },
    { "key": "autot",       "type": "number", "rw": true,  "label": "Auto Target Temp",  "commandTopic": "setting/3eb5ebcd/autot",    "unit": "°C" },
    { "key": "autor",       "type": "number", "rw": true,  "label": "Hysteresis",        "commandTopic": "setting/3eb5ebcd/autor",    "unit": "°C" },
    { "key": "home",        "type": "number", "rw": false, "label": "Indoor Temp",       "unit": "°C" },
    { "key": "outside",     "type": "number", "rw": false, "label": "Outdoor Temp",      "unit": "°C" },
    { "key": "liquid",      "type": "number", "rw": false, "label": "Refrigerant Temp",  "unit": "°C" },
    { "key": "hum",         "type": "number", "rw": false, "label": "Humidity",          "unit": "%" },
    { "key": "comp",        "type": "number", "rw": false, "label": "Compressor Speed",  "unit": "Hz" },
    { "key": "fanrpm",      "type": "number", "rw": false, "label": "Fan Speed",         "unit": "RPM" },
    { "key": "consumption", "type": "number", "rw": false, "label": "Power Consumption", "unit": "W" },
    { "key": "Whheating",   "type": "number", "rw": false, "label": "Heating Energy",    "unit": "Wh" },
    { "key": "Whcooling",   "type": "number", "rw": false, "label": "Cooling Energy",    "unit": "Wh" },
    { "key": "env",         "type": "number", "rw": false, "label": "Room Temp (ref.)",  "unit": "°C" },
    { "key": "env_set",     "type": "number", "rw": true,  "label": "Room Temp (inject)","unit": "°C" },
    { "key": "ble_temp",    "type": "number", "rw": false, "label": "BLE Temperature",   "unit": "°C" },
    { "key": "ble_hum",     "type": "number", "rw": false, "label": "BLE Humidity",      "unit": "%" },
    { "key": "ble_bat",     "type": "number", "rw": false, "label": "BLE Battery",       "unit": "%" }
  ]
}
```

### C.2 Corresponding Status Payload (Real Hardware Values from openCCU Screenshot)

```json
{
  "power":   false,
  "mode":    "H",
  "fan":     "A",
  "temp":    23,
  "home":    22.5,
  "hum":     50,
  "liquid":  21,
  "outside": 22,
  "demand":  0,
  "ble_temp": 22.19,
  "ble_hum":  47.04,
  "ble_bat":  48
}
```

*Values from openCCU prototype screenshot 2026-08-24: Home 22.5°C, Humidity 50%, Liquid 21°C, Outside 22°C, BLE Temp 22.19°C, BLE Hum 47.04%, BLE Bat 48%, Demand 0%.*

---

## 22. Appendix D – Glossary

| Term | Definition |
|---|---|
| ACL | Access Control List — broker-level topic access restriction per client |
| Broker | MQTT message broker (e.g. Mosquitto, EMQX) |
| CONNACK | MQTT connection acknowledgement packet |
| ESP32 | Espressif ESP32 series microcontroller — platform for Faikout firmware |
| Faikout | ESP32-based MQTT-connected HVAC controller firmware by RevK |
| HVAC | Heating, Ventilation and Air Conditioning |
| ioBroker | Open-source home automation platform (Node.js) |
| JSON | JavaScript Object Notation — RFC 8259 |
| MQTT | Message Queuing Telemetry Transport — lightweight pub/sub protocol |
| Node-RED | Flow-based visual programming tool for IoT |
| openCCU | Community variant of Homematic CCU3 firmware |
| openHAB | Open Home Automation Bus — open-source automation platform (Java) |
| QoS | MQTT Quality of Service level (0, 1, or 2) |
| ReGa | HomeMatic scripting language used for CCU system variable management |
| Redmatic | Node-RED distribution for Homematic CCU |
| Retained | MQTT retain flag — broker stores message for future subscribers |
| RevK | Author and maintainer of the ESP32-Faikout firmware |
| TLS | Transport Layer Security |
| WoT | W3C Web of Things |

---

*End of document.*  
*FAIKOUT-SPEC-MQTT-SCHEMA-001 / Draft 0.2 / September 2026 / RaW07*
