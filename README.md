# ECEM202A Final Project
## Project Topic - Time Synchronization over Bluetooth Low Energy
## Team

Milin Patel

## Building

Required Software:
1. Python >= 3.8.5
2. scons
3. arm-none-eabi toolset 9.2.1
4. nRF5 SDK 17.0.2 (in the same directory as ble_app_blinky folder)

Run 'scons' in the ble_app_blinky folder to build the hex file. Hex files will be placed in 'ble_app_blinky/build/bin'.

## Running

1. Use the nRF Programmer from nRF Connect to flash on the hex file.
2. Download s140nrf52 7.2.0 and flash on the S140(ID 0x100) SoftDevice hex file.

## Hardware Required

1. 2+x nRF52840 Dongle (https://www.nordicsemi.com/Software-and-tools/Development-Kits/nRF52840-Dongle)
2. Logic Analyzer and wires to probe GPIO.
