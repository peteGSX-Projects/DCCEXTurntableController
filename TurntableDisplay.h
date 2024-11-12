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

#ifndef TURNTABLEDISPLAY_H
#define TURNTABLEDISPLAY_H

#include <Arduino.h>
#include <DCCEXProtocol.h>
#include <TFT_eSPI.h>

class TurntableDisplay {
public:
  /// @brief Constructor for the TurntableDisplay object, results in the basic turntable drawn on screen
  /// @param displaySprite Pointer to an existing TFT_eSprite object
  /// @param textColour 16 bit colour for the text
  /// @param backgroundColour 16 bit colour for the background
  /// @param bridgeColour 16 bit colour for the turntable bridge
  /// @param bridgeMovingColour 16 bit colour for the bridge when moving, or when user is selecting a new position
  /// @param bridgePositionColour 16 bit colour for the end of the bridge indicating the selected position
  /// @param positionTextColour 16 bit colour for the name of the selected position
  /// @param blinkDelay Delay in ms to blink position text and bridge when turntable is moving
  TurntableDisplay(TFT_eSprite *displaySprite, uint16_t backgroundColour, uint8_t pitOffset, uint16_t pitColour,
                   uint16_t homeColour, uint16_t positionColour, uint16_t bridgeColour, uint16_t bridgeMovingColour,
                   uint16_t bridgePositionColour, uint16_t positionTextColour, unsigned long blinkDelay);

  /// @brief Draws the initial turntable and bridge position, only to be called when lists have been received
  /// @param turntable Pointer to an existing DCCEXProtocol turntable object
  void begin(Turntable *turntable);

  /// @brief Get the DCCEXProtocol turntable object associated with this display
  /// @return Pointer to the turntable object
  Turntable *getTurntable();

  /// @brief Update the display - call this at least once per main loop iteration to respond to broadcasts and blink if
  /// moving
  void update();

  /// @brief Set the bridge to the next available position (clockwise), moves through home as position 0
  void setNextPosition();

  /// @brief Set the bridge to the previous available position (counter-clockwise), moves through home as position 0
  void setPreviousPosition();

  /// @brief Set the display's bridge position - call from a broadcast message to update the display
  /// @param position Position index
  void setPosition(uint8_t position);

  /// @brief Get the current user selected position index
  /// @return Position index
  uint8_t getPosition();

private:
  TFT_eSprite *_displaySprite;    // Pointer to an existing TFT_eSprite object
  Turntable *_turntable;          // Pointer to an existing DCC-EX protocol turntable object
  uint16_t _backgroundColour;     // 16 bit background colour
  uint8_t _pitOffset;             // Number of pixels to inset pit wall from edge of display
  uint16_t _pitColour;            // Colour of the pit wall
  uint16_t _homeColour;           // Colour of the home position indicator
  uint16_t _positionColour;       // Colour of position indicators
  uint8_t _bridgePosition;        // Current position of the bridge as selected by the user
  uint16_t _bridgeColour;         // 16 bit colour of the bridge
  uint16_t _bridgeMovingColour;   // 16 bit colour of the bridge when moving or when not aligned with turntable object
  uint16_t _bridgePositionColour; // 16 bit colour of the end of the bridge aligned with the position
  uint16_t _positionTextColour;   // Colour of the text for each position
  unsigned long _blinkDelay;      // Delay in ms for blinking when moving
  unsigned long _lastBlinkTime;   // Time of the last blink in ms
  bool _blinkState;               // Flag to manage if the current state for blinking is on or off
  bool _needsRedraw;              // Flag if the display needs redrawing
  const float _degreesToRadians = 0.0174532925; // Degrees to radians
  float _homeAngle;                             // Store the angle of the home position, all others are relative to this

  /// @brief Draws the basic turntable on screen
  void _drawTurntable();

  /// @brief Draw the currently selected bridge's position on screen
  void _drawBridge();

  /// @brief Draw the currently selected position's name on screen
  void _drawPositionName();

  /// @brief Get coordinates of end of a line, pivot at x,y, length r, angle a, *Taken from TFT_eSPI anti aliased clock
  /// demo*
  /// @param x Starting X point to calculate coordinates from
  /// @param y Starting Y point to calculate coordinates from
  /// @param xp Reference to the resultant X point variable
  /// @param yp Reference to the resultant Y point variable
  /// @param r Length of the desired object to be drawn (typically a line)
  /// @param a Angle it is to be drawn at
  void _getCoordinates(uint16_t x, uint16_t y, float *xp, float *yp, uint16_t r, float a);

  /// @brief Calculate the correct angle to draw a line on screen relative to the home position
  /// @param relativeAngle Relative angle of the position to be drawn
  /// @return The absolute angle to draw the line on screen
  float _calculateAngle(float relativeAngle);
};

#endif // TURNTABLEDISPLAY_H
