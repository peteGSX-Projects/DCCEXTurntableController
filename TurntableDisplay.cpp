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
                                   uint16_t bridgeColour, uint16_t bridgeMovingColour, uint16_t bridgePositionColour,
                                   uint16_t positionTextColour, unsigned long blinkDelay)
    : _displaySprite(displaySprite), _csClient(csClient), _backgroundColour(backgroundColour), _pitOffset(pitOffset),
      _pitColour(pitColour), _homeColour(homeColour), _positionColour(positionColour), _bridgeColour(bridgeColour),
      _bridgeMovingColour(bridgeMovingColour), _bridgePositionColour(bridgePositionColour),
      _positionTextColour(positionTextColour), _blinkDelay(blinkDelay) {
  _bridgePosition = 0; // Start at home, will update once begin called
  _lastBlinkTime = 0;  // Default time to 0
  _blinkState = true;  // Default to bridge and text being displayed
  _needsRedraw = true; // Default to needing to draw the display
  _isMoving = false;   // Default to not moving
}

void TurntableDisplay::begin() {
  Turntable *turntable = _csClient.turntables->getFirst();
  if (turntable) {
    update();
  }
}

void TurntableDisplay::update() {
  if (!_needsRedraw && !_isMoving) // Don't need to update if it doesn't need it, and it's not moving
    return;
  Turntable *turntable = _csClient.turntables->getFirst();
  if (!turntable) // If we don't have a turntable object, can't do anything
    return;
  unsigned long currentTime = millis();
  if (_isMoving && (currentTime - _lastBlinkTime > _blinkDelay)) { // Blink at the defined rate
    _lastBlinkTime = currentTime;
    _blinkState = !_blinkState;
  } else if (!_isMoving) { // Ensure when a movement has finished that we set state to be on
    _needsRedraw = false;
    _blinkState = true;
  } else {
    _needsRedraw = false;
  }
  _drawTurntable();
  _drawBridge();
  _drawPositionName();
  _displaySprite.pushSprite(0, 0);
}

void TurntableDisplay::setNextPosition() {
  Turntable *turntable = _csClient.turntables->getFirst();
  if (!turntable) // No turntable object, don't try to do anything
    return;
  uint8_t maxPosition = turntable->getIndexCount() - 1;
  if (maxPosition == 0) // If we only have home, don't try to do anything
    return;
  if (_bridgePosition == maxPosition) {
    _bridgePosition = 0; // If at max, move to home next
  } else if (_bridgePosition < maxPosition) {
    _bridgePosition++; // Increment to the next position
  } else {
    _bridgePosition = 0;
  }
  _needsRedraw = true;
}

void TurntableDisplay::setPreviousPosition() {
  Turntable *turntable = _csClient.turntables->getFirst();
  if (!turntable) // No turntable object, don't try to do anything
    return;
  uint8_t maxPosition = turntable->getIndexCount() - 1;
  if (maxPosition == 0) // If we only have home, don't try to do anything
    return;
  if (_bridgePosition == 0) {
    _bridgePosition = maxPosition; // If we're at home, max is next
  } else if (_bridgePosition > 0) {
    _bridgePosition--; // Decrement to previous position
  } else {
    _bridgePosition = 0;
  }
  _needsRedraw = true;
}

void TurntableDisplay::setPosition(uint8_t position, bool moving) {
  Turntable *turntable = _csClient.turntables->getFirst();
  if (!turntable)
    return;
  _isMoving = moving;
  // _isMoving = turntable->isMoving(); CANNOT USE THIS METHOD - suspected bug in protocol library
  _bridgePosition = position;
  _needsRedraw = true;
}

uint8_t TurntableDisplay::getPosition() { return _bridgePosition; }

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
}

void TurntableDisplay::_drawBridge() {}

void TurntableDisplay::_drawPositionName() {
  Turntable *turntable = _csClient.turntables->getFirst();
  if (!turntable)
    return;
  char *positionName = nullptr;
  for (TurntableIndex *index = turntable->getFirstIndex(); index; index = index->getNextIndex()) {
    if (index->getId() == _bridgePosition) {
      positionName = index->getName();
      break;
    }
  }
  uint16_t x = _displaySprite.width() / 2;
  uint16_t y = _displaySprite.height() / 2;
  _displaySprite.setFreeFont(TEXT_FONT);
  _displaySprite.setTextDatum(MC_DATUM);
  if (_blinkState) {
    _displaySprite.setTextColor(_positionTextColour);
  } else {
    _displaySprite.setTextColor(_backgroundColour);
  }
  _displaySprite.drawString(positionName, x, y);
  CONSOLE.print("Draw position|_blinkState|name: ");
  CONSOLE.print(_bridgePosition);
  CONSOLE.print("|");
  CONSOLE.print(_blinkState);
  CONSOLE.print("|");
  CONSOLE.println(positionName);
}
