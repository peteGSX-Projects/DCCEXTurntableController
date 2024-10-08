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

#ifndef COMMANDSTATIONCLIENT_H
#define COMMANDSTATIONCLIENT_H

#include <Arduino.h>
#include <DCCEXProtocol.h>

/// @brief Setup EX-CommandStation client:
/// - associates the console and CommandStation connections with the client object
/// - sets up the listener for broadcasts/responses
/// @param consoleStream Reference to the console stream object
/// @param csConnectionStream Reference to the CommandStation connection stream object
void setupCSClient(Stream &consoleStream, Stream &csConnectionStream);

/// @brief Process CommandStation client to listen for broadcasts/responses:
/// - requests lists from CommandStation if not received
/// - retries up to 5 times
/// - 2 second delay between retries
void processCSClient();

#endif // COMMANDSTATIONCLIENT_H