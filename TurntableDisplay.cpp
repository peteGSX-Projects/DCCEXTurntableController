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

TurntableDisplay::TurntableDisplay(TFT_eSPI &display, DCCEXProtocol &csClient, uint16_t backgroundColour,
                                   uint8_t pitOffset, uint16_t pitColour, uint16_t homeColour, uint16_t positionColour,
                                   uint16_t bridgeColour, uint16_t bridgePositionColour)
    : _display(display), _csClient(csClient), _backgroundColour(backgroundColour), _pitOffset(pitOffset),
      _pitColour(pitColour), _homeColour(homeColour), _positionColour(positionColour), _bridgeColour(bridgeColour),
      _bridgePositionColour(bridgePositionColour) {
  _bridgePosition = 255; // Set to max to ensure first redraw of the bridge will occur
}

void TurntableDisplay::begin() {
  Turntable *turntable = _csClient.turntables->getFirst();
  if (turntable) {
    _drawTurntable();
    drawBridge();
  }
}

void TurntableDisplay::drawBridge() {
  Turntable *turntable = _csClient.turntables->getFirst();
  if (turntable) {
    uint8_t newPosition = turntable->getIndex();
    if (_bridgePosition != newPosition) {
      _display.fillScreen(_backgroundColour);
      _bridgePosition = newPosition;
      uint8_t currentPosition = turntable->getIndex();
      char *positionName = nullptr;
      uint16_t positionAngle = 0;
      for (TurntableIndex *index = turntable->getFirstIndex(); index; index = index->getNextIndex()) {
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
}

void TurntableDisplay::_drawTurntable() {}
