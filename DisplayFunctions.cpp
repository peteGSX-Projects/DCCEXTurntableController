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
TFT_eSprite displaySprite = TFT_eSprite(&display);
TurntableDisplay turntableDisplay =
    TurntableDisplay(displaySprite, csClient, BACKGROUND_COLOUR, PIT_OFFSET, PIT_COLOUR, HOME_COLOUR, POSITION_COLOUR,
                     BRIDGE_COLOUR, BRIDGE_POSITION_COLOUR);

void setupDisplay() {
  display.init();
#if defined(GC9A01_BL)
  pinMode(GC9A01_BL, OUTPUT);
  digitalWrite(GC9A01_BL, HIGH);
#endif
  const GFXfont *dccexFont = DCCEX_FONT;
  const GFXfont *textFont = TEXT_FONT;
  display.setRotation(GC9A01_ROTATION);
  displaySprite.createSprite(display.width(), display.height());
  display.setFreeFont(dccexFont);
  display.fillScreen(DCCEX_BACKGROUND);
  uint8_t dccexFontHeight = dccexFont->yAdvance;
  uint8_t fontHeight = textFont->yAdvance;
  uint16_t x = display.width() / 2;
  uint16_t y = (display.height() / 2) - (dccexFontHeight + (fontHeight * 3) / 2);
  display.setTextDatum(MC_DATUM);
  display.setTextSize(1);
  uint16_t dccWidth = display.textWidth("DCC-");
  uint16_t exWidth = display.textWidth("EX");
  display.setTextColor(DCCEX_DCC, DCCEX_BACKGROUND);
  display.drawString("DCC-", x - (exWidth / 2), y);
  display.setTextColor(DCCEX_EX, DCCEX_BACKGROUND);
  display.drawString("EX", x - (dccWidth / 2) + dccWidth, y);
  y += (fontHeight * 2);
  display.setFreeFont(textFont);
  display.setTextColor(DCCEX_DCC, DCCEX_BACKGROUND);
  display.drawString("Turntable Controller", x, y);
  y += fontHeight;
  uint16_t versionTextWidth = display.textWidth("Version: ");
  uint16_t versionWidth = display.textWidth(VERSION);
  display.drawString("Version: ", x - (versionWidth /2), y);
  display.setTextColor(DCCEX_EX, DCCEX_BACKGROUND);
  display.drawString(VERSION, x - (versionTextWidth /2) + versionTextWidth, y);
  y += fontHeight;
  display.setTextColor(DCCEX_DCC, DCCEX_BACKGROUND);
  display.drawString("Waiting...", x, y);
}

void createTurntableDisplay() { turntableDisplay.begin(); }

void updateDisplay() {
  unsigned long currentTime = millis();
  turntableDisplay.update(currentTime);
}
