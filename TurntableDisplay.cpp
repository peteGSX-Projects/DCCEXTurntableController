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

#include "Defines.h"
#include "TurntableDisplay.h"

TurntableDisplay::TurntableDisplay(TFT_eSPI &display, Turntable &dccexTurntable, uint16_t backgroundColour,
                                   uint8_t pitOffset, uint16_t pitColour, uint16_t homeColour, uint16_t positionColour,
                                   uint16_t bridgeColour, uint16_t bridgePositionColour)
    : _display(display), _dccexTurntable(dccexTurntable), _backgroundColour(backgroundColour),
      _bridgeColour(bridgeColour), _bridgePositionColour(bridgePositionColour) {
  _bridgePosition = 255; // Set to max to ensure first redraw of the bridge will occur
  _drawTurntable(pitOffset, pitColour, homeColour, positionColour);
  drawBridge();
}

void TurntableDisplay::drawBridge() {
  _display.fillScreen(_backgroundColour);
  uint8_t newPosition = _dccexTurntable.getIndex();
  if (_bridgePosition != newPosition) {
    _bridgePosition = newPosition;
    uint8_t currentPosition = _dccexTurntable.getIndex();
    char *positionName = nullptr;
    uint16_t positionAngle = 0;
    for (TurntableIndex *index = _dccexTurntable.getFirstIndex(); index; index = index->getNextIndex()) {
      if (index->getId() == currentPosition) {
        positionName = index->getName();
        positionAngle = index->getAngle();
        break;
      }
    }
    CONSOLE.println("Need to draw bridge position|name|angle");
    CONSOLE.print(newPosition);
    CONSOLE.print("|");
    CONSOLE.print(positionName);
    CONSOLE.print("|");
    CONSOLE.println(positionAngle);
  }
}

void TurntableDisplay::_drawTurntable(uint8_t pitOffset, uint16_t pitColour, uint16_t homeColour,
                                      uint16_t positionColour) {}
