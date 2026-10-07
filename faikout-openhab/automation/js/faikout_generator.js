'use strict';

// ================================================================
// faikout_generator.js
// openHAB GraalVM JS – Faikout MQTT Integration Generator
//
// Place this file in: /etc/openhab/automation/js/
//
// Runs on system startup. Queries the Faikout HTTP API to detect
// which features are active, then creates:
//   - A MQTT Broker Thing
//   - A Generic MQTT Thing for the Faikout with per-feature channels
//   - Items linked to those channels
//
// All Things and Items are created via the openHAB REST API and
// stored in the internal JSON database (not in .things/.items files).
// Re-running the script is safe – existing entries are updated.
// ================================================================

const { rules, triggers, actions } = require('openhab');

// ================================================================
// CONFIGURATION – adjust to your setup
// ================================================================
const CFG = {
  faikoutHost:    '9C139EEF6D28',
  mqttBrokerHost: '192.168.7.20',
  mqttBrokerPort: 1884,
  mqttUsername:   '',
  mqttPassword:   '',
  ohRestUrl:      'http://localhost:8080/rest',
  ohApiToken:     'oh.claude.i3gIpRK2HwXmOEDpFWpFN53Xys5BkAgLkAaDlOY9tVGE2Zqg9EM0LtmGoC9FL6v1jlWOqh2d0Hvhp3qldw',
  itemPrefix:     'Faikout',
  brokerUID:      'mqtt:broker:faikout-broker',
  deviceUID:      'mqtt:topic:faikout-broker:faikout',
};

// ================================================================
// MQTT TOPICS
// ================================================================
const STATUS_TOPIC  = 'status/'  + CFG.faikoutHost;
const COMMAND_TOPIC = 'command/' + CFG.faikoutHost + '/control';

// ================================================================
// CHANNEL DEFINITIONS
// All known Faikout fields. The generator queries the Faikout HTTP
// API and only creates channels for fields present in the response.
// ================================================================
//  id        label                  itemType  jsonKey    writable
const CHANNELS = [
  { id: 'power',    label: 'Power',            type: 'Switch', key: 'power',    rw: true  },
  { id: 'mode',     label: 'Mode',             type: 'String', key: 'mode',     rw: true  },
  { id: 'fan',      label: 'Fan Speed',        type: 'String', key: 'fan',      rw: true  },
  { id: 'temp',     label: 'Target Temp',      type: 'Number', key: 'temp',     rw: true  },
  { id: 'home',     label: 'Return Air Temp',  type: 'Number', key: 'home',     rw: false },
  { id: 'env',      label: 'External Temp',    type: 'Number', key: 'env',      rw: false },
  { id: 'inlet',    label: 'Inlet Temp',       type: 'Number', key: 'inlet',    rw: false },
  { id: 'liquid',   label: 'Liquid Temp',      type: 'Number', key: 'liquid',   rw: false },
  { id: 'louvre',   label: 'Louvre',           type: 'String', key: 'louvre',   rw: true  },
  { id: 'swingh',   label: 'Swing Horizontal', type: 'Switch', key: 'swingh',   rw: true  },
  { id: 'swingv',   label: 'Swing Vertical',   type: 'Switch', key: 'swingv',   rw: true  },
  { id: 'powerful', label: 'Powerful',         type: 'Switch', key: 'powerful', rw: true  },
  { id: 'econo',    label: 'Econo',            type: 'Switch', key: 'econo',    rw: true  },
  { id: 'streamer', label: 'Streamer',         type: 'Switch', key: 'streamer', rw: true  },
  { id: 'comfort',  label: 'Comfort Airflow',  type: 'Switch', key: 'comfort',  rw: true  },
  { id: 'demand',   label: 'Demand Control',   type: 'Switch', key: 'demand',   rw: true  },
  { id: 'slave',    label: 'Slave Mode',       type: 'Switch', key: 'slave',    rw: false },
];

// ================================================================
// REST HELPERS
// ================================================================
function buildHeaders() {
  const h = { 'Content-Type': 'application/json', 'Accept': 'application/json' };
  if (CFG.ohApiToken) h['Authorization'] = 'Bearer ' + CFG.ohApiToken;
  return h;
}

function ohGet(path) {
  try {
    return actions.HTTP.sendHttpGetRequest(CFG.ohRestUrl + path, buildHeaders(), 5000);
  } catch (e) {
    console.error('[faikout-gen] GET ' + path + ' failed: ' + e);
    return null;
  }
}

function ohPost(path, body) {
  try {
    return actions.HTTP.sendHttpPostRequest(
      CFG.ohRestUrl + path, 'application/json', JSON.stringify(body), buildHeaders(), 5000
    );
  } catch (e) {
    console.error('[faikout-gen] POST ' + path + ' failed: ' + e);
    return null;
  }
}

function ohPut(path, body) {
  try {
    return actions.HTTP.sendHttpPutRequest(
      CFG.ohRestUrl + path, 'application/json', JSON.stringify(body), buildHeaders(), 5000
    );
  } catch (e) {
    console.error('[faikout-gen] PUT ' + path + ' failed: ' + e);
    return null;
  }
}

// ================================================================
// FAIKOUT HTTP API – detect active features
// ================================================================
function fetchFaikoutStatus() {
  // Faikout exposes device state at /api (RevK firmware convention).
  // If this returns null or HTML, adjust the endpoint to /status.
  const url = 'http://' + CFG.faikoutHost + '/api';
  console.log('[faikout-gen] Querying Faikout at ' + url);
  try {
    const raw = actions.HTTP.sendHttpGetRequest(url, 5000);
    if (raw) return JSON.parse(raw);
  } catch (e) {
    console.warn('[faikout-gen] Faikout not reachable: ' + e);
  }
  return null;
}

// ================================================================
// MQTT BROKER THING
// ================================================================
function ensureBrokerThing() {
  const existing = ohGet('/things/' + encodeURIComponent(CFG.brokerUID));
  if (existing && !existing.includes('"error"')) {
    console.log('[faikout-gen] Broker Thing exists, skipping creation.');
    return;
  }
  const body = {
    UID:           CFG.brokerUID,
    thingTypeUID:  'mqtt:broker',
    label:         'Faikout MQTT Broker',
    configuration: {
      host:     CFG.mqttBrokerHost,
      port:     CFG.mqttBrokerPort,
      secure:   false,
      clientId: 'openhab-faikout',
      ...(CFG.mqttUsername && { username: CFG.mqttUsername }),
      ...(CFG.mqttPassword && { password: CFG.mqttPassword }),
    },
    channels: [],
  };
  console.log('[faikout-gen] Creating Broker Thing...');
  ohPost('/things', body);
}

// ================================================================
// GENERIC MQTT DEVICE THING WITH CHANNELS
// ================================================================
function channelTypeUID(type) {
  return type === 'Number' ? 'mqtt:number'
       : type === 'Switch' ? 'mqtt:switch'
       : 'mqtt:string';
}

function channelConfig(ch) {
  const cfg = {
    stateTopic:            STATUS_TOPIC,
    transformationPattern: 'JSONPATH:$.' + ch.key,
  };
  if (ch.rw) {
    cfg.commandTopic = COMMAND_TOPIC;
    // Switch channels: Faikout expects true/false (not ON/OFF)
    if (ch.type === 'Switch') {
      cfg.on  = 'true';
      cfg.off = 'false';
      cfg.formatBeforePublish = '{"' + ch.key + '": %s}';
    } else if (ch.type === 'Number') {
      // Numeric payload, unquoted: {"temp": 22}
      cfg.formatBeforePublish = '{"' + ch.key + '": %s}';
    } else {
      // String payload, quoted: {"mode": "C"}
      cfg.formatBeforePublish = '{"' + ch.key + '": "%s"}';
    }
  }
  return cfg;
}

function ensureDeviceThing(activeChannels) {
  const channelList = activeChannels.map(ch => ({
    uid:            CFG.deviceUID + ':' + ch.id,
    id:             ch.id,
    channelTypeUID: channelTypeUID(ch.type),
    label:          ch.label,
    configuration:  channelConfig(ch),
    properties:     {},
    defaultTags:    [],
  }));

  const body = {
    UID:           CFG.deviceUID,
    thingTypeUID:  'mqtt:topic',
    label:         'Faikout (' + CFG.faikoutHost + ')',
    bridgeUID:     CFG.brokerUID,
    configuration: {},
    channels:      channelList,
  };

  const existing = ohGet('/things/' + encodeURIComponent(CFG.deviceUID));
  if (existing && !existing.includes('"error"')) {
    console.log('[faikout-gen] Updating Device Thing (' + activeChannels.length + ' channels)...');
    ohPut('/things/' + encodeURIComponent(CFG.deviceUID), body);
  } else {
    console.log('[faikout-gen] Creating Device Thing (' + activeChannels.length + ' channels)...');
    ohPost('/things', body);
  }
}

// ================================================================
// ITEMS + CHANNEL LINKS
// ================================================================
function itemName(ch) {
  return CFG.itemPrefix + '_' + ch.id.charAt(0).toUpperCase() + ch.id.slice(1);
}

function ensureItem(ch) {
  const name = itemName(ch);
  const body = {
    name:     name,
    type:     ch.type,
    label:    'Faikout ' + ch.label,
    category: ch.type === 'Number' ? 'Temperature' : '',
    tags:     [],
  };
  console.log('[faikout-gen] Ensuring Item: ' + name);
  ohPut('/items/' + name, body);
  return name;
}

function ensureLink(name, channelUID) {
  ohPut('/links/' + encodeURIComponent(name) + '/' + encodeURIComponent(channelUID), {
    itemName:      name,
    channelUID:    channelUID,
    configuration: {},
  });
}

// ================================================================
// MAIN
// ================================================================
function generate() {
  console.log('[faikout-gen] === Faikout Integration Generator starting ===');

  // 1. Detect active features via Faikout HTTP API
  const status = fetchFaikoutStatus();
  let activeChannels;
  if (status) {
    activeChannels = CHANNELS.filter(ch => ch.key in status && status[ch.key] !== null);
    console.log('[faikout-gen] Active channels: ' + activeChannels.map(c => c.id).join(', '));
  } else {
    // Fallback: generate all channels if Faikout is not reachable at startup
    console.warn('[faikout-gen] Faikout unreachable – generating all channels as fallback.');
    activeChannels = CHANNELS;
  }

  // 2. MQTT Broker Thing
  ensureBrokerThing();

  // 3. Faikout Device Thing with detected channels
  ensureDeviceThing(activeChannels);

  // 4. Items + channel links
  for (const ch of activeChannels) {
    const name = ensureItem(ch);
    ensureLink(name, CFG.deviceUID + ':' + ch.id);
  }

  console.log('[faikout-gen] === Done. ' + activeChannels.length + ' channel(s) created/updated. ===');
}

// ================================================================
// RULE – runs once when openHAB is fully started
// ================================================================
rules.JSRule({
  name:        'Faikout Integration Generator',
  description: 'Generates MQTT Things and Items for Faikout on startup',
  triggers:    [triggers.SystemStartlevelTrigger(100)],
  execute:     generate,
});
