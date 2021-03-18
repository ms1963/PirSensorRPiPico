# PirSensorRPiPico

This is a sample C/C++ project for Raspberry Pi Pico.
It is intended to illustrate the usage of the Raspberry Pi Pico Generator, Picoprobe incl. OpenOCD, and VS Code.
Prerequisites: Installation of Pico-SDK and setting of PICO_SDK_PATH, cmake, make or similar generator, gcc-arm-eabi-none-toolchain.
The simple C example itself uses a PIR motion sensor to detect movement. An IRQ handler is registered to monitor a falling or rising edge on the pin where the sensor is connected to the Pico. On a rising edge (movement) an LED is turned on, while the LED is turned off on a falling edge (movement stopped).
