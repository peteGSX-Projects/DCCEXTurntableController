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
If not defined in myConfig.h, define the rotary encoder pins here
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

/*
If not defined in myConfig.h, define the GC9A01 display pins here
*/
#ifndef GC9A01_DIN
#define GC9A01_DIN PA7
#endif // GC9A01_DIN
#ifndef GC9A01_CLK
#define GC9A01_CLK PA5
#endif // GC9A01_CLK
#ifndef GC9A01_CS
#define GC9A01_CS PA4
#endif // GC9A01_CS
#ifndef GC9A01_DC
#define GC9A01_DC PA3
#endif // GC9A01_DC
#ifndef GC9A01_RST
#define GC9A01_RST PA2
#endif // GC9A01_RST
#ifndef GC9A01_BL
#define GC9A01_BL PA1
#endif // GC9A01_BL

#endif // DEFINES_H
