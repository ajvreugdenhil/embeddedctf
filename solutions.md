# Hints to get started with the CTF

There are six flags. Some are not as obvious as others.

## UART

the mcu has a shell in which a flag can be requested with the command "showuartflag.

connect with usb or a uart dongle, run `picocom /dev/ttyUSB0 -b 57600 --omap crcrlf`. Run `help` to get available commands.

## Undocumented UART command

With strings or by analyzing the flash image, the player can discover that there's a command that's not listed in help. Running this gets the player a flag.

## BOF

The shell has a buffer overflow vuln. At boot, a memory location is shown. Executing the function at that location gets the player a flag. (NOT VERIFIED)

## Blink

The led blinks the bits of a flag. A logic analyzer or computer vision can be used to extract the flag from the pattern. (NOT VERIFIED)

## Networking

With a command in the shell, the mcu tries to contact a remote server. This always fails. But the GET request can be sniffed. The flag is passed as a parameter.

## Strings

One flag can be easily extracted using `strings`. It is not shown anywhere during normal execution.
