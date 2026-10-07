// Settings
// Generated from:-
// /home/raw/faikout-projects/faikout-Modifications/main/settings.def
// /home/raw/faikout-projects/faikout-Modifications/components/ESP32-RevK/settings.def

#include <stdint.h>
#include "sdkconfig.h"
#include "settings.h"
revk_settings_bits_t revk_settings_bits={0};
#define	str(s)	#s
#define	quote(s)	str(s)
revk_settings_t const revk_settings[]={
 {.type=REVK_SETTINGS_BIT,.name="dump",.comment="Dump protocol on MQTT for each message",.len=4,.bit=REVK_SETTINGS_BITFIELD_dump},
 {.type=REVK_SETTINGS_BIT,.name="debug",.comment="Debug - logs summary of status responses",.len=5,.bit=REVK_SETTINGS_BITFIELD_debug,.live=1,.hide=1},
 {.type=REVK_SETTINGS_BIT,.name="debughex",.comment="Debug in hex",.len=8,.bit=REVK_SETTINGS_BITFIELD_debughex,.live=1},
 {.type=REVK_SETTINGS_BIT,.name="snoop",.comment="Listen only (for debugging)",.len=5,.bit=REVK_SETTINGS_BITFIELD_snoop},
 {.type=REVK_SETTINGS_BIT,.name="livestatus",.comment="Send status messages in real time",.len=10,.bit=REVK_SETTINGS_BITFIELD_livestatus,.live=1},
 {.type=REVK_SETTINGS_BIT,.name="fixstatus",.comment="Send status as fixed values not array",.len=9,.bit=REVK_SETTINGS_BITFIELD_fixstatus},
 {.type=REVK_SETTINGS_BIT,.name="s21extra",.comment="Sends extra S21 messages, usually used with dump or debug",.group=1,.len=8,.dot=3,.bit=REVK_SETTINGS_BITFIELD_s21extra,.live=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="s21tries",.comment="Repeat attempts at S21 controls",.group=1,.len=8,.dot=3,.def="10",.ptr=&s21tries,.size=sizeof(uint8_t),.live=1},
 {.type=REVK_SETTINGS_BIT,.name="webcontrol",.comment="Web based controls",.group=2,.len=10,.dot=3,.def="1",.bit=REVK_SETTINGS_BITFIELD_webcontrol},
 {.type=REVK_SETTINGS_BIT,.name="websettings",.comment="Web based settings",.group=2,.len=11,.dot=3,.def="1",.bit=REVK_SETTINGS_BITFIELD_websettings},
 {.type=REVK_SETTINGS_STRING,.name="model",.comment="Set model name manually",.len=5,.ptr=&model,.malloc=1},
 {.type=REVK_SETTINGS_STRING,.name="region",.comment="Region (legacy URLs)",.len=6,.def="eu",.ptr=&region,.malloc=1},
 {.type=REVK_SETTINGS_BIT,.name="fahrenheit",.comment="Web shows Fahrenheit",.len=10,.bit=REVK_SETTINGS_BITFIELD_fahrenheit,.live=1},
 {.type=REVK_SETTINGS_BIT,.name="nos21",.comment="Do not try S21 protocol",.group=3,.len=5,.dot=2,.bit=REVK_SETTINGS_BITFIELD_nos21,.live=1,.fix=1},
 {.type=REVK_SETTINGS_BIT,.name="nox50a",.comment="Do not try X50A protocol",.group=3,.len=6,.dot=2,.bit=REVK_SETTINGS_BITFIELD_nox50a,.live=1,.fix=1},
 {.type=REVK_SETTINGS_BIT,.name="nocnwired",.comment="Do not try CN_WIRED protocol",.group=3,.len=9,.dot=2,.def="1",.bit=REVK_SETTINGS_BITFIELD_nocnwired,.live=1,.fix=1},
 {.type=REVK_SETTINGS_BIT,.name="noas",.comment="Do not try (experimental) Altherma_S protocol",.group=3,.len=4,.dot=2,.def="1",.bit=REVK_SETTINGS_BITFIELD_noas,.live=1,.fix=1},
 {.type=REVK_SETTINGS_BIT,.name="noswaptx",.comment="Do not try inverted Tx (use GPIO setting only)",.group=3,.len=8,.dot=2,.bit=REVK_SETTINGS_BITFIELD_noswaptx,.live=1,.fix=1},
 {.type=REVK_SETTINGS_BIT,.name="noswaprx",.comment="Do not try inverted Rx (use GPIO setting only)",.group=3,.len=8,.dot=2,.bit=REVK_SETTINGS_BITFIELD_noswaprx,.live=1,.fix=1},
 {.type=REVK_SETTINGS_BIT,.name="nodemand",.comment="Disable demand control",.group=3,.len=8,.dot=2,.bit=REVK_SETTINGS_BITFIELD_nodemand},
 {.type=REVK_SETTINGS_BIT,.name="noauto",.comment="Unit does not have auto mode",.group=3,.len=6,.dot=2,.bit=REVK_SETTINGS_BITFIELD_noauto},
 {.type=REVK_SETTINGS_BIT,.name="noecono",.comment="Unit does not have econo mode",.group=3,.len=7,.dot=2,.bit=REVK_SETTINGS_BITFIELD_noecono},
 {.type=REVK_SETTINGS_BIT,.name="noswingv",.comment="Unit does not have swing (V)",.group=3,.len=8,.dot=2,.bit=REVK_SETTINGS_BITFIELD_noswingv,.old="noswingw"},
 {.type=REVK_SETTINGS_BIT,.name="noswingh",.comment="Unit does not have swing (H)",.group=3,.len=8,.dot=2,.bit=REVK_SETTINGS_BITFIELD_noswingh},
 {.type=REVK_SETTINGS_BIT,.name="nocomfort",.comment="Unit does not have comfort mode",.group=3,.len=9,.dot=2,.bit=REVK_SETTINGS_BITFIELD_nocomfort},
 {.type=REVK_SETTINGS_BIT,.name="nostreamer",.comment="Unit does not have streamer mode",.group=3,.len=10,.dot=2,.bit=REVK_SETTINGS_BITFIELD_nostreamer},
 {.type=REVK_SETTINGS_BIT,.name="nopowerful",.comment="Unit does not have powerful mode",.group=3,.len=10,.dot=2,.bit=REVK_SETTINGS_BITFIELD_nopowerful},
 {.type=REVK_SETTINGS_BIT,.name="nosensor",.comment="Unit does not have sensor mode",.group=3,.len=8,.dot=2,.bit=REVK_SETTINGS_BITFIELD_nosensor},
 {.type=REVK_SETTINGS_BIT,.name="noquiet",.comment="Unit does not have quiet mode",.group=3,.len=7,.dot=2,.bit=REVK_SETTINGS_BITFIELD_noquiet},
 {.type=REVK_SETTINGS_BIT,.name="noled",.comment="Unit does not have LED control",.group=3,.len=5,.dot=2,.def="1",.bit=REVK_SETTINGS_BITFIELD_noled},
 {.type=REVK_SETTINGS_BIT,.name="noflap",.comment="Unit does not have flap mode",.group=3,.len=6,.dot=2,.bit=REVK_SETTINGS_BITFIELD_noflap},
 {.type=REVK_SETTINGS_BIT,.name="noantifreeze",.comment="Unit does not have antifreeze mode",.group=3,.len=12,.dot=2,.bit=REVK_SETTINGS_BITFIELD_noantifreeze},
 {.type=REVK_SETTINGS_BIT,.name="nohumidity",.comment="Unit does not have humidity",.group=3,.len=10,.dot=2,.bit=REVK_SETTINGS_BITFIELD_nohumidity},
 {.type=REVK_SETTINGS_BIT,.name="nohumidify",.comment="Unit does not have humidifier",.group=3,.len=10,.dot=2,.def="1",.bit=REVK_SETTINGS_BITFIELD_nohumidify},
 {.type=REVK_SETTINGS_BIT,.name="nohourly",.comment="Do not do hourly S21 poll (DH)",.group=3,.len=8,.dot=2,.def="1",.bit=REVK_SETTINGS_BITFIELD_nohourly,.live=1},
 {.type=REVK_SETTINGS_BIT,.name="nofaikoutauto",.comment="Do not show Faikout auto controls (unless already set up and no password)",.group=3,.len=13,.dot=2,.bit=REVK_SETTINGS_BITFIELD_nofaikoutauto,.live=1,.old="nofaikinauto"},
 {.type=REVK_SETTINGS_BIT,.name="nohvacaction",.comment="Do not track/report hvac_action for Faikout auto mode in HA",.group=3,.len=12,.dot=2,.def="1",.bit=REVK_SETTINGS_BITFIELD_nohvacaction},
 {.type=REVK_SETTINGS_BIT,.name="nofanauto",.comment="Do not control fan in Faikout auto mode",.group=3,.len=9,.dot=2,.bit=REVK_SETTINGS_BITFIELD_nofanauto},
 {.type=REVK_SETTINGS_BIT,.name="nohomepreset",.comment="Do not include a home in HA preset list",.group=3,.len=12,.dot=2,.bit=REVK_SETTINGS_BITFIELD_nohomepreset},
 {.type=REVK_SETTINGS_BIT,.name="noicons",.comment="Do not show icons on web UI",.group=3,.len=7,.dot=2,.bit=REVK_SETTINGS_BITFIELD_noicons,.live=1},
 {.type=REVK_SETTINGS_BIT,.name="udpdiscovery",.comment="Enable Daikin BRP-compatible UDP discovery",.group=4,.len=12,.dot=3,.bit=REVK_SETTINGS_BITFIELD_udpdiscovery,.old="udp_discovery"},
 {.type=REVK_SETTINGS_BIT,.name="haenable",.comment="Home Assistant",.group=5,.len=8,.dot=2,.def="1",.bit=REVK_SETTINGS_BITFIELD_haenable,.old="ha"},
 {.type=REVK_SETTINGS_BIT,.name="haswitches",.comment="Set additional HA switches",.group=5,.len=10,.dot=2,.bit=REVK_SETTINGS_BITFIELD_haswitches},
 {.type=REVK_SETTINGS_BIT,.name="hafanrpm",.comment="Use RPM not Hz for HA fan speed",.group=5,.len=8,.dot=2,.bit=REVK_SETTINGS_BITFIELD_hafanrpm},
 {.type=REVK_SETTINGS_BIT,.name="hacomprpm",.comment="Use RPM not Hz for HA comp speed",.group=5,.len=9,.dot=2,.bit=REVK_SETTINGS_BITFIELD_hacomprpm},
 {.type=REVK_SETTINGS_BIT,.name="ha1c",.comment="Force 1C steps in HA temp setting",.group=5,.len=4,.dot=2,.bit=REVK_SETTINGS_BITFIELD_ha1c},
 {.type=REVK_SETTINGS_BIT,.name="haperiodic",.comment="Reduce HA updates",.group=5,.len=10,.dot=2,.bit=REVK_SETTINGS_BITFIELD_haperiodic},
 {.type=REVK_SETTINGS_BIT,.name="haram",.comment="Log memory usage",.group=5,.len=5,.dot=2,.bit=REVK_SETTINGS_BITFIELD_haram},
 {.type=REVK_SETTINGS_BIT,.name="hauptime",.comment="Log uptime",.group=5,.len=8,.dot=2,.bit=REVK_SETTINGS_BITFIELD_hauptime},
 {.type=REVK_SETTINGS_STRING,.name="hadomain",.comment="Local domain for HA links (blank for IP)",.group=5,.len=8,.dot=2,.def="local",.ptr=&hadomain,.malloc=1},
 {.type=REVK_SETTINGS_BIT,.name="cnmark900",.comment="CN_WIRED. mark using 900uS not 1000uS",.group=6,.len=9,.dot=2,.bit=REVK_SETTINGS_BITFIELD_cnmark900,.live=1},
 {.type=REVK_SETTINGS_UNSIGNED,.isenum=1,.name="fantype",.comment="Fan type override",.len=7,.ptr=&fantype,.size=sizeof(uint8_t),.enums=REVK_SETTINGS_FANTYPE_ENUMS,.old="fanstep"},
 {.type=REVK_SETTINGS_BIT,.name="lockmode",.comment="Do not auto switch heat/cool modes in Faikout auto",.len=8,.bit=REVK_SETTINGS_BITFIELD_lockmode},
 {.type=REVK_SETTINGS_UNSIGNED,.name="protocol",.comment="Internal protocol as found, saved when found, can be used with protofix",.len=8,.ptr=&protocol,.size=sizeof(uint8_t),.hide=1},
 {.type=REVK_SETTINGS_BIT,.name="protofix",.comment="Protofix forces no change, use nos21, nox50a, etc instead maybe",.len=8,.bit=REVK_SETTINGS_BITFIELD_protofix,.hide=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="reporting",.comment="Status report period (s)",.len=9,.def="60",.ptr=&reporting,.size=sizeof(uint32_t)},
 {.type=REVK_SETTINGS_UNSIGNED,.name="uart",.comment="UART number",.len=4,.def="1",.ptr=&uart,.size=sizeof(uint8_t),.fix=1,.hide=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="thermref",.comment="Percentage inlet rather than home temp used by your aircon",.len=8,.def="50",.ptr=&thermref,.size=sizeof(uint8_t),.live=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="switchtemp",.comment="Increase max (heating) or decrease min (cooling)",.len=10,.def="0.5",.ptr=&switchtemp,.size=sizeof(uint8_t),.live=1,.decimal=1,.unit="℃",.old="switch10"},
 {.type=REVK_SETTINGS_UNSIGNED,.name="pushtemp",.comment="Increase min (heating) or decrease max (cooling)",.len=8,.def="0.1",.ptr=&pushtemp,.size=sizeof(uint8_t),.live=1,.decimal=1,.unit="℃",.old="push10"},
 {.type=REVK_SETTINGS_SIGNED,.name="coolover",.comment="For cooling, push (decrease) target sent to aircon by this from min to force cooling before reaching target",.group=7,.len=8,.dot=4,.def="6",.ptr=&coolover,.size=sizeof(int8_t),.live=1,.unit="℃"},
 {.type=REVK_SETTINGS_UNSIGNED,.name="coolback",.comment="For cooling, pull (increase) target sent to aircon by this from max to stop cooling after reaching target",.group=7,.len=8,.dot=4,.def="6",.ptr=&coolback,.size=sizeof(uint8_t),.live=1,.unit="℃"},
 {.type=REVK_SETTINGS_SIGNED,.name="heatover",.comment="For heating, push (increase) target sent to aircon by this from max to force heating before reaching target",.group=8,.len=8,.dot=4,.def="6",.ptr=&heatover,.size=sizeof(int8_t),.live=1,.unit="℃"},
 {.type=REVK_SETTINGS_UNSIGNED,.name="heatback",.comment="For heating, pull (decrease) target sent to aircon by this from min to stop heating after reaching target",.group=8,.len=8,.dot=4,.def="6",.ptr=&heatback,.size=sizeof(uint8_t),.live=1,.unit="℃"},
 {.type=REVK_SETTINGS_SIGNED,.name="minoutside",.comment="Lowest allowed outside temp allowed for operation (if known)",.group=9,.len=10,.dot=3,.def="-100",.ptr=&minoutside,.size=sizeof(int8_t),.live=1,.unit="℃"},
 {.type=REVK_SETTINGS_SIGNED,.name="frosttemp",.comment="Frost protect (below this, turn on hot regardless)",.len=9,.def="-100",.ptr=&frosttemp,.size=sizeof(int8_t),.live=1,.unit="℃"},
 {.type=REVK_SETTINGS_BIT,.name="temptrack",.comment="Set target temp based on Daikin measured temp not required target",.group=10,.len=9,.dot=4,.def="0",.bit=REVK_SETTINGS_BITFIELD_temptrack,.live=1},
 {.type=REVK_SETTINGS_BIT,.name="tempadjust",.comment="Adjust target temp allowing for different Daikin measure to external measure",.group=10,.len=10,.dot=4,.def="1",.bit=REVK_SETTINGS_BITFIELD_tempadjust,.live=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="tempnoflap",.comment="Min time between target temp changes",.group=10,.len=10,.dot=4,.def="0",.ptr=&tempnoflap,.size=sizeof(uint16_t),.live=1,.unit="s"},
#ifdef CONFIG_BT_NIMBLE_ENABLED
 {.type=REVK_SETTINGS_BIT,.name="bleenable",.comment="Enable BLE for sensors or remote",.group=11,.len=9,.dot=3,.bit=REVK_SETTINGS_BITFIELD_bleenable,.hide=1,.old="ble"},
 {.type=REVK_SETTINGS_STRING,.name="autob",.comment="BLE sensor ID",.group=12,.len=5,.dot=4,.ptr=&autob,.malloc=1,.live=1},
#endif
 {.type=REVK_SETTINGS_BIT,.name="autoe",.comment="Enable auto time and power operations",.group=12,.len=5,.dot=4,.def="1",.bit=REVK_SETTINGS_BITFIELD_autoe,.live=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="auto0",.comment="HHMM format turn off time",.group=12,.len=5,.dot=4,.ptr=&auto0,.size=sizeof(uint16_t),.live=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="auto1",.comment="HHMM format turn on time",.group=12,.len=5,.dot=4,.ptr=&auto1,.size=sizeof(uint16_t),.live=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="autot",.comment="Faikout auto target temperature",.group=12,.len=5,.dot=4,.ptr=&autot,.size=sizeof(uint16_t),.live=1,.decimal=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="autor",.comment="Faikout auto margin either side of autot",.group=12,.len=5,.dot=4,.ptr=&autor,.size=sizeof(uint8_t),.live=1,.decimal=1},
 {.type=REVK_SETTINGS_BIT,.name="autop",.comment="Enable auto power on/off (regardless of times)",.group=12,.len=5,.dot=4,.bit=REVK_SETTINGS_BITFIELD_autop,.live=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="autofmax",.comment="Max fan setting when starting heat/cool way off from target",.group=12,.len=8,.dot=4,.def="5",.ptr=&autofmax,.size=sizeof(uint8_t),.live=1,.old="fmaxauto"},
 {.type=REVK_SETTINGS_UNSIGNED,.name="autoptemp",.comment="Auto power on/off by temperature deviation by this amount",.group=12,.len=9,.dot=4,.def="0.5",.ptr=&autoptemp,.size=sizeof(uint8_t),.live=1,.decimal=1,.old="autop10"},
 {.type=REVK_SETTINGS_BIT,.name="autolcontrol",.comment="Auto toggle on/off LED based on current HVAC action",.group=12,.len=12,.dot=4,.def="0",.bit=REVK_SETTINGS_BITFIELD_autolcontrol,.live=1},
 {.type=REVK_SETTINGS_STRING,.name="autotopic",.comment="Topic to follow for reference temperature for Faikout auto",.group=12,.len=9,.dot=4,.ptr=&autotopic,.malloc=1},
 {.type=REVK_SETTINGS_STRING,.name="autopayload",.comment="JSON field in payload of above topic for reference temp",.group=12,.len=11,.dot=4,.ptr=&autopayload,.malloc=1},
 {.type=REVK_SETTINGS_BIT,.name="thermostat",.comment="Faikout auto simple thermostat mode (heat to max, cool to min)",.len=10,.bit=REVK_SETTINGS_BITFIELD_thermostat,.live=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="tmin",.comment="Min temp setting of system",.group=13,.len=4,.dot=1,.def="16",.ptr=&tmin,.size=sizeof(uint8_t),.live=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="tcoolmin",.comment="Min temp setting for Faikout auto when cooling",.group=13,.len=8,.dot=1,.def="16",.ptr=&tcoolmin,.size=sizeof(uint8_t),.live=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="tmax",.comment="Max temp setting of system",.group=13,.len=4,.dot=1,.def="32",.ptr=&tmax,.size=sizeof(uint8_t),.live=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="theatmax",.comment="Max temp setting for Faikout auto when heating",.group=13,.len=8,.dot=1,.def="32",.ptr=&theatmax,.size=sizeof(uint8_t),.live=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="tpredicts",.comment="Temp prediction sample time",.group=13,.len=9,.dot=1,.def="30",.ptr=&tpredicts,.size=sizeof(uint32_t)},
 {.type=REVK_SETTINGS_UNSIGNED,.name="tpredictt",.comment="Temp prediction total time factor",.group=13,.len=9,.dot=1,.def="120",.ptr=&tpredictt,.size=sizeof(uint32_t)},
 {.type=REVK_SETTINGS_UNSIGNED,.name="tsample",.comment="Sample period for making adjustments",.group=13,.len=7,.dot=1,.def="900",.ptr=&tsample,.size=sizeof(uint32_t)},
 {.type=REVK_SETTINGS_UNSIGNED,.name="tcontrol",.comment="Control messages timeout",.group=13,.len=8,.dot=1,.def="600",.ptr=&tcontrol,.size=sizeof(uint32_t)},
#ifdef  CONFIG_IDF_TARGET_ESP32S3
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="tx",.comment="Tx",.len=2,.def="-48",.ptr=&tx,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕"},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="rx",.comment="Rx",.len=2,.def="-34",.ptr=&rx,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕"},
#else
#ifdef  CONFIG_IDF_TARGET_ESP32C5
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="tx",.comment="Tx",.len=2,.def="-26",.ptr=&tx,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕"},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="rx",.comment="Rx",.len=2,.def="-25",.ptr=&rx,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕"},
#else
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="tx",.comment="Tx",.len=2,.def="-26",.ptr=&tx,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕"},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="rx",.comment="Rx",.len=2,.def="-27",.ptr=&rx,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕"},
#endif
#endif
#if CONFIG_SOC_I2C_NUM > 1 // we need 2 I2C bus for master and slave
 {.type=REVK_SETTINGS_BIT,.name="i2cen",.comment="Enable I2C temp and humidity sensor spoofing",.group=14,.len=5,.dot=3,.def="0",.bit=REVK_SETTINGS_BITFIELD_i2cen},
 {.type=REVK_SETTINGS_SIGNED,.name="i2chtemp",.comment="Offset to add to external sensor temp to reflect inlet temp when heating",.group=14,.len=8,.dot=3,.def="4.0",.ptr=&i2chtemp,.size=sizeof(int8_t),.live=1,.decimal=1,.unit="℃"},
 {.type=REVK_SETTINGS_SIGNED,.name="i2cctemp",.comment="Offset to add to external sensor temp to reflect inlet temp when cooling",.group=14,.len=8,.dot=3,.def="-1.5",.ptr=&i2cctemp,.size=sizeof(int8_t),.live=1,.decimal=1,.unit="℃"},
#if defined(CONFIG_IDF_TARGET_ESP32C5)
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="i2cslsda",.comment="GPIO to use for I2C slave with Daikin board - SDA",.group=14,.len=8,.dot=3,.def="9",.ptr=&i2cslsda,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕"},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="i2cslscl",.comment="GPIO to use for I2C slave with Daikin board - SCL",.group=14,.len=8,.dot=3,.def="10",.ptr=&i2cslscl,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕"},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="i2cmasda",.comment="GPIO to use for I2C master with inlet sensor - SDA - always LP I2C pins on this target",.group=14,.len=8,.dot=3,.def="2",.ptr=&i2cmasda,.size=sizeof(revk_gpio_t),.set=1,.flags="- ~↓↕⇕",.fix=1,.hide=1},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="i2cmassl",.comment="GPIO to use for I2C master with inlet sensor - SCL - always LP I2C pins on this target",.group=14,.len=8,.dot=3,.def="3",.ptr=&i2cmassl,.size=sizeof(revk_gpio_t),.set=1,.flags="- ~↓↕⇕",.fix=1,.hide=1},
#elif defined(CONFIG_IDF_TARGET_ESP32C6)
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="i2cslsda",.comment="GPIO to use for I2C slave with Daikin board - SDA",.group=14,.len=8,.dot=3,.def="2",.ptr=&i2cslsda,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕"},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="i2cslscl",.comment="GPIO to use for I2C slave with Daikin board - SCL",.group=14,.len=8,.dot=3,.def="3",.ptr=&i2cslscl,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕"},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="i2cmasda",.comment="GPIO to use for I2C master with inlet sensor - SDA - always LP I2C pins on this target",.group=14,.len=8,.dot=3,.def="6",.ptr=&i2cmasda,.size=sizeof(revk_gpio_t),.set=1,.flags="- ~↓↕⇕",.fix=1,.hide=1},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="i2cmassl",.comment="GPIO to use for I2C master with inlet sensor - SCL - always LP I2C pins on this target",.group=14,.len=8,.dot=3,.def="7",.ptr=&i2cmassl,.size=sizeof(revk_gpio_t),.set=1,.flags="- ~↓↕⇕",.fix=1,.hide=1},
#elif !defined(CONFIG_REVK_ETHERNET)
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="i2cslsda",.comment="GPIO to use for I2C slave with Daikin board - SDA",.group=14,.len=8,.dot=3,.def="9",.ptr=&i2cslsda,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕"},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="i2cslscl",.comment="GPIO to use for I2C slave with Daikin board - SCL",.group=14,.len=8,.dot=3,.def="10",.ptr=&i2cslscl,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕"},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="i2cmasda",.comment="GPIO to use for I2C master with inlet sensor - SDA",.group=14,.len=8,.dot=3,.def="11",.ptr=&i2cmasda,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕"},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="i2cmassl",.comment="GPIO to use for I2C master with inlet sensor - SCL",.group=14,.len=8,.dot=3,.def="12",.ptr=&i2cmassl,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕"},
#else
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="i2cslsda",.comment="GPIO to use for I2C slave with Daikin board - SDA",.group=14,.len=8,.dot=3,.ptr=&i2cslsda,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕"},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="i2cslscl",.comment="GPIO to use for I2C slave with Daikin board - SCL",.group=14,.len=8,.dot=3,.ptr=&i2cslscl,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕"},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="i2cmasda",.comment="GPIO to use for I2C master with inlet sensor - SDA",.group=14,.len=8,.dot=3,.ptr=&i2cmasda,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕"},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="i2cmassl",.comment="GPIO to use for I2C master with inlet sensor - SCL",.group=14,.len=8,.dot=3,.ptr=&i2cmassl,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕"},
#endif
#endif
 {.type=REVK_SETTINGS_STRING,.name="xgpio1name",.comment="Label for Additional GPIO 1",.len=10,.ptr=&xgpio1name,.malloc=1,.hide=1},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="xgpio1",.comment="Additional GPIO 1 (not set = disabled)",.len=6,.ptr=&xgpio1,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕",.hide=1},
 {.type=REVK_SETTINGS_BIT,.name="xgpio1out",.comment="GPIO 1: Output (else Input)",.len=9,.def="0",.bit=REVK_SETTINGS_BITFIELD_xgpio1out,.hide=1},
 {.type=REVK_SETTINGS_BIT,.name="xgpio1pd",.comment="GPIO 1: Pull-Down (Input only)",.len=8,.def="0",.bit=REVK_SETTINGS_BITFIELD_xgpio1pd,.hide=1},
 {.type=REVK_SETTINGS_BIT,.name="xgpio1pwm",.comment="GPIO 1: PWM mode (implies output)",.len=9,.def="0",.bit=REVK_SETTINGS_BITFIELD_xgpio1pwm,.hide=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="xgpio1freq",.comment="GPIO 1: PWM frequency (Hz)",.len=10,.def="1000",.ptr=&xgpio1freq,.size=sizeof(uint16_t),.hide=1},
 {.type=REVK_SETTINGS_BIT,.name="xgpio1adc",.comment="GPIO 1: ADC mode (analog input, 0-100%)",.len=9,.def="0",.bit=REVK_SETTINGS_BITFIELD_xgpio1adc,.hide=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="xgpio1adct",.comment="GPIO 1: ADC change threshold to report (%)",.len=10,.def="5",.ptr=&xgpio1adct,.size=sizeof(uint8_t),.live=1,.hide=1},
 {.type=REVK_SETTINGS_STRING,.name="xgpio2name",.comment="Label for Additional GPIO 2",.len=10,.ptr=&xgpio2name,.malloc=1,.hide=1},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="xgpio2",.comment="Additional GPIO 2",.len=6,.ptr=&xgpio2,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕",.hide=1},
 {.type=REVK_SETTINGS_BIT,.name="xgpio2out",.comment="GPIO 2: Output (else Input)",.len=9,.def="0",.bit=REVK_SETTINGS_BITFIELD_xgpio2out,.hide=1},
 {.type=REVK_SETTINGS_BIT,.name="xgpio2pd",.comment="GPIO 2: Pull-Down (Input only)",.len=8,.def="0",.bit=REVK_SETTINGS_BITFIELD_xgpio2pd,.hide=1},
 {.type=REVK_SETTINGS_BIT,.name="xgpio2pwm",.comment="GPIO 2: PWM mode (implies output)",.len=9,.def="0",.bit=REVK_SETTINGS_BITFIELD_xgpio2pwm,.hide=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="xgpio2freq",.comment="GPIO 2: PWM frequency (Hz)",.len=10,.def="1000",.ptr=&xgpio2freq,.size=sizeof(uint16_t),.hide=1},
 {.type=REVK_SETTINGS_BIT,.name="xgpio2adc",.comment="GPIO 2: ADC mode (analog input, 0-100%)",.len=9,.def="0",.bit=REVK_SETTINGS_BITFIELD_xgpio2adc,.hide=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="xgpio2adct",.comment="GPIO 2: ADC change threshold to report (%)",.len=10,.def="5",.ptr=&xgpio2adct,.size=sizeof(uint8_t),.live=1,.hide=1},
 {.type=REVK_SETTINGS_STRING,.name="xgpio3name",.comment="Label for Additional GPIO 3",.len=10,.ptr=&xgpio3name,.malloc=1,.hide=1},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="xgpio3",.comment="Additional GPIO 3",.len=6,.ptr=&xgpio3,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕",.hide=1},
 {.type=REVK_SETTINGS_BIT,.name="xgpio3out",.comment="GPIO 3: Output (else Input)",.len=9,.def="0",.bit=REVK_SETTINGS_BITFIELD_xgpio3out,.hide=1},
 {.type=REVK_SETTINGS_BIT,.name="xgpio3pd",.comment="GPIO 3: Pull-Down (Input only)",.len=8,.def="0",.bit=REVK_SETTINGS_BITFIELD_xgpio3pd,.hide=1},
 {.type=REVK_SETTINGS_BIT,.name="xgpio3pwm",.comment="GPIO 3: PWM mode (implies output)",.len=9,.def="0",.bit=REVK_SETTINGS_BITFIELD_xgpio3pwm,.hide=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="xgpio3freq",.comment="GPIO 3: PWM frequency (Hz)",.len=10,.def="1000",.ptr=&xgpio3freq,.size=sizeof(uint16_t),.hide=1},
 {.type=REVK_SETTINGS_BIT,.name="xgpio3adc",.comment="GPIO 3: ADC mode (analog input, 0-100%)",.len=9,.def="0",.bit=REVK_SETTINGS_BITFIELD_xgpio3adc,.hide=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="xgpio3adct",.comment="GPIO 3: ADC change threshold to report (%)",.len=10,.def="5",.ptr=&xgpio3adct,.size=sizeof(uint8_t),.live=1,.hide=1},
 {.type=REVK_SETTINGS_STRING,.name="xgpio4name",.comment="Label for Additional GPIO 4",.len=10,.ptr=&xgpio4name,.malloc=1,.hide=1},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="xgpio4",.comment="Additional GPIO 4",.len=6,.ptr=&xgpio4,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕",.hide=1},
 {.type=REVK_SETTINGS_BIT,.name="xgpio4out",.comment="GPIO 4: Output (else Input)",.len=9,.def="0",.bit=REVK_SETTINGS_BITFIELD_xgpio4out,.hide=1},
 {.type=REVK_SETTINGS_BIT,.name="xgpio4pd",.comment="GPIO 4: Pull-Down (Input only)",.len=8,.def="0",.bit=REVK_SETTINGS_BITFIELD_xgpio4pd,.hide=1},
 {.type=REVK_SETTINGS_BIT,.name="xgpio4pwm",.comment="GPIO 4: PWM mode (implies output)",.len=9,.def="0",.bit=REVK_SETTINGS_BITFIELD_xgpio4pwm,.hide=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="xgpio4freq",.comment="GPIO 4: PWM frequency (Hz)",.len=10,.def="1000",.ptr=&xgpio4freq,.size=sizeof(uint16_t),.hide=1},
 {.type=REVK_SETTINGS_BIT,.name="xgpio4adc",.comment="GPIO 4: ADC mode (analog input, 0-100%)",.len=9,.def="0",.bit=REVK_SETTINGS_BITFIELD_xgpio4adc,.hide=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="xgpio4adct",.comment="GPIO 4: ADC change threshold to report (%)",.len=10,.def="5",.ptr=&xgpio4adct,.size=sizeof(uint8_t),.live=1,.hide=1},
 {.type=REVK_SETTINGS_STRING,.name="xgpio5name",.comment="Label for Additional GPIO 5",.len=10,.ptr=&xgpio5name,.malloc=1,.hide=1},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="xgpio5",.comment="Additional GPIO 5",.len=6,.ptr=&xgpio5,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕",.hide=1},
 {.type=REVK_SETTINGS_BIT,.name="xgpio5out",.comment="GPIO 5: Output (else Input)",.len=9,.def="0",.bit=REVK_SETTINGS_BITFIELD_xgpio5out,.hide=1},
 {.type=REVK_SETTINGS_BIT,.name="xgpio5pd",.comment="GPIO 5: Pull-Down (Input only)",.len=8,.def="0",.bit=REVK_SETTINGS_BITFIELD_xgpio5pd,.hide=1},
 {.type=REVK_SETTINGS_BIT,.name="xgpio5pwm",.comment="GPIO 5: PWM mode (implies output)",.len=9,.def="0",.bit=REVK_SETTINGS_BITFIELD_xgpio5pwm,.hide=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="xgpio5freq",.comment="GPIO 5: PWM frequency (Hz)",.len=10,.def="1000",.ptr=&xgpio5freq,.size=sizeof(uint16_t),.hide=1},
 {.type=REVK_SETTINGS_BIT,.name="xgpio5adc",.comment="GPIO 5: ADC mode (analog input, 0-100%)",.len=9,.def="0",.bit=REVK_SETTINGS_BITFIELD_xgpio5adc,.hide=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="xgpio5adct",.comment="GPIO 5: ADC change threshold to report (%)",.len=10,.def="5",.ptr=&xgpio5adct,.size=sizeof(uint8_t),.live=1,.hide=1},
#ifdef	CONFIG_REVK_SETTINGS_PASSWORD
 {.type=REVK_SETTINGS_STRING,.name="password",.comment="Settings password<br>(not sent securely so use with care)",.len=8,.ptr=&password,.malloc=1,.revk=1,.hide=1,.secret=1},
#endif
#ifdef  CONFIG_MDNS_MAX_INTERFACES
 {.type=REVK_SETTINGS_STRING,.name="hostname",.comment="Hostname[.local]<br>(used in DHCP and MQTT)",.len=8,.ptr=&hostname,.malloc=1,.revk=1,.hide=1},
 {.type=REVK_SETTINGS_STRING,.name="instance",.comment="Descriptive name of host, default is hostname",.len=8,.ptr=&instance,.malloc=1,.revk=1,.hide=1},
#else
 {.type=REVK_SETTINGS_STRING,.name="hostname",.comment="Host name<br>(used in DHCP and MQTT)",.len=8,.ptr=&hostname,.malloc=1,.revk=1,.hide=1},
#endif
 {.type=REVK_SETTINGS_STRING,.name="otahost",.comment="OTA hostname",.group=15,.len=7,.dot=3,.dq=1,.def=quote(CONFIG_REVK_OTAHOST),.ptr=&otahost,.malloc=1,.revk=1,.live=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="otadays",.comment="OTA auto load (days)",.group=15,.len=7,.dot=3,.dq=1,.def=quote(CONFIG_REVK_OTADAYS),.ptr=&otadays,.size=sizeof(uint8_t),.revk=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="otastart",.comment="OTA check after startup (min seconds)",.group=15,.len=8,.dot=3,.def="600",.ptr=&otastart,.size=sizeof(uint16_t),.revk=1},
 {.type=REVK_SETTINGS_BIT,.name="otaauto",.comment="OTA auto upgrade",.group=15,.len=7,.dot=3,.def="1",.bit=REVK_SETTINGS_BITFIELD_otaauto,.revk=1,.hide=1,.live=1},
#ifdef	CONFIG_REVK_WEB_BETA
 {.type=REVK_SETTINGS_BIT,.name="otabeta",.comment="OTA from beta release",.group=15,.len=7,.dot=3,.bit=REVK_SETTINGS_BITFIELD_otabeta,.revk=1,.hide=1,.live=1},
#endif
 {.type=REVK_SETTINGS_BLOB,.name="otacert",.comment="OTA cert of otahost",.group=15,.len=7,.dot=3,.dq=1,.def=quote(CONFIG_REVK_OTACERT),.ptr=&otacert,.malloc=1,.revk=1,.base64=1},
 {.type=REVK_SETTINGS_BIT,.name="dark",.comment="Default LED off",.len=4,.bit=REVK_SETTINGS_BITFIELD_dark,.revk=1,.live=1},
 {.type=REVK_SETTINGS_STRING,.name="ntphost",.comment="NTP host",.len=7,.dq=1,.def=quote(CONFIG_REVK_NTPHOST),.ptr=&ntphost,.malloc=1,.revk=1},
 {.type=REVK_SETTINGS_STRING,.name="tz",.comment="Timezone (<a href='https://gist.github.com/alwynallan/24d96091655391107939' target=_blank>info</a>)",.len=2,.dq=1,.def=quote(CONFIG_REVK_TZ),.ptr=&tz,.malloc=1,.revk=1,.hide=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="watchdogtime",.comment="Watchdog (seconds)",.len=12,.dq=1,.def=quote(CONFIG_REVK_WATCHDOG),.ptr=&watchdogtime,.size=sizeof(uint32_t),.revk=1},
#ifdef  CONFIG_IDF_TARGET_ESP32S3
 {.type=REVK_SETTINGS_UNSIGNED,.name="usbuptime",.comment="USB  turns off after this many seconds",.len=9,.dq=1,.def=quote(CONFIG_REVK_USBUPTIME),.ptr=&usbuptime,.size=sizeof(uint16_t),.revk=1},
#endif
#ifdef  CONFIG_IDF_TARGET_ESP32S3
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="factorygpio",.comment="Factory reset GPIO (press 3 times)",.len=11,.dq=1,.def=quote(CONFIG_REVK_GPIO_RESET),.ptr=&factorygpio,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕",.revk=1},
#else
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="factorygpio",.comment="Factory reset GPIO (press 3 times)",.len=11,.ptr=&factorygpio,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕",.revk=1},
#endif
 {.type=REVK_SETTINGS_STRING,.name="topicgroup",.comment="MQTT Alternative hostname accepted for commands",.group=16,.len=10,.dot=5,.ptr=&topicgroup,.malloc=1,.revk=1,.array=2},
 {.type=REVK_SETTINGS_STRING,.name="topiccommand",.comment="MQTT Topic for commands",.group=16,.len=12,.dot=5,.def="command",.ptr=&topiccommand,.malloc=1,.revk=1,.old="prefixcommand"},
 {.type=REVK_SETTINGS_STRING,.name="topicsetting",.comment="MQTT Topic for settings",.group=16,.len=12,.dot=5,.def="setting",.ptr=&topicsetting,.malloc=1,.revk=1,.old="prefixsetting"},
 {.type=REVK_SETTINGS_STRING,.name="topicstate",.comment="MQTT Topic for state",.group=16,.len=10,.dot=5,.def="state",.ptr=&topicstate,.malloc=1,.revk=1,.old="prefixstate"},
 {.type=REVK_SETTINGS_STRING,.name="topicevent",.comment="MQTT Topic for event",.group=16,.len=10,.dot=5,.def="event",.ptr=&topicevent,.malloc=1,.revk=1,.old="prefixevent"},
 {.type=REVK_SETTINGS_STRING,.name="topicinfo",.comment="MQTT Topic for info",.group=16,.len=9,.dot=5,.def="info",.ptr=&topicinfo,.malloc=1,.revk=1,.old="prefixinfo"},
 {.type=REVK_SETTINGS_STRING,.name="topicerror",.comment="MQTT Topic for error",.group=16,.len=10,.dot=5,.def="error",.ptr=&topicerror,.malloc=1,.revk=1,.old="prefixerror"},
 {.type=REVK_SETTINGS_STRING,.name="topicha",.comment="MQTT Topic for homeassistant",.group=16,.len=7,.dot=5,.def="homeassistant",.ptr=&topicha,.malloc=1,.revk=1},
 {.type=REVK_SETTINGS_BIT,.name="prefixapp",.comment="MQTT use appname/ in front of hostname in topic",.group=17,.len=9,.dot=6,.dq=1,.def=quote(CONFIG_REVK_PREFIXAPP),.bit=REVK_SETTINGS_BITFIELD_prefixapp,.revk=1},
 {.type=REVK_SETTINGS_BIT,.name="prefixhost",.comment="MQTT use (appname/)hostname/topic instead of topic/(appname/)hostname",.group=17,.len=10,.dot=6,.dq=1,.def=quote(CONFIG_REVK_PREFIXHOST),.bit=REVK_SETTINGS_BITFIELD_prefixhost,.revk=1},
#ifdef	CONFIG_REVK_BLINK_DEF
#ifdef	CONFIG_REVK_BLINK_WS2812_DEF
#ifdef	CONFIG_REVK_LED_TEST
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="blink",.comment="WS2812 LED, and loop test",.len=5,.dq=1,.def=quote(CONFIG_REVK_BLINK),.ptr=&blink,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕",.revk=1,.array=2},
#else
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="blink",.comment="WS2812 LED",.len=5,.dq=1,.def=quote(CONFIG_REVK_BLINK),.ptr=&blink,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕",.revk=1},
#endif
 {.type=REVK_SETTINGS_BIT,.name="ws2812rgb",.comment="Reverse green and red on WS2812 LED",.len=9,.def="0",.bit=REVK_SETTINGS_BITFIELD_ws2812rgb,.revk=1},
#else
#ifdef	CONFIG_REVK_LED_TEST
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="blink",.comment="R, G, B LED array (for WS2818, set first two the same, third can be loop test)",.len=5,.dq=1,.def=quote(CONFIG_REVK_BLINK),.ptr=&blink,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕",.revk=1,.array=3},
#else
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="blink",.comment="R, G, B LED array (for WS2812, set first two the same)",.len=5,.dq=1,.def=quote(CONFIG_REVK_BLINK),.ptr=&blink,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕",.revk=1,.array=3},
#endif
#endif
#endif
#ifdef  CONFIG_REVK_APMODE
#ifdef	CONFIG_REVK_APCONFIG
 {.type=REVK_SETTINGS_UNSIGNED,.name="apport",.comment="TCP port for config web pages on AP",.group=18,.len=6,.dot=2,.dq=1,.def=quote(CONFIG_REVK_APPORT),.ptr=&apport,.size=sizeof(uint16_t),.revk=1},
#endif
 {.type=REVK_SETTINGS_UNSIGNED,.name="aptime",.comment="Limit AP to time (seconds)",.group=18,.len=6,.dot=2,.dq=1,.def=quote(CONFIG_REVK_APTIME),.ptr=&aptime,.size=sizeof(uint32_t),.revk=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="apwait",.comment="Wait off line before starting AP (seconds)",.group=18,.len=6,.dot=2,.dq=1,.def=quote(CONFIG_REVK_APWAIT),.ptr=&apwait,.size=sizeof(uint32_t),.revk=1},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="apgpio",.comment="Start AP on GPIO",.group=18,.len=6,.dot=2,.dq=1,.def=quote(CONFIG_REVK_APGPIO),.ptr=&apgpio,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕",.revk=1},
#endif
#ifdef  CONFIG_REVK_MQTT
 {.type=REVK_SETTINGS_STRING,.name="mqtthost",.comment="MQTT hostname",.group=19,.len=8,.dot=4,.dq=1,.def=quote(CONFIG_REVK_MQTTHOST),.ptr=&mqtthost,.malloc=1,.revk=1,.array=CONFIG_REVK_MQTT_CLIENTS,.hide=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="mqttport",.comment="MQTT port",.group=19,.len=8,.dot=4,.dq=1,.def=quote(CONFIG_REVK_MQTTPORT),.ptr=&mqttport,.size=sizeof(uint16_t),.revk=1,.array=CONFIG_REVK_MQTT_CLIENTS},
 {.type=REVK_SETTINGS_STRING,.name="mqttuser",.comment="MQTT username",.group=19,.len=8,.dot=4,.dq=1,.def=quote(CONFIG_REVK_MQTTUSER),.ptr=&mqttuser,.malloc=1,.revk=1,.array=CONFIG_REVK_MQTT_CLIENTS,.hide=1},
 {.type=REVK_SETTINGS_STRING,.name="mqttpass",.comment="MQTT password",.group=19,.len=8,.dot=4,.dq=1,.def=quote(CONFIG_REVK_MQTTPASS),.ptr=&mqttpass,.malloc=1,.revk=1,.array=CONFIG_REVK_MQTT_CLIENTS,.secret=1,.hide=1},
 {.type=REVK_SETTINGS_BLOB,.name="mqttcert",.comment="MQTT CA certificate (for mqtts)",.group=19,.len=8,.dot=4,.dq=1,.def=quote(CONFIG_REVK_MQTTCERT),.ptr=&mqttcert,.malloc=1,.revk=1,.array=CONFIG_REVK_MQTT_CLIENTS,.base64=1},
#endif
 {.type=REVK_SETTINGS_BLOB,.name="clientkey",.comment="Client Key (MQTT TLS)",.group=20,.len=9,.dot=6,.ptr=&clientkey,.malloc=1,.revk=1,.base64=1},
 {.type=REVK_SETTINGS_BLOB,.name="clientcert",.comment="Client certificate (MQTT TLS)",.group=20,.len=10,.dot=6,.ptr=&clientcert,.malloc=1,.revk=1,.base64=1},
#if     defined(CONFIG_REVK_WIFI) || defined(CONFIG_REVK_MESH)
 {.type=REVK_SETTINGS_UNSIGNED,.name="wifireset",.comment="Restart if WiFi off for this long (seconds)",.group=21,.len=9,.dot=4,.dq=1,.def=quote(CONFIG_REVK_WIFIRESET),.ptr=&wifireset,.size=sizeof(uint16_t),.revk=1},
 {.type=REVK_SETTINGS_STRING,.name="wifissid",.comment="WiFI SSID (name)",.group=21,.len=8,.dot=4,.dq=1,.def=quote(CONFIG_REVK_WIFISSID),.ptr=&wifissid,.malloc=1,.revk=1,.hide=1},
 {.type=REVK_SETTINGS_STRING,.name="wifipass",.comment="WiFi password",.group=21,.len=8,.dot=4,.dq=1,.def=quote(CONFIG_REVK_WIFIPASS),.ptr=&wifipass,.malloc=1,.revk=1,.hide=1,.secret=1},
 {.type=REVK_SETTINGS_STRING,.name="wifiip",.comment="WiFi Fixed IP/len or IPv6",.group=21,.len=6,.dot=4,.dq=1,.def=quote(CONFIG_REVK_WIFIIP),.ptr=&wifiip,.malloc=1,.revk=1},
 {.type=REVK_SETTINGS_STRING,.name="wifigw",.comment="WiFi Fixed gateway",.group=21,.len=6,.dot=4,.dq=1,.def=quote(CONFIG_REVK_WIFIGW),.ptr=&wifigw,.malloc=1,.revk=1},
 {.type=REVK_SETTINGS_STRING,.name="wifidns",.comment="WiFi fixed DNS",.group=21,.len=7,.dot=4,.dq=1,.def=quote(CONFIG_REVK_WIFIDNS),.ptr=&wifidns,.malloc=1,.revk=1,.array=3},
 {.type=REVK_SETTINGS_OCTET,.name="wifibssid",.comment="WiFI BSSID",.group=21,.len=9,.dot=4,.dq=1,.def=quote(CONFIG_REVK_WIFIBSSID),.ptr=&wifibssid,.size=sizeof(uint8_t[6]),.revk=1,.hex=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="wifichan",.comment="WiFI channel",.group=21,.len=8,.dot=4,.dq=1,.def=quote(CONFIG_REVK_WIFICHAN),.ptr=&wifichan,.size=sizeof(uint8_t),.revk=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="wifiuptime",.comment="WiFI turns off after this many seconds",.group=21,.len=10,.dot=4,.dq=1,.def=quote(CONFIG_REVK_WIFIUPTIME),.ptr=&wifiuptime,.size=sizeof(uint16_t),.revk=1},
 {.type=REVK_SETTINGS_BIT,.name="wifips",.comment="WiFi power save",.group=21,.len=6,.dot=4,.dq=1,.def=quote(CONFIG_REVK_WIFIPS),.bit=REVK_SETTINGS_BITFIELD_wifips,.revk=1},
 {.type=REVK_SETTINGS_BIT,.name="wifimaxps",.comment="WiFi power save (max)",.group=21,.len=9,.dot=4,.dq=1,.def=quote(CONFIG_REVK_WIFIMAXPS),.bit=REVK_SETTINGS_BITFIELD_wifimaxps,.revk=1},
#ifdef CONFIG_REVK_ETHERNET
 {.type=REVK_SETTINGS_BIT,.name="wifiminpower",.comment="Reduce WiFi TX power to minimum (2 dBm) — useful when Ethernet is primary and WiFi cannot be disabled",.group=21,.len=12,.dot=4,.def="0",.bit=REVK_SETTINGS_BITFIELD_wifiminpower,.revk=1},
 {.type=REVK_SETTINGS_BIT,.name="wifinoeth",.comment="Turn off WiFi when Ethernet online",.group=21,.len=9,.dot=4,.def="0",.bit=REVK_SETTINGS_BITFIELD_wifinoeth,.revk=1},
#endif
#endif
#ifndef	CONFIG_REVK_MESH
 {.type=REVK_SETTINGS_STRING,.name="apssid",.comment="AP mode SSID (name)",.group=18,.len=6,.dot=2,.dq=1,.def=quote(CONFIG_REVK_APSSID),.ptr=&apssid,.malloc=1,.revk=1},
 {.type=REVK_SETTINGS_STRING,.name="appass",.comment="AP mode password",.group=18,.len=6,.dot=2,.dq=1,.def=quote(CONFIG_REVK_APPASS),.ptr=&appass,.malloc=1,.revk=1,.secret=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="apmax",.comment="AP max clients",.group=18,.len=5,.dot=2,.dq=1,.def=quote(CONFIG_REVK_APMAX),.ptr=&apmax,.size=sizeof(uint8_t),.revk=1,.hide=1},
 {.type=REVK_SETTINGS_STRING,.name="apip",.comment="AP mode block",.group=18,.len=4,.dot=2,.dq=1,.def=quote(CONFIG_REVK_APIP),.ptr=&apip,.malloc=1,.revk=1},
 {.type=REVK_SETTINGS_BIT,.name="aplr",.comment="AP LR mode",.group=18,.len=4,.dot=2,.dq=1,.def=quote(CONFIG_REVK_APLR),.bit=REVK_SETTINGS_BITFIELD_aplr,.revk=1},
 {.type=REVK_SETTINGS_BIT,.name="aphide",.comment="AP hide SSID",.group=18,.len=6,.dot=2,.dq=1,.def=quote(CONFIG_REVK_APHIDE),.bit=REVK_SETTINGS_BITFIELD_aphide,.revk=1},
#endif
#ifdef	CONFIG_REVK_MESH
 {.type=REVK_SETTINGS_STRING,.name="nodename",.comment="Mesh node name",.len=8,.ptr=&nodename,.malloc=1,.revk=1,.hide=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="meshreset",.comment="Reset if mesh off for this long (seconds)",.group=22,.len=9,.dot=4,.dq=1,.def=quote(CONFIG_REVK_MESHRESET),.ptr=&meshreset,.size=sizeof(uint16_t),.revk=1,.hide=1},
 {.type=REVK_SETTINGS_OCTET,.name="meshid",.comment="Mesh ID (hex)",.group=22,.len=6,.dot=4,.dq=1,.def=quote(CONFIG_REVK_MESHID),.ptr=&meshid,.size=sizeof(uint8_t[6]),.revk=1,.hex=1,.hide=1},
 {.type=REVK_SETTINGS_OCTET,.name="meshkey",.comment="Mesh key",.group=22,.len=7,.dot=4,.ptr=&meshkey,.size=sizeof(uint8_t[16]),.revk=1,.secret=1,.hex=1,.hide=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="meshwidth",.comment="Mesh width",.group=22,.len=9,.dot=4,.dq=1,.def=quote(CONFIG_REVK_MESHWIDTH),.ptr=&meshwidth,.size=sizeof(uint16_t),.revk=1,.hide=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="meshdepth",.comment="Mesh depth",.group=22,.len=9,.dot=4,.dq=1,.def=quote(CONFIG_REVK_MESHDEPTH),.ptr=&meshdepth,.size=sizeof(uint16_t),.revk=1,.hide=1},
 {.type=REVK_SETTINGS_UNSIGNED,.name="meshmax",.comment="Mesh max devices",.group=22,.len=7,.dot=4,.dq=1,.def=quote(CONFIG_REVK_MESHMAX),.ptr=&meshmax,.size=sizeof(uint16_t),.revk=1,.hide=1},
 {.type=REVK_SETTINGS_STRING,.name="meshpass",.comment="Mesh AP password",.group=22,.len=8,.dot=4,.dq=1,.def=quote(CONFIG_REVK_MESHPASS),.ptr=&meshpass,.malloc=1,.revk=1,.secret=1,.hide=1},
 {.type=REVK_SETTINGS_BIT,.name="meshlr",.comment="Mesh use LR mode",.group=22,.len=6,.dot=4,.dq=1,.def=quote(CONFIG_REVK_MESHLR),.bit=REVK_SETTINGS_BITFIELD_meshlr,.revk=1,.hide=1},
 {.type=REVK_SETTINGS_BIT,.name="meshroot",.comment="This is preferred mesh root",.group=22,.len=8,.dot=4,.bit=REVK_SETTINGS_BITFIELD_meshroot,.revk=1,.hide=1},
#endif
#ifdef	CONFIG_REVK_ETH_KSZ8851SNL
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="ethcs",.comment="Ethernet SPI CS",.group=23,.len=5,.dot=3,.dq=1,.def=quote(CONFIG_REVK_ETH_CS),.ptr=&ethcs,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕",.revk=1},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="ethmosi",.comment="Ethernet SPI MOSI",.group=23,.len=7,.dot=3,.dq=1,.def=quote(CONFIG_REVK_ETH_MOSI),.ptr=&ethmosi,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕",.revk=1},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="ethclk",.comment="Ethernet SPI CLK",.group=23,.len=6,.dot=3,.dq=1,.def=quote(CONFIG_REVK_ETH_CLK),.ptr=&ethclk,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕",.revk=1},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="ethmiso",.comment="Ethernet SPI MISO",.group=23,.len=7,.dot=3,.dq=1,.def=quote(CONFIG_REVK_ETH_MISO),.ptr=&ethmiso,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕",.revk=1},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="ethwol",.comment="Ethernet SPI Wake on LAN",.group=23,.len=6,.dot=3,.dq=1,.def=quote(CONFIG_REVK_ETH_WOL),.ptr=&ethwol,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕",.revk=1},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="ethint",.comment="Ethernet SPI INT",.group=23,.len=6,.dot=3,.dq=1,.def=quote(CONFIG_REVK_ETH_INT),.ptr=&ethint,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕",.revk=1},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="ethrst",.comment="Ethernet SPI RST",.group=23,.len=6,.dot=3,.dq=1,.def=quote(CONFIG_REVK_ETH_RST),.ptr=&ethrst,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕",.revk=1},
 {.type=REVK_SETTINGS_UNSIGNED,.gpio=1,.name="ethpoeload",.comment="Ethernet POE load",.group=23,.len=10,.dot=3,.dq=1,.def=quote(CONFIG_REVK_ETH_POELOAD),.ptr=&ethpoeload,.size=sizeof(revk_gpio_t),.fix=1,.set=1,.flags="- ~↓↕⇕",.revk=1},
#if	CONFIG_REVK_ETH_POE_TIMER >= 0 && CONFIG_REVK_ETH_POE_LEDC >= 0
 {.type=REVK_SETTINGS_BIT,.name="ethpoepwm",.comment="Ethernet POE load PWM rather than just turning off",.group=23,.len=9,.dot=3,.def="1",.bit=REVK_SETTINGS_BITFIELD_ethpoepwm,.revk=1,.fix=1},
#endif
 {.type=REVK_SETTINGS_STRING,.name="ethip",.comment="Ethernet Fixed IP/len or IPv6",.group=23,.len=5,.dot=3,.ptr=&ethip,.malloc=1,.revk=1},
 {.type=REVK_SETTINGS_STRING,.name="ethgw",.comment="Ethernet Fixed gateway",.group=23,.len=5,.dot=3,.ptr=&ethgw,.malloc=1,.revk=1},
 {.type=REVK_SETTINGS_STRING,.name="ethdns",.comment="Ethernet fixed DNS",.group=23,.len=6,.dot=3,.ptr=&ethdns,.malloc=1,.revk=1,.array=3},
#endif
{0}};
#undef quote
#undef str
uint8_t s21tries=0;
char* model=NULL;
char* region=NULL;
char* hadomain=NULL;
uint8_t fantype=0;
const char REVK_SETTINGS_FANTYPE_ENUMS[]="Default,5 level+auto,3 level,3 level+auto";
uint8_t protocol=0;
uint32_t reporting=0;
uint8_t uart=0;
uint8_t thermref=0;
uint8_t switchtemp=0;
uint8_t pushtemp=0;
int8_t coolover=0;
uint8_t coolback=0;
int8_t heatover=0;
uint8_t heatback=0;
int8_t minoutside=0;
int8_t frosttemp=0;
uint16_t tempnoflap=0;
#ifdef CONFIG_BT_NIMBLE_ENABLED
char* autob=NULL;
#endif
uint16_t auto0=0;
uint16_t auto1=0;
uint16_t autot=0;
uint8_t autor=0;
uint8_t autofmax=0;
uint8_t autoptemp=0;
char* autotopic=NULL;
char* autopayload=NULL;
uint8_t tmin=0;
uint8_t tcoolmin=0;
uint8_t tmax=0;
uint8_t theatmax=0;
uint32_t tpredicts=0;
uint32_t tpredictt=0;
uint32_t tsample=0;
uint32_t tcontrol=0;
#ifdef  CONFIG_IDF_TARGET_ESP32S3
revk_gpio_t tx={0};
revk_gpio_t rx={0};
#else
#ifdef  CONFIG_IDF_TARGET_ESP32C5
revk_gpio_t tx={0};
revk_gpio_t rx={0};
#else
revk_gpio_t tx={0};
revk_gpio_t rx={0};
#endif
#endif
#if CONFIG_SOC_I2C_NUM > 1 // we need 2 I2C bus for master and slave
int8_t i2chtemp=0;
int8_t i2cctemp=0;
#if defined(CONFIG_IDF_TARGET_ESP32C5)
revk_gpio_t i2cslsda={0};
revk_gpio_t i2cslscl={0};
revk_gpio_t i2cmasda={0};
revk_gpio_t i2cmassl={0};
#elif defined(CONFIG_IDF_TARGET_ESP32C6)
revk_gpio_t i2cslsda={0};
revk_gpio_t i2cslscl={0};
revk_gpio_t i2cmasda={0};
revk_gpio_t i2cmassl={0};
#elif !defined(CONFIG_REVK_ETHERNET)
revk_gpio_t i2cslsda={0};
revk_gpio_t i2cslscl={0};
revk_gpio_t i2cmasda={0};
revk_gpio_t i2cmassl={0};
#else
revk_gpio_t i2cslsda={0};
revk_gpio_t i2cslscl={0};
revk_gpio_t i2cmasda={0};
revk_gpio_t i2cmassl={0};
#endif
#endif
char* xgpio1name=NULL;
revk_gpio_t xgpio1={0};
uint16_t xgpio1freq=0;
uint8_t xgpio1adct=0;
char* xgpio2name=NULL;
revk_gpio_t xgpio2={0};
uint16_t xgpio2freq=0;
uint8_t xgpio2adct=0;
char* xgpio3name=NULL;
revk_gpio_t xgpio3={0};
uint16_t xgpio3freq=0;
uint8_t xgpio3adct=0;
char* xgpio4name=NULL;
revk_gpio_t xgpio4={0};
uint16_t xgpio4freq=0;
uint8_t xgpio4adct=0;
char* xgpio5name=NULL;
revk_gpio_t xgpio5={0};
uint16_t xgpio5freq=0;
uint8_t xgpio5adct=0;
#ifdef	CONFIG_REVK_SETTINGS_PASSWORD
char* password=NULL;
#endif
#ifdef  CONFIG_MDNS_MAX_INTERFACES
char* hostname=NULL;
char* instance=NULL;
#else
char* hostname=NULL;
#endif
char* otahost=NULL;
uint8_t otadays=0;
uint16_t otastart=0;
#ifdef	CONFIG_REVK_WEB_BETA
#endif
revk_settings_blob_t* otacert=NULL;
char* ntphost=NULL;
char* tz=NULL;
uint32_t watchdogtime=0;
#ifdef  CONFIG_IDF_TARGET_ESP32S3
uint16_t usbuptime=0;
#endif
#ifdef  CONFIG_IDF_TARGET_ESP32S3
revk_gpio_t factorygpio={0};
#else
revk_gpio_t factorygpio={0};
#endif
char* topicgroup[2]={0};
char* topiccommand=NULL;
char* topicsetting=NULL;
char* topicstate=NULL;
char* topicevent=NULL;
char* topicinfo=NULL;
char* topicerror=NULL;
char* topicha=NULL;
#ifdef	CONFIG_REVK_BLINK_DEF
#ifdef	CONFIG_REVK_BLINK_WS2812_DEF
#ifdef	CONFIG_REVK_LED_TEST
revk_gpio_t blink[2]={0};
#else
revk_gpio_t blink={0};
#endif
#else
#ifdef	CONFIG_REVK_LED_TEST
revk_gpio_t blink[3]={0};
#else
revk_gpio_t blink[3]={0};
#endif
#endif
#endif
#ifdef  CONFIG_REVK_APMODE
#ifdef	CONFIG_REVK_APCONFIG
uint16_t apport=0;
#endif
uint32_t aptime=0;
uint32_t apwait=0;
revk_gpio_t apgpio={0};
#endif
#ifdef  CONFIG_REVK_MQTT
char* mqtthost[CONFIG_REVK_MQTT_CLIENTS]={0};
uint16_t mqttport[CONFIG_REVK_MQTT_CLIENTS]={0};
char* mqttuser[CONFIG_REVK_MQTT_CLIENTS]={0};
char* mqttpass[CONFIG_REVK_MQTT_CLIENTS]={0};
revk_settings_blob_t* mqttcert[CONFIG_REVK_MQTT_CLIENTS]={0};
#endif
revk_settings_blob_t* clientkey=NULL;
revk_settings_blob_t* clientcert=NULL;
#if     defined(CONFIG_REVK_WIFI) || defined(CONFIG_REVK_MESH)
uint16_t wifireset=0;
char* wifissid=NULL;
char* wifipass=NULL;
char* wifiip=NULL;
char* wifigw=NULL;
char* wifidns[3]={0};
uint8_t wifibssid[6]={0};
uint8_t wifichan=0;
uint16_t wifiuptime=0;
#ifdef CONFIG_REVK_ETHERNET
#endif
#endif
#ifndef	CONFIG_REVK_MESH
char* apssid=NULL;
char* appass=NULL;
uint8_t apmax=0;
char* apip=NULL;
#endif
#ifdef	CONFIG_REVK_MESH
char* nodename=NULL;
uint16_t meshreset=0;
uint8_t meshid[6]={0};
uint8_t meshkey[16]={0};
uint16_t meshwidth=0;
uint16_t meshdepth=0;
uint16_t meshmax=0;
char* meshpass=NULL;
#endif
#ifdef	CONFIG_REVK_ETH_KSZ8851SNL
revk_gpio_t ethcs={0};
revk_gpio_t ethmosi={0};
revk_gpio_t ethclk={0};
revk_gpio_t ethmiso={0};
revk_gpio_t ethwol={0};
revk_gpio_t ethint={0};
revk_gpio_t ethrst={0};
revk_gpio_t ethpoeload={0};
#if	CONFIG_REVK_ETH_POE_TIMER >= 0 && CONFIG_REVK_ETH_POE_LEDC >= 0
#endif
char* ethip=NULL;
char* ethgw=NULL;
char* ethdns[3]={0};
#endif
#ifdef CONFIG_BT_NIMBLE_ENABLED
#endif
#ifdef  CONFIG_IDF_TARGET_ESP32S3
#else
#ifdef  CONFIG_IDF_TARGET_ESP32C5
#else
#endif
#endif
#if CONFIG_SOC_I2C_NUM > 1 // we need 2 I2C bus for master and slave
#if defined(CONFIG_IDF_TARGET_ESP32C5)
#elif defined(CONFIG_IDF_TARGET_ESP32C6)
#elif !defined(CONFIG_REVK_ETHERNET)
#else
#endif
#endif
#ifdef	CONFIG_REVK_SETTINGS_PASSWORD
#endif
#ifdef  CONFIG_MDNS_MAX_INTERFACES
#else
#endif
#ifdef	CONFIG_REVK_WEB_BETA
#endif
#ifdef  CONFIG_IDF_TARGET_ESP32S3
#endif
#ifdef  CONFIG_IDF_TARGET_ESP32S3
#else
#endif
#ifdef	CONFIG_REVK_BLINK_DEF
#ifdef	CONFIG_REVK_BLINK_WS2812_DEF
#ifdef	CONFIG_REVK_LED_TEST
#else
#endif
#else
#ifdef	CONFIG_REVK_LED_TEST
#else
#endif
#endif
#endif
#ifdef  CONFIG_REVK_APMODE
#ifdef	CONFIG_REVK_APCONFIG
#endif
#endif
#ifdef  CONFIG_REVK_MQTT
#endif
#if     defined(CONFIG_REVK_WIFI) || defined(CONFIG_REVK_MESH)
#ifdef CONFIG_REVK_ETHERNET
#endif
#endif
#ifndef	CONFIG_REVK_MESH
#endif
#ifdef	CONFIG_REVK_MESH
#endif
#ifdef	CONFIG_REVK_ETH_KSZ8851SNL
#if	CONFIG_REVK_ETH_POE_TIMER >= 0 && CONFIG_REVK_ETH_POE_LEDC >= 0
#endif
#endif
const char revk_settings_secret[]="✶✶✶✶✶✶✶✶";
