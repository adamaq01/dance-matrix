# Dance Matrix

This a Teensy 4.1 firmware used to drive arbitrary sized LED matrices in a PIU/DDR/ITG dance pad.

Its main purpose is to replace the simple LEDs in an original pad with square LED matrices capable of displaying funny animations and effects.

## Features

- Supports up to 5 matrices of any size (up to 64x64 pixels) (TODO)
- Can be linked with another Dance Matrix for 2 pad setups (up to 10 matrices) (TODO)
- Supports "virtual" matrices representing the pad's metal frames to simplify animation creation (TODO)
- Loading animations from SD card (TODO)

## Requirements

- Hardware
  - A [Teensy 4.1](https://www.pjrc.com/store/teensy41.html) board
  - Up to 5 LED matrices (up to 64x64 pixels) and the same amount of [SmartMatrix shields](https://docs.pixelmatix.com/SmartMatrix/shield-t4.html)
  - A way of powering the LED matrices
- Software
  - [PlatformIO](https://platformio.org/) (for building the firmware)
  - TBD (There is no frontend yet)

## Building

- Install PlatformIO and the Teensy 4.1 platform (see [PlatformIO docs](https://docs.platformio.org/en/latest/core/installation.html))
- Clone this repository
- Run `git submodule update --init --recursive` to fetch the SmartMatrix library
- Copy the files inside `toolchain-fixes` to the `~/.platformio/packages/toolchain-gccarmnoneabi/arm-none-abi/lib` directory
- Run `pio run` in the project's root directory
- Firmware is located in `.pio/build/teensy41/firmware.hex`

## License

[MIT](LICENSE)