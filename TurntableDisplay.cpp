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
  _homeAngle = 0;      // Default to home at 0 degrees
}

void TurntableDisplay::begin() {
  Turntable *turntable = _csClient.turntables->getFirst();
  if (turntable) {
    setPosition(turntable->getIndex()); // Set initial position
  }
}

void TurntableDisplay::update() {
  if (!_needsRedraw) // Only update if redraw flagged
    return;
  Turntable *turntable = _csClient.turntables->getFirst();
  if (!turntable) // If we don't have a turntable object, can't do anything
    return;
  bool isMoving = turntable->isMoving();
  unsigned long currentTime = millis();
  if (isMoving && (currentTime - _lastBlinkTime > _blinkDelay)) { // Blink at the defined rate
    _lastBlinkTime = currentTime;
    _blinkState = !_blinkState;
  } else if (!isMoving) { // Ensure when a movement has finished that we set state to be on
    _needsRedraw = false;
    _blinkState = true;
  }
  _drawTurntable(turntable);
  _drawBridge(turntable);
  _drawPositionName(turntable);
  _displaySprite.pushSprite(0, 0);
}

void TurntableDisplay::setNextPosition() {
  Turntable *turntable = _csClient.turntables->getFirst();
  if (!turntable) // No turntable object, don't try to do anything
    return;
  if (turntable->isMoving()) // If moving, don't allow other changes
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
  if (turntable->isMoving()) // If moving, don't allow other changes
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

void TurntableDisplay::setPosition(uint8_t position) {
  Turntable *turntable = _csClient.turntables->getFirst();
  if (!turntable)
    return;
  _bridgePosition = position;
  _needsRedraw = true;
}

uint8_t TurntableDisplay::getPosition() { return _bridgePosition; }

void TurntableDisplay::_drawTurntable(Turntable *turntable) {
  _displaySprite.fillSprite(_backgroundColour); // Clear screen
  uint16_t x = _displaySprite.width() / 2;      // Get X/Y for centre of screen for circle and positions
  uint16_t y = _displaySprite.height() / 2;
  uint16_t radius = min(x, y) - _pitOffset; // Radius of the pit wall subtracts _pitOffset
  float positionX = 0;
  float positionY = 0;
  float angle = 0;
  for (TurntableIndex *index = turntable->getFirstIndex(); index; index = index->getNextIndex()) {
    if (index->getId() == 0) { // First index will always be home, so safe to get its angle here
      _homeAngle = index->getAngle() / 10;
      angle = _homeAngle;
    } else {
      angle = _calculateAngle(index->getAngle() / 10); // All other positions are relative to home angle
    }
    _getCoordinates(x, y, &positionX, &positionY, radius + (_pitOffset / 2),
                    angle); // Calculate coordinates to plot each position indicator, draw these before the pit wall so
                            // it clears the centre
    if (index->getId() == 0) {
      _displaySprite.drawWideLine(x, y, positionX, positionY, 6.0f, _homeColour);
    } else {
      _displaySprite.drawWideLine(x, y, positionX, positionY, 6.0f, _positionColour);
    }
  }
  _displaySprite.fillSmoothCircle(x, y, radius, _pitColour, _backgroundColour);
  _displaySprite.fillSmoothCircle(x, y, radius - 3, _backgroundColour);
}

void TurntableDisplay::_drawBridge(Turntable *turntable) {
  float angle = 0;
  bool isMoving = turntable->isMoving();
  for (TurntableIndex *index = turntable->getFirstIndex(); index; index = index->getNextIndex()) {
    if (index->getId() == _bridgePosition) {
      if (_bridgePosition == 0) {
        angle = _homeAngle;
      } else {
        angle = _calculateAngle(index->getAngle() / 10);
      }
      break;
    }
  }
  float x = 0;
  float y = 0;
  uint16_t bridgeColour;
  uint16_t bridgeHomeEndColour;
  if (_blinkState) {
    if (isMoving || (_bridgePosition != turntable->getIndex())) {
      bridgeColour = _bridgeMovingColour;
    } else {
      bridgeColour = _bridgeColour;
    }
    bridgeHomeEndColour = _bridgePositionColour;
  } else {
    bridgeColour = _backgroundColour;
    bridgeHomeEndColour = _backgroundColour;
  }
  uint16_t halfBridgeLength = (min(_displaySprite.width(), _displaySprite.height()) / 2) - _pitOffset - 10;
  uint16_t homeHalfBridgeLength = halfBridgeLength - 15;
  _getCoordinates(_displaySprite.width() / 2, _displaySprite.height() / 2, &x, &y, homeHalfBridgeLength,
                  angle); // Get coordinates for home end of bridge starting from display centre
  _displaySprite.drawWideLine(_displaySprite.width() / 2, _displaySprite.height() / 2, x, y, 6.0f, bridgeColour);
  uint16_t homeX = x;
  uint16_t homeY = y;
  _getCoordinates(homeX, homeY, &x, &y, 15,
                  angle); // Get coordinates for the home end indicator starting from home end of the bridge
  _displaySprite.drawWideLine(homeX, homeY, x, y, 6.0f, bridgeHomeEndColour);
  angle += 180; // Add 180 degrees for other end of bridge
  _getCoordinates(_displaySprite.width() / 2, _displaySprite.height() / 2, &x, &y, halfBridgeLength,
                  angle); // Get coordinates for other end starting from display centre
  _displaySprite.drawWideLine(_displaySprite.width() / 2, _displaySprite.height() / 2, x, y, 6.0f, bridgeColour);
}

void TurntableDisplay::_drawPositionName(Turntable *turntable) {
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
}

// =========================================================================
// Get coordinates of end of a line, pivot at x,y, length r, angle a
// Taken from TFT_eSPI Anti-aliased_Clock demo
// =========================================================================
// Coordinates are returned to caller via the xp and yp pointers
void TurntableDisplay::_getCoordinates(uint16_t x, uint16_t y, float *xp, float *yp, uint16_t r, float a) {
  float sx1 = cos((a - 90) * _degreesToRadians);
  float sy1 = sin((a - 90) * _degreesToRadians);
  *xp = sx1 * r + x;
  *yp = sy1 * r + y;
}

float TurntableDisplay::_calculateAngle(float relativeAngle) {
  float angle = fmod((relativeAngle + _homeAngle), 360.0f);
  return angle;
}
