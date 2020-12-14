# ECEM202A Final Project
## Project Topic - Time Synchronization over Bluetooth Low Energy
## Team

Milin Patel

## Building Software

Required Software:
1. Python >= 3.8.5
2. scons
3. arm-none-eabi toolset 9.2.1
4. nRF5 SDK 17.0.2 (in the same directory as time_sync folder)

Run 'scons' in the time_sync folder to build the hex file. Hex files will be placed in 'time_sync/build/bin'.

## Hardware Required

1. 2+x nRF52840 Dongle (https://www.nordicsemi.com/Software-and-tools/Development-Kits/nRF52840-Dongle)
2. Logic Analyzer and wires to probe GPIO
3. Smartphone with Bluetooth capabilities

## Running

1. Download s140nrf52 7.2.0 and flash on the S140(ID 0x100) SoftDevice hex file using the nRF Programmer from nRF Connect.
2. Flash on the time_sync.hex file built from scons.
3. Connect to one of the dongles using a smartphone and Bluetooth app (like nRF Connect for iOS/Android).
4. Send a value of 0x1 to set the dongle as a master and start sending time synchronization packets.
5. GPIO P0.24 toggles on timer period completion. Master dongle will also toggle P0.22 to indicate start of SYNC.
6. Monitor GPIO P0.24 on all dongles as the edges will be synchronized.
