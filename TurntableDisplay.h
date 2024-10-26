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

/// @brief Reusable struct to make returning coordinates from methods easier
struct Coordinates {
  uint16_t x;
  uint16_t y;
};

class TurntableDisplay {
public:
  /// @brief Constructor for the TurntableDisplay object, results in the basic turntable drawn on screen
  /// @param displaySprite Reference to an existing TFT_eSprite object
  /// @param csClient Reference to an existing DCCEXProtocol client object
  /// @param textColour 16 bit colour for the text
  /// @param backgroundColour 16 bit colour for the background
  /// @param bridgeColour 16 bit colour for the turntable bridge
  /// @param bridgePositionColour 16 bit colour for the end of the bridge indicating the selected position
  TurntableDisplay(TFT_eSprite &displaySprite, DCCEXProtocol &csClient, uint16_t backgroundColour, uint8_t pitOffset,
                   uint16_t pitColour, uint16_t homeColour, uint16_t positionColour, uint16_t bridgeColour,
                   uint16_t bridgePositionColour);

  /// @brief Draws the initial turntable and bridge position, only to be called when lists have been received
  void begin();

  /// @brief Update the display - call this at least once per main loop iteration to respond to broadcasts and blink if
  /// moving
  /// @param updateTime Current time in ms
  void update(unsigned long updateTime);

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
  TFT_eSprite &_displaySprite;            // Reference to an existing TFT_eSprite object
  DCCEXProtocol &_csClient;               // Pointer to an existing DCC-EX protocol turntable object
  uint16_t _backgroundColour;             // 16 bit background colour
  uint8_t _pitOffset;                     // Number of pixels to inset pit wall from edge of display
  uint16_t _pitColour;                    // Colour of the pit wall
  uint16_t _homeColour;                   // Colour of the home position indicator
  uint16_t _positionColour;               // Colour of position indicators
  uint8_t _bridgePosition;                // Current position of the bridge as selected by the user
  uint16_t _bridgeColour;                 // 16 bit colour of the bridge
  uint16_t _bridgePositionColour;         // 16 bit colour of the end of the bridge aligned with the position
  uint8_t _fontWidth;                     // Used to determine text positioning later
  uint8_t _fontHeight;                    // Used to determine text positioning later
  static const unsigned long _blinkDelay; // Delay in ms for blinking when moving
  unsigned long _lastBlink;               // Last time in ms a blink occurred

  /// @brief Draw the currently selected position's name on screen
  void _drawPositionName(uint8_t position);

  /// @brief Draws the basic turntable on screen
  void _drawTurntable();

  /// @brief Determines the X/Y coordinates to display the provided text in the centre of the display
  /// @param text Char array of text to get coordinates for
  Coordinates _getTextPosition(const char *text);
};

#endif // TURNTABLEDISPLAY_H
