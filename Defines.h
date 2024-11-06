/*
 *  © 2024 Peter Cole
 *
 *  This is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  It is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this code.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef DEFINES_H
#define DEFINES_H

#include <TFT_eSPI.h>

#define SERIAL_CLIENT 1
#define WIFI_CLIENT 2

/*
If we haven't got a custom config.h, use the example
*/
#if __has_include("myConfig.h")
#include "myConfig.h"
#else
#warning myConfig.h not found, Using defaults
#endif

/*
If not defined in myConfig.h, define the console and DCC-EX client connection streams here
Default client type is serial
*/
#ifndef CONSOLE
#define CONSOLE Serial
#endif // CONSOLE
#ifndef CLIENT_TYPE
#define CLIENT_TYPE SERIAL_CLIENT
#endif // CLIENT_TYPE
#ifndef CS_CONNECTION
#define CS_CONNECTION Serial1
#endif // CS_CONNECTION

#if (CLIENT_TYPE == WIFI_CLIENT) // Only process WiFi details if that's the client type
#if defined(ARDUINO_ARCH_STM32)  // If WiFi defined and using Blackpill, error
#error "You cannot enable a WiFi client unless using the supported ESP32 microcontroller"
#endif
/*
If not defined in myConfig.h, define placeholder WiFi connection details
*/
#ifndef WIFI_SSID
#define WIFI_SSID "Your WiFi SSID Here"
#endif // WIFI_SSID
#ifndef WIFI_PASSWORD
#define WIFI_PASSWORD "Your WiFi password here"
#endif // WIFI_PASSWORD
#ifndef COMMANDSTATION_IP
#define COMMANDSTATION_IP "192.168.4.1"
#endif // COMMANDSTATION_IP
#ifndef COMMANDSTATION_PORT
#define COMMANDSTATION_PORT 2560
#endif // COMMANDSTATION_PORT
#ifndef ENABLE_HEARTBEAT
#define ENABLE_HEARTBEAT 60000
#endif // ENABLE_HEARTBEAT

#endif // CLIENT_TYPE==WIFI_CLIENT

/*
If not defined in myConfig.h, define the rotary encoder pins and options here
*/
#if defined(ARDUINO_ARCH_STM32) // Blackpill defaults
#ifndef ROTARY_BTN
#define ROTARY_BTN PB15
#endif // ROTARY_BTN
#ifndef ROTARY_DT
#define ROTARY_DT PB14
#endif // ROTARY_DT
#ifndef ROTARY_CLK
#define ROTARY_CLK PB13
#endif                            // ROTARY_CLK
#elif defined(ARDUINO_ARCH_ESP32) // ESP32 defaults
#ifndef ROTARY_BTN
#define ROTARY_BTN 25
#endif // ROTARY_BTN
#ifndef ROTARY_DT
#define ROTARY_DT 26
#endif // ROTARY_DT
#ifndef ROTARY_CLK
#define ROTARY_CLK 27
#endif // ROTARY_CLK
#endif // ARCH type
#ifndef FULL_STEP
#define HALF_STEP
#endif // FULL_STEP

/*
If not defined in myConfig.h, define the GC9A01 display pins here
Note only backlight is defined here, the rest should be in the TFT_eSPI config
*/
#if defined(ARDUINO_ARCH_STM32) // Blackpill defaults
#ifndef GC9A01_BL
#define GC9A01_BL PA1
#endif                            // GC9A01_BL
#elif defined(ARDUINO_ARCH_ESP32) // ESP32 defaults
#ifndef GC9A01_BL
#define GC9A01_BL 21
#endif // GC9A01_BL
#endif // ARCH type

/*
If not defined in myConfig.h, define GC9A01 default options here
*/
#ifndef GC9A01_ROTATION
#define GC9A01_ROTATION 0
#endif // GC9A01_ROTATION

/*
If not defined in myConfig.h, define default colours here
*/
#ifndef BACKGROUND_COLOUR
#define BACKGROUND_COLOUR TFT_BLACK
#endif // BACKGROUND_COLOUR
#ifndef POSITION_TEXT_COLOUR
#define POSITION_TEXT_COLOUR TFT_GREENYELLOW
#endif // POSITION_TEXT_COLOUR
#ifndef BRIDGE_COLOUR
#define BRIDGE_COLOUR TFT_RED
#endif // BRIDGE_COLOUR
#ifndef BRIDGE_MOVING_COLOUR
#define BRIDGE_MOVING_COLOUR TFT_DARKCYAN
#endif // BRIDGE_MOVING COLOUR
#ifndef PIT_COLOUR
#define PIT_COLOUR TFT_BLUE
#endif // PIT_COLOUR
#ifndef BRIDGE_POSITION_COLOUR
#define BRIDGE_POSITION_COLOUR TFT_YELLOW
#endif // BRIDGE_POSITION_COLOUR
#ifndef HOME_COLOUR
#define HOME_COLOUR TFT_CYAN
#endif // HOME_COLOUR
#ifndef POSITION_COLOUR
#define POSITION_COLOUR TFT_MAGENTA
#endif // POSITION_COLOUR

/*
If not defined in myConfig.h, define the blink delay here (in ms)
*/
#ifndef BLINK_DELAY
#define BLINK_DELAY 500
#endif // BLINK_DELAY

/*
If not defined in myConfig.h, define the text font here
*/
#ifndef TEXT_FONT
#define TEXT_FONT &FreeSansBold12pt7b
#endif // TEXT_FONT

/*
If not defined in myConfig.h, define turntable display parameters here
*/
#ifndef PIT_OFFSET
#define PIT_OFFSET 30
#endif // PIT_OFFSET

#endif // DEFINES_H
