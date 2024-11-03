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
#include "CommandStationListener.h"

const unsigned long retrieveTurntableRetryDelay = 2000; // ms between retrying requesting turntable info
unsigned long lastRetrieveTurntableRetry = 0;           // time in ms of last retry
uint8_t retrieveTurntableRetries = 5;                   // number of times left to retry requesting turntable info
bool retrievalErrorDisplayed = false;                   // flag an error has already been displayed

DCCEXProtocol csClient;
CSListener csListener;

void setupCSClient(Stream &consoleStream, Stream &csConnectionStream) {
  csClient.setLogStream(&consoleStream);
  csClient.setDelegate(&csListener);
  csClient.enableHeartbeat();
  csClient.connect(&csConnectionStream);
}

void processCSClient() {
  csClient.check();
  if (!csClient.receivedLists()) {
    unsigned long currentMillis = millis();
    if (currentMillis - lastRetrieveTurntableRetry > retrieveTurntableRetryDelay && retrieveTurntableRetries > 0) {
      lastRetrieveTurntableRetry = currentMillis;
      retrieveTurntableRetries--;
      csClient.getLists(false, false, false, true);
      CONSOLE.println("Requesting turntable info");
    } else if (!retrievalErrorDisplayed && retrieveTurntableRetries == 0) {
      retrievalErrorDisplayed = true;
      CONSOLE.println("Turntable info not received within the retry period");
    }
  }
}
