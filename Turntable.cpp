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
#include "Turntable.h"

void createTurntable() {
  for (auto *turntable = csClient.turntables->getFirst(); turntable; turntable = turntable->getNext()) {
    CONSOLE.print("Create turntable ID ");
    CONSOLE.print(turntable->getId());
    CONSOLE.print(" called ");
    CONSOLE.println(turntable->getName());
    CONSOLE.println("Positions:");
    for (auto *position = turntable->getFirstIndex(); position; position = position->getNextIndex()) {
      CONSOLE.print(position->getId());
      CONSOLE.print(" at angle ");
      CONSOLE.print(position->getAngle());
      CONSOLE.print(" called ");
      CONSOLE.println(position->getName());
    }
  }
}