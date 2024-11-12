# DCC-EX Turntable Controller

This is a controller for DCC-EX turntables, operating as a native DCC-EX protocol client to utilise a turntable object and allow a user to operate it.

Turntable operations are displayed on a round LCD.

This README is very brief, and for the full documentation refer to [Pete's Pages](https://petegsx-projects.github.io/dcc-ex-turntable-controller/index.html).

## Hardware required

This software has been written for either an STM32F411CEU6 Blackpill or Espressif ESP32 Dev board, with a connected rotary encoder and GC9A01 based LCD.

It also requires a serial connection to a DCC-EX CommandStation (either Blackpill or ESP32), or a WiFi connection (ESP32 only).

### Pins and connections

The below pins are used to connect to the CommandStation's serial port, rotary encoder, and GC9A01 LCD.

Remember to cross Rx/Tx so that the Blackpill/ESP32 Rx connects to the CommandStation's Tx, and vice versa. Also be sure to connect a common ground, and take into account if the CommandStation uses 3.3V or 5V logic, as both the Blackpill and ESP32 are 3.3V uCs.

| Connection | Blackpill pin | ESP32 pin |
|----------- |---------------|-----------|
| Serial Rx | PA10 | 16 |
| Serial Tx | PA9 | 17 |
| Rotary encoder button | PB15 | 25
| Rotary encoder DT | PB14 | 26
| Rotary encoder CLK | PB13 | 27
| GC9A01 DIN | PA7 | 19
| GC9A01 CLK | PA5 | 18
| GC9A01 CS | PA4 | 15
| GC9A01 DC | PA3 | 2
| GC9A01 RST | PA2 | 4
| GC9A01 BL | PA1 | 21

## Installation and configuration

This repository is setup to enable PlatformIO to be used with VSCode and will automatically install the required libraries:

- DCC-EX/DCCEXProtocol
- bodmer/TFT_eSPI
- avandalen/Switch

If you prefer, you can also use the Arduino IDE, which means you will need to:

- Install board support for both STM32 and Espressif boards
- Install the above libraries
- Configure TFT_eSPI manually according to the [library's documentation](https://github.com/Bodmer/TFT_eSPI)

If you wish to customise the pins, colours, and font in use, you can copy the included "myConfig.example.h" to "myConfig.h" and edit it to suit. Instructions are in the file.
