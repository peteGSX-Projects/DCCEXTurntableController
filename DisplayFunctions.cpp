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
#include "Defines.h"
#include "DisplayFunctions.h"
#include "TurntableDisplay.h"
#include "Version.h"
#include <SPI.h>
#include <TFT_eSPI.h>

TFT_eSPI display = TFT_eSPI();
TurntableDisplay turntableDisplay =
    TurntableDisplay(display, csClient, BACKGROUND_COLOUR, PIT_OFFSET, PIT_COLOUR, HOME_COLOUR, POSITION_COLOUR,
                     BRIDGE_COLOUR, BRIDGE_POSITION_COLOUR);

void setupDisplay() {
  display.init();
#if defined(GC9A01_BL)
  pinMode(GC9A01_BL, OUTPUT);
  digitalWrite(GC9A01_BL, HIGH);
#endif
  const GFXfont *gfxFont = TEXT_FONT;
  display.setRotation(GC9A01_ROTATION);
  display.fillScreen(BACKGROUND_COLOUR);
  display.setTextSize(1);
  display.setFreeFont(gfxFont);
  display.setTextColor(TEXT_COLOUR);
  uint8_t fontHeight = gfxFont->yAdvance;
  uint8_t fontWidth = display.textWidth("A");
  uint16_t x = (display.width() / 2) - (fontWidth * 20 / 2);
  uint16_t y = (display.height() / 2) - (fontHeight * 4 / 2);
  display.setCursor(x, y);
  display.print("DCC-EX");
  display.setCursor(x, y+= fontHeight);
  display.print("Turntable Controller");
  display.setCursor(x, y += fontHeight);
  display.print("Version: ");
  display.print(VERSION);
  display.setCursor(x, y += fontHeight);
  display.print("Waiting for info...");
}

void createTurntableDisplay() { turntableDisplay.begin(); }

void updateDisplay() { turntableDisplay.drawBridge(); }
