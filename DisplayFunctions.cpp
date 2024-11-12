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
#include "Version.h"
#include <SPI.h>
#include <TFT_eSPI.h>

TFT_eSPI display = TFT_eSPI();
TFT_eSprite displaySprite = TFT_eSprite(&display);
TurntableDisplay turntableDisplay =
    TurntableDisplay(&displaySprite, BACKGROUND_COLOUR, PIT_OFFSET, PIT_COLOUR, HOME_COLOUR, POSITION_COLOUR,
                     BRIDGE_COLOUR, BRIDGE_MOVING_COLOUR, BRIDGE_POSITION_COLOUR, POSITION_TEXT_COLOUR, BLINK_DELAY);
uint16_t statusX;
uint16_t statusY;

/*
Colour definitions and fonts for the DCC-EX logo
*/
uint16_t dccexDCCColour = 0x01C8;
uint16_t dccexEXColour = 0x03B6;
uint16_t dccexBackgroundColour = 0xFFFF;
const GFXfont *dccexFont = &FreeSansBold12pt7b;
const GFXfont *dccexSmallFont = &FreeMono9pt7b;
const GFXfont *dccexVersionFont = &FreeMonoBold9pt7b;

void setupDisplay() {
  display.init();
#if defined(GC9A01_BL)
  pinMode(GC9A01_BL, OUTPUT);
  digitalWrite(GC9A01_BL, HIGH);
#endif
  display.setRotation(GC9A01_ROTATION);
  displaySprite.setColorDepth(8); // Limit colour to 8 bit otherwise out of RAM
  displaySprite.createSprite(display.width(), display.height());
}

void displaySoftwareInfo() {
  display.setFreeFont(dccexFont);
  display.fillScreen(dccexBackgroundColour);
  uint8_t dccexFontHeight = dccexFont->yAdvance;
  uint8_t fontHeight = dccexSmallFont->yAdvance;
  uint16_t x = display.width() / 2;
  uint16_t y = (display.height() / 2) - (dccexFontHeight + (fontHeight * 3) / 2);
  display.setTextDatum(MC_DATUM);
  display.setTextSize(1);
  uint16_t dccWidth = display.textWidth("DCC-");
  uint16_t exWidth = display.textWidth("EX");
  display.setTextColor(dccexDCCColour, dccexBackgroundColour);
  display.drawString("DCC-", x - (exWidth / 2), y);
  display.setTextColor(dccexEXColour, dccexBackgroundColour);
  display.drawString("EX", x - (dccWidth / 2) + dccWidth, y);
  y += (fontHeight * 2);
  display.setFreeFont(dccexSmallFont);
  display.setTextColor(dccexDCCColour, dccexBackgroundColour);
  display.drawString("Turntable Controller", x, y);
  y += fontHeight;
  uint16_t versionTextWidth = display.textWidth("Version: ");
  display.setFreeFont(dccexVersionFont);
  uint16_t versionWidth = display.textWidth(VERSION);
  display.setFreeFont(dccexSmallFont);
  display.drawString("Version: ", x - (versionWidth / 2), y);
  display.setTextColor(dccexEXColour, dccexBackgroundColour);
  display.setFreeFont(dccexVersionFont);
  display.drawString(VERSION, x - (versionTextWidth / 2) + versionTextWidth, y);
  y += fontHeight;
  statusX = x;
  statusY = y;
}

void displayConnectingScreen() {
  displaySoftwareInfo();
  displayStatus("Connecting...");
}

void displayRetrievingInfo() {
  displaySoftwareInfo();
  displayStatus("Retrieve turntable...");
}

void createTurntableDisplay() {
  Turntable *turntable = nullptr;
  if (TURNTABLE_ID == 0) { // If no user ID has been specified, get first turntable
    turntable = csClient.turntables->getFirst();
  } else { // Otherwise get the specified turntable by ID
    turntable = csClient.turntables->getById(TURNTABLE_ID);
  }
  if (turntable) {
    turntableDisplay.begin(turntable);
  }
}

void updateDisplay() { turntableDisplay.update(); }

void displayConnectionError() {
  displaySoftwareInfo();
  displayStatus("Connect failed");
}

void displayObjectRetrievalError() {
  displaySoftwareInfo();
  displayStatus("Retrieval failed");
}

void displayStatus(const char *status) {
  display.setTextColor(dccexDCCColour, dccexBackgroundColour);
  display.setFreeFont(dccexSmallFont);
  display.drawString(status, statusX, statusY);
}
