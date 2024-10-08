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

#ifndef COMMANDSTATIONLISTENER_H
#define COMMANDSTATIONLISTENER_H

#include "Defines.h"
#include <Arduino.h>
#include <DCCEXProtocol.h>

class CSListener : public DCCEXProtocolDelegate {
public:
  /// @brief Displays the received server version in the console
  /// @param major Major version number
  /// @param minor Minor version number
  /// @param patch Patch version number
  void receivedServerVersion(int major, int minor, int patch);

  /// @brief Print the turntable list to the console
  void receivedTurntableList();

  /// @brief Print a turntable action to the console
  /// @param turntableId ID of the turntable associated with the move
  /// @param position Position number being moved to
  /// @param moving Boolean indicating if a move is in progress
  void receivedTurntableAction(int turntableId, int position, bool moving);
};

#endif // COMMANDSTATIONLISTENER_H
