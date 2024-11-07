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

#include "WiFiFunctions.h"
#if (CLIENT_TYPE == WIFI_CLIENT)
#include "DisplayFunctions.h"

WiFiClient wifiClient;

const unsigned long wifiRetryDelay = 1000;     // ms between WiFi connection attempts
unsigned long lastWiFiRetry = 0;               // time in ms of last attempt to connect to WiFi
uint8_t wifiRetries = 5;                       // number of retries for WiFi connection
const unsigned long csClientRetryDelay = 1000; // ms between client connection attempts
unsigned long lastClientConnectionRetry = 0;   // time is ms of last attempt to connect to CS
uint8_t csClientRetries = 5;                   // number of retries for CommandStation connection
bool wifiStarted = false;                      // flag that WiFi.begin() has been called

bool connectWiFi() {
  if (!wifiStarted) {
    CONSOLE.print("Connect to WiFi SSID|password: ");
    CONSOLE.print(WIFI_SSID);
    CONSOLE.print("|");
    CONSOLE.println(WIFI_PASSWORD);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    wifiStarted = true;
  }
  if (WiFi.status() == WL_CONNECTED) {
    return true;
  } else if (WiFi.status() != WL_CONNECTED && wifiRetries > 0 && (millis() - lastWiFiRetry) > lastWiFiRetry) {
    wifiRetries--;
    lastWiFiRetry = millis();
    return false;
  } else if (WiFi.status() != WL_CONNECTED && wifiRetries == 0) {
    displayConnectionError();
    return false;
  }
  return false;
}

bool connectCommandStation() {
  if (wifiClient.connected()) {
    return true;
  } else if (csClientRetries > 0 && (millis() - lastClientConnectionRetry) > csClientRetryDelay) {
    csClientRetries--;
    lastClientConnectionRetry = millis();
    CONSOLE.print("Connect to CommandStation IP|port: ");
    CONSOLE.print(COMMANDSTATION_IP);
    CONSOLE.print("|");
    CONSOLE.println(COMMANDSTATION_PORT);
    IPAddress commandStationIP = convertIP(COMMANDSTATION_IP);
    wifiClient.connect(commandStationIP, COMMANDSTATION_PORT);
    return false;
  } else if (csClientRetries == 0) {
    displayConnectionError();
    return false;
  }
  return false;
}

IPAddress convertIP(const char *ipAddressString) {
  int first;
  int second;
  int third;
  int fourth;
  if (sscanf(ipAddressString, "%d.%d.%d.%d", &first, &second, &third, &fourth) == 4) {
    if ((first >= 0 && first <= 255) && (second >= 0 && second <= 255) && (third >= 0 && third <= 255) &&
        (fourth >= 0 && fourth <= 255)) {
      return IPAddress(first, second, third, fourth);
    } else {
      CONSOLE.println("IP address is out of range");
    }
  } else {
    CONSOLE.println("Invalid IP address format");
  }
  return IPAddress(0, 0, 0, 0);
}

#endif // CLIENT_TYPE
