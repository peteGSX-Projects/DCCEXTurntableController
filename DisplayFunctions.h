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

#ifndef DISPLAYFUNCTIONS_H
#define DISPLAYFUNCTIONS_H

#include "TurntableDisplay.h"

extern TurntableDisplay turntableDisplay;

/// @brief Setup display object
void setupDisplay();

/// @brief Display DCC-EX logo and software version
void displaySoftwareInfo();

/// @brief Initial screen display
void displayStartupScreen();

/// @brief Create the turntable display when info is received
void createTurntableDisplay();

/// @brief Placeholder to keep the display up to date
void updateDisplay();

/// @brief If a connection to the CommandStation cannot be made, display error
void displayConnectionError();

/// @brief If retrieving the turntable object fails, display error
void displayObjectRetrievalError();

/// @brief Display the provided status text
/// @param status Char array of status text
void displayStatus(const char *status);

#endif // DISPLAYFUNCTIONS_H
