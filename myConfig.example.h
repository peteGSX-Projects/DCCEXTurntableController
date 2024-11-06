/*
 *  This is the example myConfig.h file for DCCEXTurntableController
 *
 *  If custom configuration is required, copy this file to "myConfig.h", and note that this is case sensitive, and on
 *  Windows in particular, ensure it doesn't add a ".txt" extension.
 *
 *  Uncomment any line (remove the "//" at the beginning) and change any required parameters.
 *
 *  Note that TFT_eSPI requires explicit configuration to work, and you will need to remain the library documentation.
 */

#ifndef MYCONFIG_H
#define MYCONFIG_H

// EDIT NOTHING ABOVE THIS LINE

/*
If required, define the console and DCC-EX client connection streams here
Only define *either* SERIAL_CLIENT or WIFI_CLIENT
ENABLE_HEARTBEAT is on by default for WiFi only to send every 60 seconds
*/
// #define CONSOLE Serial // default
// #define CLIENT_TYPE SERIAL_CLIENT // default
// #define CLIENT_TYPE WIFI_CLIENT
// #define CS_CONNECTION Serial1 // default
// #define ENABLE_HEARTBEAT 60000 // default with WIFI_CLIENT

/*
If defining WIFI_CLIENT, set your WiFi and CommandStation details here
*/
// #define WIFI_SSID "Your WiFi SSID"
// #define WIFI_PASSWORD "Your WiFi password"
// #define COMMANDSTATION_IP "192.168.4.1"
// #define COMMANDSTATION_PORT 2560

/*
If required, define the rotary encoder pins and options here
*/
// #define ROTARY_BTN PB15 // Blackpill default
// #define ROTARY_BTN 25 // ESP32 default
// #define ROTARY_DT PB14 // Blackpill default
// #define ROTARY_DT 26 // ESP32 default
// #define ROTARY_CLK PB13 // Blackpill default
// #define ROTARY_CLK 27 // ESP32 default

// #define FULL_STEP // Use this to enable a full step of the rotary encoder
// #define HALF_STEP // Use this to enable a half step of the rotary encoder (default)

/*
If required, define the GC9A01 display pins here
Note only backlight is defined here, the rest should be in the TFT_eSPI config
*/
// #define GC9A01_BL PA1 // Blackpill default
// #define GC9A01_BL 21 // ESP32 default

/*
If required, define GC9A01 options here
*/
// #define GC9A01_ROTATION 0

/*
If required, define colours here
*/
// #define BACKGROUND_COLOUR TFT_BLACK
// #define POSITION_TEXT_COLOUR TFT_GREENYELLOW
// #define BRIDGE_COLOUR TFT_RED
// #define BRIDGE_MOVING_COLOUR TFT_DARKCYAN
// #define PIT_COLOUR TFT_BLUE
// #define BRIDGE_POSITION_COLOUR TFT_YELLOW
// #define HOME_COLOUR TFT_CYAN
// #define POSITION_COLOUR TFT_MAGENTA

/*
If required, define the blink delay here (in ms)
*/
// #define BLINK_DELAY 500

/*
If required, define the text font here
*/
// #define TEXT_FONT &FreeSansBold12pt7b

/*
If required, define turntable display parameters here
*/
// #define PIT_OFFSET 30

// EDIT NOTHING BELOW THIS LINE

#endif // MYCONFIG_H
