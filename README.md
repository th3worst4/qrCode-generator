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

### How to compile?

To compile this project you can use the [Makefile][], there will be some g++ commands. I recommend you first clear all directories by using `make clean-all`, it will delete any object, executable and image files for both bin and debug directories. So on you can use `make all` to create both debug and release executable. The files on debug folder accept gdb debugging.

OBS.: the [Makefile] was built to run at Windows machines using [PowerShell 7.x][]. You can install PowerShell on Linux or macOS with one of those is your platform, still I just recommend you to do some changes on the Makefile.

[Makefile]: Makefile
[PowerShell 7.x]: https://github.com/PowerShell/PowerShell

### How to use it?
My intention is you could pass an argument at execution on command prompt, like the following:

`.\main.exe samplestring`

Still, if you pass no argument, the program will ask one to be provided at the console. At this moment, this behavior is disabled for bebugging purposes, but you can enable it. 

Go to the [source/main.cpp], at line 17 you will see the following:

`out.generate(21, "'Twas brilling", 'L', 0b011)`;

change it to:

`out.generate(21, *(argv+1), 'L', 0b011)`

Now you will be able to pass any 20 or less characters string to be encoded.

### Where to find my QR Code?
There is two options:
1) If you have ran the relese project it will be at bin/final.png
2) If you have run the debug project it will be at debug/final.png

Either of this options, you will see an "out.png" file. This is an exact copy of the generated QR Code, but on 1:1 scale (21x21 px). Don't worry about it, you can delete this if you want.
 
## Be aware this is still an ongoing project!
As an ongoing project, the code lacks the Reed Solomon correction code. Then none decoder can detect and transmit the data yet. 

Reed Solomon Code is a very interesting and hard topic to study by your own (and that's what I'm doing), but if you'd like more info check this link [Reed-Solomon codes for coders][].

[Reed-Solomon codes for coders]: https://en.wikiversity.org/wiki/Reed–Solomon_codes_for_coders



### todo
* LEARN REED SOLOMON CODE
