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

/*
 *  This is a controller for a DCC-EX EX-Turntable, connecting via a serial interface
 *  to a DCC-EX EX-CommandStation.
 */

/*
Include the required libraries
*/
#include "CommandStationClient.h"
#include "Defines.h"
#include "DisplayFunctions.h"
#include "InputFunctions.h"
#include "Version.h"
#include <Arduino.h>

#if (CLIENT_TYPE == WIFI_CLIENT)
#include "WiFiFunctions.h"
#endif // CLIENT_TYPE

/// @brief Initial setup
void setup() {
  CONSOLE.begin(115200);
  setupDisplay();
  displaySoftwareInfo();
  delay(2000); // Display the startup screen for 2 secs to ensure CS is up first
  CONSOLE.print("EX-Turntable Controller ");
  CONSOLE.println(VERSION);
}

/// @brief Main loop
void loop() {
  bool connectionState = true; // Default to true for serial connection, WiFi overrides if not
#if (CLIENT_TYPE == WIFI_CLIENT)
  connectionState = connectWiFi(); // Make sure WiFi connection is alive
  if (connectionState) {
    connectionState = connectCommandStation(); // IF WiFi alive, make sure CS connection is alive
  }
#endif // CLIENT_TYPE
  if (connectionState) { // Only process clients if connection is true
    connectCSClient();   // Make sure connection to CS is alive
    processCSClient();   // Ensure objects are retrieved and broadcasts are received
  }
  updateDisplay();        // Ensure display shows current state
  processEncoderButton(); // Process button presses
  processEncoder();       // Process encoder rotations
}
