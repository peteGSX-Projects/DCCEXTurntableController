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

#ifndef COMMANDSTATIONCONNECTION_H
#define COMMANDSTATIONCONNECTION_H

#include <Arduino.h>
#include <DCCEXProtocol.h>

/// @brief Setup connection to EX-CommandStation
/// @param consoleStream Reference to the console stream object
/// @param csConnectionStream Reference to the CommandStation connection stream object
void setupCSConnection(Stream &consoleStream, Stream &csConnectionStream);

/// @brief Process CommandStation connection for broadcasts/responses
void processCSConnection();

#endif // COMMANDSTATIONCONNECTION_H