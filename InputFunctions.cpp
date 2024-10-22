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

#include "DeviceFunctions.h"
#include "InputFunctions.h"
#include "Rotary.h"
#include "avdweb_Switch.h"

Rotary encoder = Rotary(ROTARY_DT, ROTARY_CLK);
Switch encoderButton(ROTARY_BTN);

void processInput() {
  encoderButton.poll();
  if (encoderButton.singleClick()) {
    CONSOLE.println("Select position");
  }
  if (encoderButton.doubleClick()) {
    CONSOLE.println("Home");
  }
  if (encoderButton.longPress()) {
    resetDevice();
  }
  byte direction = encoder.process();
  if (direction == DIR_CW) {
    CONSOLE.println("Clockwise");
  } else if (direction == DIR_CCW) {
    CONSOLE.println("Counter-clockwise");
  }
}
