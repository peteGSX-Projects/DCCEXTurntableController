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
*/
#ifndef CONSOLE
#define CONSOLE Serial
#endif // CONSOLE
#ifndef CS_CONNECTION
#define CS_CONNECTION Serial1
#endif // CS_CONNECTION

/*
If not defined in myConfig.h, define the rotary encoder pins and options here
*/
#ifndef ROTARY_BTN
#define ROTARY_BTN PB15
#endif // ROTARY_BTN
#ifndef ROTARY_DT
#define ROTARY_DT PB14
#endif // ROTARY_DT
#ifndef ROTARY_CLK
#define ROTARY_CLK PB13
#endif // ROTARY_CLK
#ifndef FULL_STEP
#define HALF_STEP
#endif // FULL_STEP

/*
If not defined in myConfig.h, define the GC9A01 display pins here
*/
#ifndef GC9A01_BL
#define GC9A01_BL PA1
#endif // GC9A01_BL

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
#ifndef TEXT_COLOUR
#define TEXT_COLOUR TFT_GREENYELLOW
#endif // TEXT_COLOUR
#ifndef BRIDGE_COLOUR
#define BRIDGE_COLOUR TFT_RED
#endif // BRIDGE_COLOUR
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

/*
Colour definitions and font for the DCC-EX logo
*/
#define DCCEX_DCC 0x01C8
#define DCCEX_EX 0x03B6
#define DCCEX_BACKGROUND 0xFFFF
#define DCCEX_FONT &FreeSansBold12pt7b
#define DCCEX_SMALL_FONT &FreeMono9pt7b
#define DCCEX_VERSION_FONT &FreeMonoBold9pt7b

#endif // DEFINES_H
