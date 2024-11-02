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
*/
// #define CONSOLE Serial
// #define CS_CONNECTION Serial1

/*
If required, define the rotary encoder pins and options here
*/
// #define ROTARY_BTN PB15
// #define ROTARY_DT PB14
// #define ROTARY_CLK PB13
// #define FULL_STEP // Use this to enable a full step of the rotary encoder
// #define HALF_STEP // Use this to enable a half step of the rotary encoder (default)

/*
If required, define the GC9A01 display pins here
Note only backlight is defined here, the rest should be in the TFT_eSPI config
*/
// #define GC9A01_BL PA1

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
