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

#ifndef VERSION_H
#define VERSION_H

#define VERSION "0.0.10"

/*
0.0.10 includes:
  - Generate compiler error if using an unsupported platform
0.0.9 includes:
  - Minor change to cater for the upcoming DCCEXProtocol library 1.0.0 release
0.0.8 includes:
  - Refactor TurntableDisplay class to only utilise a turntable object
  - Allow user to specify a turntable object ID to operate
0.0.7 includes:
  - Add support for ESP32 as both WiFi and serial client
  - Set TFT_eSprite to 8 bit colour to fit in RAM
  - Fix bug where nullptr position name causes a crash
0.0.6 includes:
  - Correct logic to calculate position angles from home
0.0.5 includes:
  - Update DCCEXProtocol dependency to 0.0.17 for isMoving() bugfix
  - Add heartbeat to prevent client disconnects (preparation for WiFi)
0.0.4 includes:
  - Display home and position indicators on screen around the pit wall
  - Fix angles to divide by 10 as per DCC-EX configuration
0.0.3 includes:
  - Display turntable bridge on screen with home end indicator
  - Blink bridge with position name when turntable moving
0.0.2 includes:
  - Display selected position name on screen
  - Blink position name when turntable moving
0.0.1 includes:
  - Initial version
  - Request and control first defined turntable object from EX-CS
  - Basic control implemented without display elements
*/

#endif // VERSION_H
