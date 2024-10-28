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

TurntableDisplay::TurntableDisplay(TFT_eSprite &displaySprite, DCCEXProtocol &csClient, uint16_t backgroundColour,
                                   uint8_t pitOffset, uint16_t pitColour, uint16_t homeColour, uint16_t positionColour,
                                   uint16_t bridgeColour, uint16_t bridgePositionColour)
    : _displaySprite(displaySprite), _csClient(csClient), _backgroundColour(backgroundColour), _pitOffset(pitOffset),
      _pitColour(pitColour), _homeColour(homeColour), _positionColour(positionColour), _bridgeColour(bridgeColour),
      _bridgePositionColour(bridgePositionColour) {
  _bridgePosition = 0;                        // Start at home, will update once begin called
  const GFXfont *gfxFont = TEXT_FONT;         // Set font from macro TEXT_FONT, no way to get it from the display object
  _fontHeight = gfxFont->yAdvance;            // Get the font height
  _fontWidth = _displaySprite.textWidth("A"); // Get the font width
}

void TurntableDisplay::begin() {
  Turntable *turntable = _csClient.turntables->getFirst();
  if (turntable) {
    _drawTurntable();
    _drawPositionName(0);
  }
}

void TurntableDisplay::update(unsigned long updateTime) {}

void TurntableDisplay::setNextPosition() {
  Turntable *turntable = _csClient.turntables->getFirst();
  if (!turntable) // No turntable object, don't try to do anything
    return;
  uint8_t maxPosition = turntable->getIndexCount() - 1;
  if (maxPosition == 0) // If we only have home, don't try to do anything
    return;
  if (_bridgePosition == maxPosition) {
    _bridgePosition = 1; // Cannot send home via this method, so skip it
  } else if (_bridgePosition < maxPosition) {
    _bridgePosition++; // Increment to the next position
  } else {
    _bridgePosition = 0;
  }
}

void TurntableDisplay::setPreviousPosition() {
  Turntable *turntable = _csClient.turntables->getFirst();
  if (!turntable) // No turntable object, don't try to do anything
    return;
  uint8_t maxPosition = turntable->getIndexCount() - 1;
  if (maxPosition == 0) // If we only have home, don't try to do anything
    return;
  if (_bridgePosition == 1) {
    _bridgePosition = maxPosition; // Cannot send home via this method, so skip it
  } else if (_bridgePosition > 0) {
    _bridgePosition--; // Decrement to previous position
  } else {
    _bridgePosition = 0;
  }
}

void TurntableDisplay::setPosition(uint8_t position) { _bridgePosition = position; }

uint8_t TurntableDisplay::getPosition() { return _bridgePosition; }

void TurntableDisplay::_drawPositionName(uint8_t position) {
  Turntable *turntable = _csClient.turntables->getFirst();
  if (turntable) {
    char *positionName = nullptr;
    uint16_t positionAngle = 0;
    for (TurntableIndex *index = turntable->getFirstIndex(); index; index = index->getNextIndex()) {
      if (index->getId() == position) {
        positionName = index->getName();
        positionAngle = index->getAngle();
        break;
      }
    }
    Coordinates stringPosition = _getTextPosition(positionName);
    _displaySprite.drawString(positionName, stringPosition.x, stringPosition.y);
    CONSOLE.print("Draw bridge position|name|angle|x|y: ");
    CONSOLE.print(position);
    CONSOLE.print("|");
    CONSOLE.print(positionName);
    CONSOLE.print("|");
    CONSOLE.print(positionAngle);
    CONSOLE.print("|");
    CONSOLE.print(stringPosition.x);
    CONSOLE.print("|");
    CONSOLE.println(stringPosition.y);
  }
}

void TurntableDisplay::_drawTurntable() {
  _displaySprite.fillSprite(_backgroundColour);
  uint16_t x = _displaySprite.width() / 2;
  uint16_t y = _displaySprite.height() / 2;
  uint16_t radius = min(x, y) - _pitOffset;
  CONSOLE.print("Draw pit x|y|outer radius|inner radius: ");
  CONSOLE.print(x);
  CONSOLE.print("|");
  CONSOLE.print(y);
  CONSOLE.print("|");
  CONSOLE.print(radius);
  _displaySprite.fillSmoothCircle(x, y, radius, _pitColour, _backgroundColour);
  radius -= 3;
  CONSOLE.print("|");
  CONSOLE.println(radius);
  _displaySprite.fillSmoothCircle(x, y, radius, _backgroundColour);
  _displaySprite.pushSprite(0, 0);
}

Coordinates TurntableDisplay::_getTextPosition(const char *text) {
  Coordinates coordinates;
  uint16_t textWidth = strlen(text) * _fontWidth;
  coordinates.x = ((_displaySprite.width() / 2) - (textWidth / 2));
  coordinates.y = (_displaySprite.height() / 2) - (_fontHeight / 2);
  return coordinates;
}
