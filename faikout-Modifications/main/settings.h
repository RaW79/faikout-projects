// Settings
// Generated from:-
// main/settings.def
// components/ESP32-RevK/settings.def

#include <stdint.h>
#include <stddef.h>
typedef struct revk_settings_s revk_settings_t;
struct revk_settings_s {
 void *ptr;
 const char name[16];
 const char *def;
 union {
  const char *flags;
  const char *enums;
 };
 const char *old;
 const char *unit;
 const char *comment;
 uint16_t size;
 uint8_t group;
 uint8_t bit;
 uint8_t dot:4;
 uint8_t len:4;
 uint8_t type:3;
 uint8_t decimal:5;
 uint8_t digits:5;
 uint8_t array:7;
 uint8_t malloc:1;
 uint8_t revk:1;
 uint8_t live:1;
 uint8_t hide:1;
 uint8_t fix:1;
 uint8_t set:1;
 uint8_t hex:1;
 uint8_t base32:1;
 uint8_t base64:1;
 uint8_t secret:1;
 uint8_t dq:1;
 uint8_t rtc:1;
 uint8_t gpio:1;
 uint8_t isenum:1;
};
extern const char REVK_SETTINGS_FANTYPE_ENUMS[];
enum {
REVK_SETTINGS_FANTYPE_DEFAULT,
REVK_SETTINGS_FANTYPE_5_LEVEL_AUTO,
REVK_SETTINGS_FANTYPE_3_LEVEL,
REVK_SETTINGS_FANTYPE_3_LEVEL_AUTO,
};
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
typedef struct revk_settings_blob_s revk_settings_blob_t;
struct revk_settings_blob_s {
 uint16_t len;
 uint8_t data[];
};
typedef struct revk_gpio_s revk_gpio_t;
struct revk_gpio_s {
 uint16_t num:10;
 uint16_t strong:1;
 uint16_t weak:1;
 uint16_t pulldown:1;
 uint16_t nopull:1;
 uint16_t invert:1;
 uint16_t set:1;
};
enum {
 REVK_SETTINGS_BITFIELD_dump,
 REVK_SETTINGS_BITFIELD_debug,
 REVK_SETTINGS_BITFIELD_debughex,
 REVK_SETTINGS_BITFIELD_snoop,
 REVK_SETTINGS_BITFIELD_livestatus,
 REVK_SETTINGS_BITFIELD_fixstatus,
 REVK_SETTINGS_BITFIELD_s21extra,
 REVK_SETTINGS_BITFIELD_webcontrol,
 REVK_SETTINGS_BITFIELD_websettings,
 REVK_SETTINGS_BITFIELD_fahrenheit,
 REVK_SETTINGS_BITFIELD_nos21,
 REVK_SETTINGS_BITFIELD_nox50a,
 REVK_SETTINGS_BITFIELD_nocnwired,
 REVK_SETTINGS_BITFIELD_noas,
 REVK_SETTINGS_BITFIELD_noswaptx,
 REVK_SETTINGS_BITFIELD_noswaprx,
 REVK_SETTINGS_BITFIELD_nodemand,
 REVK_SETTINGS_BITFIELD_noauto,
 REVK_SETTINGS_BITFIELD_noecono,
 REVK_SETTINGS_BITFIELD_noswingv,
 REVK_SETTINGS_BITFIELD_noswingh,
 REVK_SETTINGS_BITFIELD_nocomfort,
 REVK_SETTINGS_BITFIELD_nostreamer,
 REVK_SETTINGS_BITFIELD_nopowerful,
 REVK_SETTINGS_BITFIELD_nosensor,
 REVK_SETTINGS_BITFIELD_noquiet,
 REVK_SETTINGS_BITFIELD_noled,
 REVK_SETTINGS_BITFIELD_noflap,
 REVK_SETTINGS_BITFIELD_noantifreeze,
 REVK_SETTINGS_BITFIELD_nohumidity,
 REVK_SETTINGS_BITFIELD_nohumidify,
 REVK_SETTINGS_BITFIELD_nohourly,
 REVK_SETTINGS_BITFIELD_nofaikoutauto,
 REVK_SETTINGS_BITFIELD_nohvacaction,
 REVK_SETTINGS_BITFIELD_nofanauto,
 REVK_SETTINGS_BITFIELD_nohomepreset,
 REVK_SETTINGS_BITFIELD_noicons,
 REVK_SETTINGS_BITFIELD_udpdiscovery,
 REVK_SETTINGS_BITFIELD_haenable,
 REVK_SETTINGS_BITFIELD_haswitches,
 REVK_SETTINGS_BITFIELD_hafanrpm,
 REVK_SETTINGS_BITFIELD_hacomprpm,
 REVK_SETTINGS_BITFIELD_ha1c,
 REVK_SETTINGS_BITFIELD_haperiodic,
 REVK_SETTINGS_BITFIELD_haram,
 REVK_SETTINGS_BITFIELD_hauptime,
 REVK_SETTINGS_BITFIELD_cnmark900,
 REVK_SETTINGS_BITFIELD_lockmode,
 REVK_SETTINGS_BITFIELD_protofix,
 REVK_SETTINGS_BITFIELD_temptrack,
 REVK_SETTINGS_BITFIELD_tempadjust,
#ifdef CONFIG_BT_NIMBLE_ENABLED
 REVK_SETTINGS_BITFIELD_bleenable,
#endif
 REVK_SETTINGS_BITFIELD_autoe,
 REVK_SETTINGS_BITFIELD_autop,
 REVK_SETTINGS_BITFIELD_autolcontrol,
 REVK_SETTINGS_BITFIELD_thermostat,
#ifdef  CONFIG_IDF_TARGET_ESP32S3
#else
#ifdef  CONFIG_IDF_TARGET_ESP32C5
#else
#endif
#endif
#if CONFIG_SOC_I2C_NUM > 1 // we need 2 I2C bus for master and slave
 REVK_SETTINGS_BITFIELD_i2cen,
#if defined(CONFIG_IDF_TARGET_ESP32C5)
#elif defined(CONFIG_IDF_TARGET_ESP32C6)
#elif !defined(CONFIG_REVK_ETHERNET)
#else
#endif
#endif
 REVK_SETTINGS_BITFIELD_xgpio1out,
 REVK_SETTINGS_BITFIELD_xgpio1pd,
 REVK_SETTINGS_BITFIELD_xgpio2out,
 REVK_SETTINGS_BITFIELD_xgpio2pd,
 REVK_SETTINGS_BITFIELD_xgpio3out,
 REVK_SETTINGS_BITFIELD_xgpio3pd,
 REVK_SETTINGS_BITFIELD_xgpio4out,
 REVK_SETTINGS_BITFIELD_xgpio4pd,
 REVK_SETTINGS_BITFIELD_xgpio5out,
 REVK_SETTINGS_BITFIELD_xgpio5pd,
#ifdef	CONFIG_REVK_SETTINGS_PASSWORD
#endif
#ifdef  CONFIG_MDNS_MAX_INTERFACES
#else
#endif
 REVK_SETTINGS_BITFIELD_otaauto,
#ifdef	CONFIG_REVK_WEB_BETA
 REVK_SETTINGS_BITFIELD_otabeta,
#endif
 REVK_SETTINGS_BITFIELD_dark,
#ifdef  CONFIG_IDF_TARGET_ESP32S3
#endif
#ifdef  CONFIG_IDF_TARGET_ESP32S3
#else
#endif
 REVK_SETTINGS_BITFIELD_prefixapp,
 REVK_SETTINGS_BITFIELD_prefixhost,
#ifdef	CONFIG_REVK_BLINK_DEF
#ifdef	CONFIG_REVK_BLINK_WS2812_DEF
#ifdef	CONFIG_REVK_LED_TEST
#else
#endif
 REVK_SETTINGS_BITFIELD_ws2812rgb,
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
 REVK_SETTINGS_BITFIELD_wifips,
 REVK_SETTINGS_BITFIELD_wifimaxps,
#ifdef CONFIG_REVK_ETHERNET
 REVK_SETTINGS_BITFIELD_wifiminpower,
 REVK_SETTINGS_BITFIELD_wifinoeth,
#endif
#endif
#ifndef	CONFIG_REVK_MESH
 REVK_SETTINGS_BITFIELD_aplr,
 REVK_SETTINGS_BITFIELD_aphide,
#endif
#ifdef	CONFIG_REVK_MESH
 REVK_SETTINGS_BITFIELD_meshlr,
 REVK_SETTINGS_BITFIELD_meshroot,
#endif
#ifdef	CONFIG_REVK_ETH_KSZ8851SNL
#if	CONFIG_REVK_ETH_POE_TIMER >= 0 && CONFIG_REVK_ETH_POE_LEDC >= 0
 REVK_SETTINGS_BITFIELD_ethpoepwm,
#endif
#endif
};
typedef struct revk_settings_bits_s revk_settings_bits_t;
struct revk_settings_bits_s {
 uint8_t dump:1;	// Dump protocol on MQTT for each message
 uint8_t debug:1;	// Debug - logs summary of status responses
 uint8_t debughex:1;	// Debug in hex
 uint8_t snoop:1;	// Listen only (for debugging)
 uint8_t livestatus:1;	// Send status messages in real time
 uint8_t fixstatus:1;	// Send status as fixed values not array
 uint8_t s21extra:1;	// Sends extra S21 messages, usually used with dump or debug
 uint8_t webcontrol:1;	// Web based controls
 uint8_t websettings:1;	// Web based settings
 uint8_t fahrenheit:1;	// Web shows Fahrenheit
 uint8_t nos21:1;	// Do not try S21 protocol
 uint8_t nox50a:1;	// Do not try X50A protocol
 uint8_t nocnwired:1;	// Do not try CN_WIRED protocol
 uint8_t noas:1;	// Do not try (experimental) Altherma_S protocol
 uint8_t noswaptx:1;	// Do not try inverted Tx (use GPIO setting only)
 uint8_t noswaprx:1;	// Do not try inverted Rx (use GPIO setting only)
 uint8_t nodemand:1;	// Disable demand control
 uint8_t noauto:1;	// Unit does not have auto mode
 uint8_t noecono:1;	// Unit does not have econo mode
 uint8_t noswingv:1;	// Unit does not have swing (V)
 uint8_t noswingh:1;	// Unit does not have swing (H)
 uint8_t nocomfort:1;	// Unit does not have comfort mode
 uint8_t nostreamer:1;	// Unit does not have streamer mode
 uint8_t nopowerful:1;	// Unit does not have powerful mode
 uint8_t nosensor:1;	// Unit does not have sensor mode
 uint8_t noquiet:1;	// Unit does not have quiet mode
 uint8_t noled:1;	// Unit does not have LED control
 uint8_t noflap:1;	// Unit does not have flap mode
 uint8_t noantifreeze:1;	// Unit does not have antifreeze mode
 uint8_t nohumidity:1;	// Unit does not have humidity
 uint8_t nohumidify:1;	// Unit does not have humidifier
 uint8_t nohourly:1;	// Do not do hourly S21 poll (DH)
 uint8_t nofaikoutauto:1;	// Do not show Faikout auto controls (unless already set up and no password)
 uint8_t nohvacaction:1;	// Do not track/report hvac_action for Faikout auto mode in HA
 uint8_t nofanauto:1;	// Do not control fan in Faikout auto mode
 uint8_t nohomepreset:1;	// Do not include a home in HA preset list
 uint8_t noicons:1;	// Do not show icons on web UI
 uint8_t udpdiscovery:1;	// Enable Daikin BRP-compatible UDP discovery
 uint8_t haenable:1;	// Home Assistant
 uint8_t haswitches:1;	// Set additional HA switches
 uint8_t hafanrpm:1;	// Use RPM not Hz for HA fan speed
 uint8_t hacomprpm:1;	// Use RPM not Hz for HA comp speed
 uint8_t ha1c:1;	// Force 1C steps in HA temp setting
 uint8_t haperiodic:1;	// Reduce HA updates
 uint8_t haram:1;	// Log memory usage
 uint8_t hauptime:1;	// Log uptime
 uint8_t cnmark900:1;	// CN_WIRED. mark using 900uS not 1000uS
 uint8_t lockmode:1;	// Do not auto switch heat/cool modes in Faikout auto
 uint8_t protofix:1;	// Protofix forces no change, use nos21, nox50a, etc instead maybe
 uint8_t temptrack:1;	// Set target temp based on Daikin measured temp not required target
 uint8_t tempadjust:1;	// Adjust target temp allowing for different Daikin measure to external measure
#ifdef CONFIG_BT_NIMBLE_ENABLED
 uint8_t bleenable:1;	// Enable BLE for sensors or remote
#endif
 uint8_t autoe:1;	// Enable auto time and power operations
 uint8_t autop:1;	// Enable auto power on/off (regardless of times)
 uint8_t autolcontrol:1;	// Auto toggle on/off LED based on current HVAC action
 uint8_t thermostat:1;	// Faikout auto simple thermostat mode (heat to max, cool to min)
#ifdef  CONFIG_IDF_TARGET_ESP32S3
#else
#ifdef  CONFIG_IDF_TARGET_ESP32C5
#else
#endif
#endif
#if CONFIG_SOC_I2C_NUM > 1 // we need 2 I2C bus for master and slave
 uint8_t i2cen:1;	// Enable I2C temp and humidity sensor spoofing
#if defined(CONFIG_IDF_TARGET_ESP32C5)
#elif defined(CONFIG_IDF_TARGET_ESP32C6)
#elif !defined(CONFIG_REVK_ETHERNET)
#else
#endif
#endif
 uint8_t xgpio1out:1;	// GPIO 1: Output (else Input)
 uint8_t xgpio1pd:1;	// GPIO 1: Pull-Down (Input only)
 uint8_t xgpio2out:1;	// GPIO 2: Output (else Input)
 uint8_t xgpio2pd:1;	// GPIO 2: Pull-Down (Input only)
 uint8_t xgpio3out:1;	// GPIO 3: Output (else Input)
 uint8_t xgpio3pd:1;	// GPIO 3: Pull-Down (Input only)
 uint8_t xgpio4out:1;	// GPIO 4: Output (else Input)
 uint8_t xgpio4pd:1;	// GPIO 4: Pull-Down (Input only)
 uint8_t xgpio5out:1;	// GPIO 5: Output (else Input)
 uint8_t xgpio5pd:1;	// GPIO 5: Pull-Down (Input only)
#ifdef	CONFIG_REVK_SETTINGS_PASSWORD
#endif
#ifdef  CONFIG_MDNS_MAX_INTERFACES
#else
#endif
 uint8_t otaauto:1;	// OTA auto upgrade
#ifdef	CONFIG_REVK_WEB_BETA
 uint8_t otabeta:1;	// OTA from beta release
#endif
 uint8_t dark:1;	// Default LED off
#ifdef  CONFIG_IDF_TARGET_ESP32S3
#endif
#ifdef  CONFIG_IDF_TARGET_ESP32S3
#else
#endif
 uint8_t prefixapp:1;	// MQTT use appname/ in front of hostname in topic
 uint8_t prefixhost:1;	// MQTT use (appname/)hostname/topic instead of topic/(appname/)hostname
#ifdef	CONFIG_REVK_BLINK_DEF
#ifdef	CONFIG_REVK_BLINK_WS2812_DEF
#ifdef	CONFIG_REVK_LED_TEST
#else
#endif
 uint8_t ws2812rgb:1;	// Reverse green and red on WS2812 LED
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
 uint8_t wifips:1;	// WiFi power save
 uint8_t wifimaxps:1;	// WiFi power save (max)
#ifdef CONFIG_REVK_ETHERNET
 uint8_t wifiminpower:1;	// Reduce WiFi TX power to minimum (2 dBm) — useful when Ethernet is primary and WiFi cannot be disabled
 uint8_t wifinoeth:1;	// Turn off WiFi when Ethernet online
#endif
#endif
#ifndef	CONFIG_REVK_MESH
 uint8_t aplr:1;	// AP LR mode
 uint8_t aphide:1;	// AP hide SSID
#endif
#ifdef	CONFIG_REVK_MESH
 uint8_t meshlr:1;	// Mesh use LR mode
 uint8_t meshroot:1;	// This is preferred mesh root
#endif
#ifdef	CONFIG_REVK_ETH_KSZ8851SNL
#if	CONFIG_REVK_ETH_POE_TIMER >= 0 && CONFIG_REVK_ETH_POE_LEDC >= 0
 uint8_t ethpoepwm:1;	// Ethernet POE load PWM rather than just turning off
#endif
#endif
};
#define	dump	revk_settings_bits.dump
#define	debug	revk_settings_bits.debug
#define	debughex	revk_settings_bits.debughex
#define	snoop	revk_settings_bits.snoop
#define	livestatus	revk_settings_bits.livestatus
#define	fixstatus	revk_settings_bits.fixstatus
#define	s21extra	revk_settings_bits.s21extra
extern uint8_t s21tries;	// Repeat attempts at S21 controls
#define	webcontrol	revk_settings_bits.webcontrol
#define	websettings	revk_settings_bits.websettings
extern char* model;	// Set model name manually
extern char* region;	// Region (legacy URLs)
#define	fahrenheit	revk_settings_bits.fahrenheit
#define	nos21	revk_settings_bits.nos21
#define	nox50a	revk_settings_bits.nox50a
#define	nocnwired	revk_settings_bits.nocnwired
#define	noas	revk_settings_bits.noas
#define	noswaptx	revk_settings_bits.noswaptx
#define	noswaprx	revk_settings_bits.noswaprx
#define	nodemand	revk_settings_bits.nodemand
#define	noauto	revk_settings_bits.noauto
#define	noecono	revk_settings_bits.noecono
#define	noswingv	revk_settings_bits.noswingv
#define	noswingh	revk_settings_bits.noswingh
#define	nocomfort	revk_settings_bits.nocomfort
#define	nostreamer	revk_settings_bits.nostreamer
#define	nopowerful	revk_settings_bits.nopowerful
#define	nosensor	revk_settings_bits.nosensor
#define	noquiet	revk_settings_bits.noquiet
#define	noled	revk_settings_bits.noled
#define	noflap	revk_settings_bits.noflap
#define	noantifreeze	revk_settings_bits.noantifreeze
#define	nohumidity	revk_settings_bits.nohumidity
#define	nohumidify	revk_settings_bits.nohumidify
#define	nohourly	revk_settings_bits.nohourly
#define	nofaikoutauto	revk_settings_bits.nofaikoutauto
#define	nohvacaction	revk_settings_bits.nohvacaction
#define	nofanauto	revk_settings_bits.nofanauto
#define	nohomepreset	revk_settings_bits.nohomepreset
#define	noicons	revk_settings_bits.noicons
#define	udpdiscovery	revk_settings_bits.udpdiscovery
#define	haenable	revk_settings_bits.haenable
#define	haswitches	revk_settings_bits.haswitches
#define	hafanrpm	revk_settings_bits.hafanrpm
#define	hacomprpm	revk_settings_bits.hacomprpm
#define	ha1c	revk_settings_bits.ha1c
#define	haperiodic	revk_settings_bits.haperiodic
#define	haram	revk_settings_bits.haram
#define	hauptime	revk_settings_bits.hauptime
extern char* hadomain;	// Local domain for HA links (blank for IP)
#define	cnmark900	revk_settings_bits.cnmark900
extern uint8_t fantype;	// Fan type override
#define	lockmode	revk_settings_bits.lockmode
extern uint8_t protocol;	// Internal protocol as found, saved when found, can be used with protofix
#define	protofix	revk_settings_bits.protofix
extern uint32_t reporting;	// Status report period (s)
extern uint8_t uart;	// UART number
extern uint8_t thermref;	// Percentage inlet rather than home temp used by your aircon
extern uint8_t switchtemp;	// Increase max (heating) or decrease min (cooling)
extern uint8_t pushtemp;	// Increase min (heating) or decrease max (cooling)
extern int8_t coolover;	// For cooling, push (decrease) target sent to aircon by this from min to force cooling before reaching target
extern uint8_t coolback;	// For cooling, pull (increase) target sent to aircon by this from max to stop cooling after reaching target
extern int8_t heatover;	// For heating, push (increase) target sent to aircon by this from max to force heating before reaching target
extern uint8_t heatback;	// For heating, pull (decrease) target sent to aircon by this from min to stop heating after reaching target
extern int8_t minoutside;	// Lowest allowed outside temp allowed for operation (if known)
extern int8_t frosttemp;	// Frost protect (below this, turn on hot regardless)
#define	temptrack	revk_settings_bits.temptrack
#define	tempadjust	revk_settings_bits.tempadjust
extern uint16_t tempnoflap;	// Min time between target temp changes
#ifdef CONFIG_BT_NIMBLE_ENABLED
#define	bleenable	revk_settings_bits.bleenable
extern char* autob;	// BLE sensor ID
#endif
#define	autoe	revk_settings_bits.autoe
extern uint16_t auto0;	// HHMM format turn off time
extern uint16_t auto1;	// HHMM format turn on time
extern uint16_t autot;	// Faikout auto target temperature
extern uint8_t autor;	// Faikout auto margin either side of autot
#define	autop	revk_settings_bits.autop
extern uint8_t autofmax;	// Max fan setting when starting heat/cool way off from target
extern uint8_t autoptemp;	// Auto power on/off by temperature deviation by this amount
#define	autolcontrol	revk_settings_bits.autolcontrol
extern char* autotopic;	// Topic to follow for reference temperature for Faikout auto
extern char* autopayload;	// JSON field in payload of above topic for reference temp
#define	thermostat	revk_settings_bits.thermostat
extern uint8_t tmin;	// Min temp setting of system
extern uint8_t tcoolmin;	// Min temp setting for Faikout auto when cooling
extern uint8_t tmax;	// Max temp setting of system
extern uint8_t theatmax;	// Max temp setting for Faikout auto when heating
extern uint32_t tpredicts;	// Temp prediction sample time
extern uint32_t tpredictt;	// Temp prediction total time factor
extern uint32_t tsample;	// Sample period for making adjustments
extern uint32_t tcontrol;	// Control messages timeout
#ifdef  CONFIG_IDF_TARGET_ESP32S3
extern revk_gpio_t tx;	// Tx
extern revk_gpio_t rx;	// Rx
#else
#ifdef  CONFIG_IDF_TARGET_ESP32C5
extern revk_gpio_t tx;	// Tx
extern revk_gpio_t rx;	// Rx
#else
extern revk_gpio_t tx;	// Tx
extern revk_gpio_t rx;	// Rx
#endif
#endif
#if CONFIG_SOC_I2C_NUM > 1 // we need 2 I2C bus for master and slave
#define	i2cen	revk_settings_bits.i2cen
extern int8_t i2chtemp;	// Offset to add to external sensor temp to reflect inlet temp when heating
extern int8_t i2cctemp;	// Offset to add to external sensor temp to reflect inlet temp when cooling
#if defined(CONFIG_IDF_TARGET_ESP32C5)
extern revk_gpio_t i2cslsda;	// GPIO to use for I2C slave with Daikin board - SDA
extern revk_gpio_t i2cslscl;	// GPIO to use for I2C slave with Daikin board - SCL
extern revk_gpio_t i2cmasda;	// GPIO to use for I2C master with inlet sensor - SDA - always LP I2C pins on this target
extern revk_gpio_t i2cmassl;	// GPIO to use for I2C master with inlet sensor - SCL - always LP I2C pins on this target
#elif defined(CONFIG_IDF_TARGET_ESP32C6)
extern revk_gpio_t i2cslsda;	// GPIO to use for I2C slave with Daikin board - SDA
extern revk_gpio_t i2cslscl;	// GPIO to use for I2C slave with Daikin board - SCL
extern revk_gpio_t i2cmasda;	// GPIO to use for I2C master with inlet sensor - SDA - always LP I2C pins on this target
extern revk_gpio_t i2cmassl;	// GPIO to use for I2C master with inlet sensor - SCL - always LP I2C pins on this target
#elif !defined(CONFIG_REVK_ETHERNET)
extern revk_gpio_t i2cslsda;	// GPIO to use for I2C slave with Daikin board - SDA
extern revk_gpio_t i2cslscl;	// GPIO to use for I2C slave with Daikin board - SCL
extern revk_gpio_t i2cmasda;	// GPIO to use for I2C master with inlet sensor - SDA
extern revk_gpio_t i2cmassl;	// GPIO to use for I2C master with inlet sensor - SCL
#else
extern revk_gpio_t i2cslsda;	// GPIO to use for I2C slave with Daikin board - SDA
extern revk_gpio_t i2cslscl;	// GPIO to use for I2C slave with Daikin board - SCL
extern revk_gpio_t i2cmasda;	// GPIO to use for I2C master with inlet sensor - SDA
extern revk_gpio_t i2cmassl;	// GPIO to use for I2C master with inlet sensor - SCL
#endif
#endif
extern char* xgpio1name;	// Label for Additional GPIO 1
extern revk_gpio_t xgpio1;	// Additional GPIO 1 (not set = disabled)
#define	xgpio1out	revk_settings_bits.xgpio1out
#define	xgpio1pd	revk_settings_bits.xgpio1pd
extern char* xgpio2name;	// Label for Additional GPIO 2
extern revk_gpio_t xgpio2;	// Additional GPIO 2
#define	xgpio2out	revk_settings_bits.xgpio2out
#define	xgpio2pd	revk_settings_bits.xgpio2pd
extern char* xgpio3name;	// Label for Additional GPIO 3
extern revk_gpio_t xgpio3;	// Additional GPIO 3
#define	xgpio3out	revk_settings_bits.xgpio3out
#define	xgpio3pd	revk_settings_bits.xgpio3pd
extern char* xgpio4name;	// Label for Additional GPIO 4
extern revk_gpio_t xgpio4;	// Additional GPIO 4
#define	xgpio4out	revk_settings_bits.xgpio4out
#define	xgpio4pd	revk_settings_bits.xgpio4pd
extern char* xgpio5name;	// Label for Additional GPIO 5
extern revk_gpio_t xgpio5;	// Additional GPIO 5
#define	xgpio5out	revk_settings_bits.xgpio5out
#define	xgpio5pd	revk_settings_bits.xgpio5pd
#ifdef	CONFIG_REVK_SETTINGS_PASSWORD
extern char* password;	// Settings password<br>(not sent securely so use with care)
#endif
#ifdef  CONFIG_MDNS_MAX_INTERFACES
extern char* hostname;	// Hostname[.local]<br>(used in DHCP and MQTT)
extern char* instance;	// Descriptive name of host, default is hostname
#else
extern char* hostname;	// Host name<br>(used in DHCP and MQTT)
#endif
extern char* otahost;	// OTA hostname
extern uint8_t otadays;	// OTA auto load (days)
extern uint16_t otastart;	// OTA check after startup (min seconds)
#define	otaauto	revk_settings_bits.otaauto
#ifdef	CONFIG_REVK_WEB_BETA
#define	otabeta	revk_settings_bits.otabeta
#endif
extern revk_settings_blob_t* otacert;	// OTA cert of otahost
#define	dark	revk_settings_bits.dark
extern char* ntphost;	// NTP host
extern char* tz;	// Timezone (<a href='https://gist.github.com/alwynallan/24d96091655391107939' target=_blank>info</a>)
extern uint32_t watchdogtime;	// Watchdog (seconds)
#ifdef  CONFIG_IDF_TARGET_ESP32S3
extern uint16_t usbuptime;	// USB  turns off after this many seconds
#endif
#ifdef  CONFIG_IDF_TARGET_ESP32S3
extern revk_gpio_t factorygpio;	// Factory reset GPIO (press 3 times)
#else
extern revk_gpio_t factorygpio;	// Factory reset GPIO (press 3 times)
#endif
extern char* topicgroup[2];	// MQTT Alternative hostname accepted for commands
extern char* topiccommand;	// MQTT Topic for commands
extern char* topicsetting;	// MQTT Topic for settings
extern char* topicstate;	// MQTT Topic for state
extern char* topicevent;	// MQTT Topic for event
extern char* topicinfo;	// MQTT Topic for info
extern char* topicerror;	// MQTT Topic for error
extern char* topicha;	// MQTT Topic for homeassistant
#define	prefixapp	revk_settings_bits.prefixapp
#define	prefixhost	revk_settings_bits.prefixhost
#ifdef	CONFIG_REVK_BLINK_DEF
#ifdef	CONFIG_REVK_BLINK_WS2812_DEF
#ifdef	CONFIG_REVK_LED_TEST
extern revk_gpio_t blink[2];	// WS2812 LED, and loop test
#else
extern revk_gpio_t blink;	// WS2812 LED
#endif
#define	ws2812rgb	revk_settings_bits.ws2812rgb
#else
#ifdef	CONFIG_REVK_LED_TEST
extern revk_gpio_t blink[3];	// R, G, B LED array (for WS2818, set first two the same, third can be loop test)
#else
extern revk_gpio_t blink[3];	// R, G, B LED array (for WS2812, set first two the same)
#endif
#endif
#endif
#ifdef  CONFIG_REVK_APMODE
#ifdef	CONFIG_REVK_APCONFIG
extern uint16_t apport;	// TCP port for config web pages on AP
#endif
extern uint32_t aptime;	// Limit AP to time (seconds)
extern uint32_t apwait;	// Wait off line before starting AP (seconds)
extern revk_gpio_t apgpio;	// Start AP on GPIO
#endif
#ifdef  CONFIG_REVK_MQTT
extern char* mqtthost[CONFIG_REVK_MQTT_CLIENTS];	// MQTT hostname
extern uint16_t mqttport[CONFIG_REVK_MQTT_CLIENTS];	// MQTT port
extern char* mqttuser[CONFIG_REVK_MQTT_CLIENTS];	// MQTT username
extern char* mqttpass[CONFIG_REVK_MQTT_CLIENTS];	// MQTT password
extern revk_settings_blob_t* mqttcert[CONFIG_REVK_MQTT_CLIENTS];	// MQTT CA certificate (for mqtts)
#endif
extern revk_settings_blob_t* clientkey;	// Client Key (MQTT TLS)
extern revk_settings_blob_t* clientcert;	// Client certificate (MQTT TLS)
#if     defined(CONFIG_REVK_WIFI) || defined(CONFIG_REVK_MESH)
extern uint16_t wifireset;	// Restart if WiFi off for this long (seconds)
extern char* wifissid;	// WiFI SSID (name)
extern char* wifipass;	// WiFi password
extern char* wifiip;	// WiFi Fixed IP/len or IPv6
extern char* wifigw;	// WiFi Fixed gateway
extern char* wifidns[3];	// WiFi fixed DNS
extern uint8_t wifibssid[6];	// WiFI BSSID
extern uint8_t wifichan;	// WiFI channel
extern uint16_t wifiuptime;	// WiFI turns off after this many seconds
#define	wifips	revk_settings_bits.wifips
#define	wifimaxps	revk_settings_bits.wifimaxps
#ifdef CONFIG_REVK_ETHERNET
#define	wifiminpower	revk_settings_bits.wifiminpower
#define	wifinoeth	revk_settings_bits.wifinoeth
#endif
#endif
#ifndef	CONFIG_REVK_MESH
extern char* apssid;	// AP mode SSID (name)
extern char* appass;	// AP mode password
extern uint8_t apmax;	// AP max clients
extern char* apip;	// AP mode block
#define	aplr	revk_settings_bits.aplr
#define	aphide	revk_settings_bits.aphide
#endif
#ifdef	CONFIG_REVK_MESH
extern char* nodename;	// Mesh node name
extern uint16_t meshreset;	// Reset if mesh off for this long (seconds)
extern uint8_t meshid[6];	// Mesh ID (hex)
extern uint8_t meshkey[16];	// Mesh key
extern uint16_t meshwidth;	// Mesh width
extern uint16_t meshdepth;	// Mesh depth
extern uint16_t meshmax;	// Mesh max devices
extern char* meshpass;	// Mesh AP password
#define	meshlr	revk_settings_bits.meshlr
#define	meshroot	revk_settings_bits.meshroot
#endif
#ifdef	CONFIG_REVK_ETH_KSZ8851SNL
extern revk_gpio_t ethcs;	// Ethernet SPI CS
extern revk_gpio_t ethmosi;	// Ethernet SPI MOSI
extern revk_gpio_t ethclk;	// Ethernet SPI CLK
extern revk_gpio_t ethmiso;	// Ethernet SPI MISO
extern revk_gpio_t ethwol;	// Ethernet SPI Wake on LAN
extern revk_gpio_t ethint;	// Ethernet SPI INT
extern revk_gpio_t ethrst;	// Ethernet SPI RST
extern revk_gpio_t ethpoeload;	// Ethernet POE load
#if	CONFIG_REVK_ETH_POE_TIMER >= 0 && CONFIG_REVK_ETH_POE_LEDC >= 0
#define	ethpoepwm	revk_settings_bits.ethpoepwm
#endif
extern char* ethip;	// Ethernet Fixed IP/len or IPv6
extern char* ethgw;	// Ethernet Fixed gateway
extern char* ethdns[3];	// Ethernet fixed DNS
#endif
extern revk_settings_bits_t revk_settings_bits;
enum {
 REVK_SETTINGS_SIGNED,
 REVK_SETTINGS_UNSIGNED,
 REVK_SETTINGS_BIT,
 REVK_SETTINGS_BLOB,
 REVK_SETTINGS_STRING,
 REVK_SETTINGS_OCTET,
};
#define REVK_SETTINGS_DUMP
#define REVK_SETTINGS_DEBUG
#define REVK_SETTINGS_DEBUGHEX
#define REVK_SETTINGS_SNOOP
#define REVK_SETTINGS_LIVESTATUS
#define REVK_SETTINGS_FIXSTATUS
#define REVK_SETTINGS_S21EXTRA
#define REVK_SETTINGS_S21TRIES
#define REVK_SETTINGS_WEBCONTROL
#define REVK_SETTINGS_WEBSETTINGS
#define REVK_SETTINGS_MODEL
#define REVK_SETTINGS_REGION
#define REVK_SETTINGS_FAHRENHEIT
#define REVK_SETTINGS_NOS21
#define REVK_SETTINGS_NOX50A
#define REVK_SETTINGS_NOCNWIRED
#define REVK_SETTINGS_NOAS
#define REVK_SETTINGS_NOSWAPTX
#define REVK_SETTINGS_NOSWAPRX
#define REVK_SETTINGS_NODEMAND
#define REVK_SETTINGS_NOAUTO
#define REVK_SETTINGS_NOECONO
#define REVK_SETTINGS_NOSWINGV
#define REVK_SETTINGS_NOSWINGH
#define REVK_SETTINGS_NOCOMFORT
#define REVK_SETTINGS_NOSTREAMER
#define REVK_SETTINGS_NOPOWERFUL
#define REVK_SETTINGS_NOSENSOR
#define REVK_SETTINGS_NOQUIET
#define REVK_SETTINGS_NOLED
#define REVK_SETTINGS_NOFLAP
#define REVK_SETTINGS_NOANTIFREEZE
#define REVK_SETTINGS_NOHUMIDITY
#define REVK_SETTINGS_NOHUMIDIFY
#define REVK_SETTINGS_NOHOURLY
#define REVK_SETTINGS_NOFAIKOUTAUTO
#define REVK_SETTINGS_NOHVACACTION
#define REVK_SETTINGS_NOFANAUTO
#define REVK_SETTINGS_NOHOMEPRESET
#define REVK_SETTINGS_NOICONS
#define REVK_SETTINGS_UDPDISCOVERY
#define REVK_SETTINGS_HAENABLE
#define REVK_SETTINGS_HASWITCHES
#define REVK_SETTINGS_HAFANRPM
#define REVK_SETTINGS_HACOMPRPM
#define REVK_SETTINGS_HA1C
#define REVK_SETTINGS_HAPERIODIC
#define REVK_SETTINGS_HARAM
#define REVK_SETTINGS_HAUPTIME
#define REVK_SETTINGS_HADOMAIN
#define REVK_SETTINGS_CNMARK900
#define REVK_SETTINGS_FANTYPE
#define REVK_SETTINGS_LOCKMODE
#define REVK_SETTINGS_PROTOCOL
#define REVK_SETTINGS_PROTOFIX
#define REVK_SETTINGS_REPORTING
#define REVK_SETTINGS_UART
#define REVK_SETTINGS_THERMREF
#define REVK_SETTINGS_SWITCHTEMP
#define REVK_SETTINGS_PUSHTEMP
#define REVK_SETTINGS_COOLOVER
#define REVK_SETTINGS_COOLBACK
#define REVK_SETTINGS_HEATOVER
#define REVK_SETTINGS_HEATBACK
#define REVK_SETTINGS_MINOUTSIDE
#define REVK_SETTINGS_FROSTTEMP
#define REVK_SETTINGS_TEMPTRACK
#define REVK_SETTINGS_TEMPADJUST
#define REVK_SETTINGS_TEMPNOFLAP
#ifdef CONFIG_BT_NIMBLE_ENABLED
#define REVK_SETTINGS_BLEENABLE
#define REVK_SETTINGS_AUTOB
#endif
#define REVK_SETTINGS_AUTOE
#define REVK_SETTINGS_AUTO0
#define REVK_SETTINGS_AUTO1
#define REVK_SETTINGS_AUTOT
#define REVK_SETTINGS_AUTOR
#define REVK_SETTINGS_AUTOP
#define REVK_SETTINGS_AUTOFMAX
#define REVK_SETTINGS_AUTOPTEMP
#define REVK_SETTINGS_AUTOLCONTROL
#define REVK_SETTINGS_AUTOTOPIC
#define REVK_SETTINGS_AUTOPAYLOAD
#define REVK_SETTINGS_THERMOSTAT
#define REVK_SETTINGS_TMIN
#define REVK_SETTINGS_TCOOLMIN
#define REVK_SETTINGS_TMAX
#define REVK_SETTINGS_THEATMAX
#define REVK_SETTINGS_TPREDICTS
#define REVK_SETTINGS_TPREDICTT
#define REVK_SETTINGS_TSAMPLE
#define REVK_SETTINGS_TCONTROL
#ifdef  CONFIG_IDF_TARGET_ESP32S3
#define REVK_SETTINGS_TX
#define REVK_SETTINGS_RX
#else
#ifdef  CONFIG_IDF_TARGET_ESP32C5
#define REVK_SETTINGS_TX
#define REVK_SETTINGS_RX
#else
#define REVK_SETTINGS_TX
#define REVK_SETTINGS_RX
#endif
#endif
#if CONFIG_SOC_I2C_NUM > 1 // we need 2 I2C bus for master and slave
#define REVK_SETTINGS_I2CEN
#define REVK_SETTINGS_I2CHTEMP
#define REVK_SETTINGS_I2CCTEMP
#if defined(CONFIG_IDF_TARGET_ESP32C5)
#define REVK_SETTINGS_I2CSLSDA
#define REVK_SETTINGS_I2CSLSCL
#define REVK_SETTINGS_I2CMASDA
#define REVK_SETTINGS_I2CMASSL
#elif defined(CONFIG_IDF_TARGET_ESP32C6)
#define REVK_SETTINGS_I2CSLSDA
#define REVK_SETTINGS_I2CSLSCL
#define REVK_SETTINGS_I2CMASDA
#define REVK_SETTINGS_I2CMASSL
#elif !defined(CONFIG_REVK_ETHERNET)
#define REVK_SETTINGS_I2CSLSDA
#define REVK_SETTINGS_I2CSLSCL
#define REVK_SETTINGS_I2CMASDA
#define REVK_SETTINGS_I2CMASSL
#else
#define REVK_SETTINGS_I2CSLSDA
#define REVK_SETTINGS_I2CSLSCL
#define REVK_SETTINGS_I2CMASDA
#define REVK_SETTINGS_I2CMASSL
#endif
#endif
#define REVK_SETTINGS_XGPIO1NAME
#define REVK_SETTINGS_XGPIO1
#define REVK_SETTINGS_XGPIO1OUT
#define REVK_SETTINGS_XGPIO1PD
#define REVK_SETTINGS_XGPIO2NAME
#define REVK_SETTINGS_XGPIO2
#define REVK_SETTINGS_XGPIO2OUT
#define REVK_SETTINGS_XGPIO2PD
#define REVK_SETTINGS_XGPIO3NAME
#define REVK_SETTINGS_XGPIO3
#define REVK_SETTINGS_XGPIO3OUT
#define REVK_SETTINGS_XGPIO3PD
#define REVK_SETTINGS_XGPIO4NAME
#define REVK_SETTINGS_XGPIO4
#define REVK_SETTINGS_XGPIO4OUT
#define REVK_SETTINGS_XGPIO4PD
#define REVK_SETTINGS_XGPIO5NAME
#define REVK_SETTINGS_XGPIO5
#define REVK_SETTINGS_XGPIO5OUT
#define REVK_SETTINGS_XGPIO5PD
#ifdef	CONFIG_REVK_SETTINGS_PASSWORD
#define REVK_SETTINGS_PASSWORD
#endif
#ifdef  CONFIG_MDNS_MAX_INTERFACES
#define REVK_SETTINGS_HOSTNAME
#define REVK_SETTINGS_INSTANCE
#else
#define REVK_SETTINGS_HOSTNAME
#endif
#define REVK_SETTINGS_OTAHOST
#define REVK_SETTINGS_OTADAYS
#define REVK_SETTINGS_OTASTART
#define REVK_SETTINGS_OTAAUTO
#ifdef	CONFIG_REVK_WEB_BETA
#define REVK_SETTINGS_OTABETA
#endif
#define REVK_SETTINGS_OTACERT
#define REVK_SETTINGS_DARK
#define REVK_SETTINGS_NTPHOST
#define REVK_SETTINGS_TZ
#define REVK_SETTINGS_WATCHDOGTIME
#ifdef  CONFIG_IDF_TARGET_ESP32S3
#define REVK_SETTINGS_USBUPTIME
#endif
#ifdef  CONFIG_IDF_TARGET_ESP32S3
#define REVK_SETTINGS_FACTORYGPIO
#else
#define REVK_SETTINGS_FACTORYGPIO
#endif
#define REVK_SETTINGS_TOPICGROUP
#define REVK_SETTINGS_TOPICCOMMAND
#define REVK_SETTINGS_TOPICSETTING
#define REVK_SETTINGS_TOPICSTATE
#define REVK_SETTINGS_TOPICEVENT
#define REVK_SETTINGS_TOPICINFO
#define REVK_SETTINGS_TOPICERROR
#define REVK_SETTINGS_TOPICHA
#define REVK_SETTINGS_PREFIXAPP
#define REVK_SETTINGS_PREFIXHOST
#ifdef	CONFIG_REVK_BLINK_DEF
#ifdef	CONFIG_REVK_BLINK_WS2812_DEF
#ifdef	CONFIG_REVK_LED_TEST
#define REVK_SETTINGS_BLINK
#else
#define REVK_SETTINGS_BLINK
#endif
#define REVK_SETTINGS_WS2812RGB
#else
#ifdef	CONFIG_REVK_LED_TEST
#define REVK_SETTINGS_BLINK
#else
#define REVK_SETTINGS_BLINK
#endif
#endif
#endif
#ifdef  CONFIG_REVK_APMODE
#ifdef	CONFIG_REVK_APCONFIG
#define REVK_SETTINGS_APPORT
#endif
#define REVK_SETTINGS_APTIME
#define REVK_SETTINGS_APWAIT
#define REVK_SETTINGS_APGPIO
#endif
#ifdef  CONFIG_REVK_MQTT
#define REVK_SETTINGS_MQTTHOST
#define REVK_SETTINGS_MQTTPORT
#define REVK_SETTINGS_MQTTUSER
#define REVK_SETTINGS_MQTTPASS
#define REVK_SETTINGS_MQTTCERT
#endif
#define REVK_SETTINGS_CLIENTKEY
#define REVK_SETTINGS_CLIENTCERT
#if     defined(CONFIG_REVK_WIFI) || defined(CONFIG_REVK_MESH)
#define REVK_SETTINGS_WIFIRESET
#define REVK_SETTINGS_WIFISSID
#define REVK_SETTINGS_WIFIPASS
#define REVK_SETTINGS_WIFIIP
#define REVK_SETTINGS_WIFIGW
#define REVK_SETTINGS_WIFIDNS
#define REVK_SETTINGS_WIFIBSSID
#define REVK_SETTINGS_WIFICHAN
#define REVK_SETTINGS_WIFIUPTIME
#define REVK_SETTINGS_WIFIPS
#define REVK_SETTINGS_WIFIMAXPS
#ifdef CONFIG_REVK_ETHERNET
#define REVK_SETTINGS_WIFIMINPOWER
#define REVK_SETTINGS_WIFINOETH
#endif
#endif
#ifndef	CONFIG_REVK_MESH
#define REVK_SETTINGS_APSSID
#define REVK_SETTINGS_APPASS
#define REVK_SETTINGS_APMAX
#define REVK_SETTINGS_APIP
#define REVK_SETTINGS_APLR
#define REVK_SETTINGS_APHIDE
#endif
#ifdef	CONFIG_REVK_MESH
#define REVK_SETTINGS_NODENAME
#define REVK_SETTINGS_MESHRESET
#define REVK_SETTINGS_MESHID
#define REVK_SETTINGS_MESHKEY
#define REVK_SETTINGS_MESHWIDTH
#define REVK_SETTINGS_MESHDEPTH
#define REVK_SETTINGS_MESHMAX
#define REVK_SETTINGS_MESHPASS
#define REVK_SETTINGS_MESHLR
#define REVK_SETTINGS_MESHROOT
#endif
#ifdef	CONFIG_REVK_ETH_KSZ8851SNL
#define REVK_SETTINGS_ETHCS
#define REVK_SETTINGS_ETHMOSI
#define REVK_SETTINGS_ETHCLK
#define REVK_SETTINGS_ETHMISO
#define REVK_SETTINGS_ETHWOL
#define REVK_SETTINGS_ETHINT
#define REVK_SETTINGS_ETHRST
#define REVK_SETTINGS_ETHPOELOAD
#if	CONFIG_REVK_ETH_POE_TIMER >= 0 && CONFIG_REVK_ETH_POE_LEDC >= 0
#define REVK_SETTINGS_ETHPOEPWM
#endif
#define REVK_SETTINGS_ETHIP
#define REVK_SETTINGS_ETHGW
#define REVK_SETTINGS_ETHDNS
#endif
#define	REVK_SETTINGS_HAS_ENUM
#define	REVK_SETTINGS_HAS_OLD
#define	REVK_SETTINGS_HAS_UNIT
#define	REVK_SETTINGS_HAS_COMMENT
#define	REVK_SETTINGS_HAS_GPIO
#define	REVK_SETTINGS_HAS_NUMERIC
#define	REVK_SETTINGS_HAS_SIGNED
#define	REVK_SETTINGS_HAS_UNSIGNED
#define	REVK_SETTINGS_HAS_BIT
#define	REVK_SETTINGS_HAS_BLOB
#define	REVK_SETTINGS_HAS_STRING
#define	REVK_SETTINGS_HAS_OCTET
#define	switchtemp_scale	10
#define	pushtemp_scale	10
#define	autot_scale	10
#define	autor_scale	10
#define	autoptemp_scale	10
#define	i2chtemp_scale	10
#define	i2cctemp_scale	10
typedef uint8_t revk_setting_bits_t[28];
typedef uint8_t revk_setting_group_t[3];
extern const char revk_settings_secret[];
