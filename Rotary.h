/*
 * Rotary encoder library for Arduino.
 */

#ifndef rotary_h
#define rotary_h

#include <Arduino.h>
#include "Defines.h"

const byte DIR_CW = 0x10;
const byte DIR_CCW = 0x20;

class Rotary
{
  public:
    Rotary(char, char);
    // Process pin(s)
    unsigned char process();
  private:
    unsigned char state;
    unsigned char pin1;
    unsigned char pin2;
};

#endif
 
