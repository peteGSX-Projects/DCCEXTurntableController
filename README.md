# EXTTController

This is a controller for DCC-EX EX-Turntable utilising a rotary encoder and GC9A01 based round LCD to display turntable operations.

This controller requires a serial connection to a DCC-EX EX-CommandStation as it operates as a throttle client utilising the turntable object to obtain turntable information and operate it.

The round display responds to turntable broadcasts/responses to update the position and status of the turntable.

## Pins and connections

Serial RX - PA10
Serial TX - PA9
Rotary encoder button - PB15
Rotary encoder DT - PB14
Rotary encoder CLK - PB13
GC9A01 DIN - PA7
GC9A01 CLK - PA5
GC9A01 CS - PA4
GC9A01 DC - PA3
GC9A01 RST - PA2
GC9A01 BL - PA1
