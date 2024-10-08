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
#include "Turntable.h"

void CSListener::receivedServerVersion(int major, int minor, int patch) {
  CONSOLE.print("EX-CommandStation version: ");
  CONSOLE.print(major);
  CONSOLE.print(".");
  CONSOLE.print(minor);
  CONSOLE.print(".");
  CONSOLE.println(patch);
}

void CSListener::receivedTurntableList() {
  CONSOLE.println("Turntable info received, create it");
  createTurntable();
}

void CSListener::receivedTurntableAction(int turntableId, int position, bool moving) {
  CONSOLE.print("Turntable action ID|position|moving");
  CONSOLE.print(turntableId);
  CONSOLE.print("|");
  CONSOLE.print(position);
  CONSOLE.print("|");
  CONSOLE.println(moving);
}
