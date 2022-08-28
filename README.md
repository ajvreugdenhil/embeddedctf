# embeddedctf

ECTF is a small hardware-based CTF designed for CTF players who are unfamiliar with hardware challenges. It encourages the player to research the following topics:

- Embedded communication protocols
- Reverse engineering firmware
- Using a logic analyzer

## Setting up

The recommended way to set up the CTF is to flash the bin **with flags** from the latest release using esptool.

Alternatively, you can download or clone the repository and flash from PlatformIO.

## Playing

Flags are in the format of ECTF{}.

The .bin file you on the MCU (nodemcuv2_flags_firmware.bin) may not be inspected (it could be extracted using esptool.) Only the 'flagless' version of the firmware can be investigated (nodemcuv2_flagless_firmware.bin). This has the actual flags replaced with placeholders. This way, you cannot use `strings` to get all the flags in one shot.

## Scope

As specified above, only one version of the binaries can be analyzed with software. After analyzing that one, you can attack the version on the MCU in the intended way.

Try analyzing the following:

- GPIO
- Networking
- nodemcuv2_flagless_firmware.bin

## Hint

You may need `--omap crcrlf`
