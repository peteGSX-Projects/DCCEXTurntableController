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

#include "CommandStationClient.h"
#include "DeviceFunctions.h"
#include "DisplayFunctions.h"
#include "InputFunctions.h"
#include "Rotary.h"
#include "avdweb_Switch.h"

Rotary encoder = Rotary(ROTARY_DT, ROTARY_CLK);
Switch encoderButton(ROTARY_BTN);

void processEncoderButton() {
  encoderButton.poll();
  if (encoderButton.singleClick()) {
    sendPositionChange();
  }
  if (encoderButton.doubleClick()) {
    sendHome();
  }
  if (encoderButton.longPress()) {
    resetDevice();
  }
}

void processEncoder() {
  byte direction = encoder.process();
  if (direction == DIR_CW) {
    turntableDisplay.setNextPosition();
    CONSOLE.print("User set to position ");
    CONSOLE.println(turntableDisplay.getPosition());
  } else if (direction == DIR_CCW) {
    turntableDisplay.setPreviousPosition();
    CONSOLE.print("User set to position ");
    CONSOLE.println(turntableDisplay.getPosition());
  }
}

void sendPositionChange() {
  Turntable *turntable = csClient.turntables->getFirst();
  if (turntable) {
    if (turntableDisplay.getPosition() != turntable->getIndex()) {
      if (turntableDisplay.getPosition() == 0) {
        sendHome(); // Homing needs the correct activity set, use this instead
      } else {
        csClient.rotateTurntable(turntable->getId(), turntableDisplay.getPosition());
      }
    }
  }
}

void sendHome() {
  Turntable *turntable = csClient.turntables->getFirst();
  if (turntable) {
    csClient.rotateTurntable(turntable->getId(), 0, 2);
  }
}
