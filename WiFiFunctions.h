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

#ifndef WIFIFUNCTIONS_H
#define WIFIFUNCTIONS_H

#include "Defines.h"
#include <Arduino.h>

#if (CLIENT_TYPE == WIFI_CLIENT)
#include <WiFi.h>

extern WiFiClient wifiClient;

/// @brief Connect to WiFi using the SSID and password defined in the user's myConfig.h
void connectWiFi();

/// @brief Connect to the CommandStation using the IP address and port in the user's myConfig.h
void connectCommandStation();

/// @brief Validates and converts an IP address from the preprocessor macro string to an IPAddress object
/// @param ipAddressString Preprocessor macro IP address string COMMANDSTATION_IP
/// @return IPAddress object
IPAddress convertIP(const char *ipAddressString);

#endif // CLIENT_TYPE

#endif // WIFIFUNCTIONS_H
