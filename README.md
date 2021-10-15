# embeddedctf

ECTF is a small hardware-based CTF designed for CTF players who are unfamiliar with hardware challenges. It encourages the player to research topics like embedded communication protools, basic reverse engineering, and the use of a logic analyzer.

## Setting up

The recommended way to set the system up is as follows.

1. Flash the `embeddedctf` PIO project to a nodemcu with the `FLAGLESS` flag enabled.
2. Pull the image from the board with `esptool.py read_flash 0x0 0x400000 ectf.bin`
3. Flash the `embeddedctf` PIO project to a nodemcu with the `FLAGLESS` flag disabled.
