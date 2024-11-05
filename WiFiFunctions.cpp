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

void connectWiFi() {
  CONSOLE.print("Connect to WiFi SSID|password: ");
  CONSOLE.print(WIFI_SSID);
  CONSOLE.print("|");
  CONSOLE.println(WIFI_PASSWORD);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }
  CONSOLE.print("Connected to WiFi with IP ");
  CONSOLE.println(WiFi.localIP());
}

void connectCommandStation() {
  CONSOLE.print("Connect to CommandStation IP|port: ");
  CONSOLE.print(COMMANDSTATION_IP);
  CONSOLE.print("|");
  CONSOLE.println(COMMANDSTATION_PORT);
  IPAddress commandStationIP = convertIP(COMMANDSTATION_IP);
  if (!wifiClient.connect(commandStationIP, COMMANDSTATION_PORT)) {
    CONSOLE.println("Connection to CommandStation failed");
    displayConnectionError();
    while (1) {
      delay(1000);
    }
  }
  CONSOLE.println("Connected to CommandStation");
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
