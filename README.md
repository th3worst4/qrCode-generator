# qrCode-generator

### Simple QR Code generator.

My purpose with this project is be able to create any QR Code v1. A v1(or version 1) QR Code is made by 21 by 21 data chunks and can storage 20 or less UTF-8 characters. 

On this code, I've used bitwise encoding method. Some different encoding methods can be used to store more data, but any of them have it's own limitation. You can check more about it on the wikipedia page about [QR Code][].

[QR Code]: https://en.wikipedia.org/wiki/QR_code#

You can start navigate on the code by the [source/main.cpp][] file, by there you will be lead to the [source/image.cpp] file. It's on this file that most of the functions are defined.

[source/main.cpp]: source/main.cpp
[source/image.cpp]: source/image.cpp

This code uses the [stb_image][] library. You can check their project on GitHub!

[stb_image]: https://github.com/nothings/stb/tree/master

To compile this project you can use the [Makefile][], there will be some g++ commands. I recommend you first clear all directories by using `make clean-all`, it will delete any object, executable and image files for both bin and debug directories. So on you can use `make all` to create both debug and release executable. The files on debug folder accept gdb debugging.

OBS.: the [Makefile] was built to run at Windows machines using [PowerShell 7.x][]. You can install PowerShell on Linux or macOS with one of those is your platform, still I just recommend you to do some changes on the Makefile.

[Makefile]: Makefile
[PowerShell 7.x]: https://github.com/PowerShell/PowerShell
 
## Be aware this is still an ongoing project!

### todo
* LEARN REED SOLOMON CODE
