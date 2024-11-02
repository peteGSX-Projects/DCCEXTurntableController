# DCC-EX Turntable Controller

This is a controller for DCC-EX turntables, operating as a native DCC-EX protocol client to utilise a turntable object and allow a user to operate it.

Turntable operations are displayed on a round LCD.

## Hardware required

This software has been written explicitly for an STM32F411CEU6 Blackpill microprocessor, with a connected rotary encoder and GC9A01 based LCD.

It also requires a serial connection to a DCC-EX CommandStation.

A future may implement support for an ESP32 WROOM microprocessor to provide a WiFi client connection to the DCC-EX CommandStation.

### Pins and connections

The below pins are used on the Blackpill to connect to the CommandStation's serial port, rotary encoder, and GC9A01 LCD.

Remember to cross Rx/Tx so that the Blackpill Rx connects to the CommandStation's Tx, and vice versa. Also be sure to take into account if the CommandStation uses 3.3V or 5V logic, as the Blackpill is a 3.3V uC.

- Serial Rx - PA10
- Serial Tx - PA9
- Rotary encoder button - PB15
- Rotary encoder DT - PB14
- Rotary encoder CLK - PB13
- GC9A01 DIN - PA7
- GC9A01 CLK - PA5
- GC9A01 CS - PA4
- GC9A01 DC - PA3
- GC9A01 RST - PA2
- GC9A01 BL - PA1

## Installation and configuration

This repository is setup to enable PlatformIO to be used with VSCode and will automatically install the required libraries:

- DCC-EX/DCCEXProtocol
- bodmer/TFT_eSPI
- avandalen/Switch

If you prefer, you can also use the Arduino IDE, which means you will need to:

- Install the above libraries
- Configure TFT_eSPI manually according to the [library's documentation](https://github.com/Bodmer/TFT_eSPI)

If you wish to customise the pins, colours, and font in use, you can copy the included "myConfig.example.h" to "myConfig.h" and edit it to suit, instructions are in the file.
