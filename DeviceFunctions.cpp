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

#include "DeviceFunctions.h"

#if defined(ARDUINO_ARCH_ESP32)
#include <esp_system.h>
#endif // ARCH ESP32

void resetDevice() {
#if defined(ARDUINO_ARCH_STM32)
  __disable_irq();
  NVIC_SystemReset();
  while (true) {
  };
#elif defined(ARDUINO_ARCH_ESP32)
  ESP.restart();
#endif
}