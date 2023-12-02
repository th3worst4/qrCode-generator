# qrCode-generator

## Simple QR Code generator

My purpose with this project is be able to create any QR Code v1. A v1(or version 1) QR Code is made by 21 by 21 data modules and can storage 20 or less UTF-8 characters.

On this code, I've used bitwise encoding method. Some different encoding methods can be used to store more data, but any of them have it's own limitation. You can check more about it on the wikipedia page about [QR Code][].

[QR Code]: https://en.wikipedia.org/wiki/QR_code#

You can start navigate on the code by the [source/main.cpp][] file, by there you will be lead to the [source/image.cpp] file. It's on this file that most of the functions are defined.

[source/main.cpp]: source/main.cpp
[source/image.cpp]: source/image.cpp

This code uses the [stb_image][] library. You can check their project on GitHub!

[stb_image]: https://github.com/nothings/stb/tree/master

## How to compile?

To compile this project you can use the [Makefile][], there will be some g++ commands. I recommend you first clear all directories by using `make clean-all`, it will delete any object, executable and image files for both bin and debug directories. So on you can use `make all` to create both debug and release executable. The files on debug folder accept gdb debugging.

OBS.: the [Makefile] was built to run at Windows machines using [PowerShell 7.x][]. You can install PowerShell on Linux or macOS if one of those is your platform, still I just recommend you to do some changes on the Makefile.

[Makefile]: Makefile
[PowerShell 7.x]: https://github.com/PowerShell/PowerShell

## How to use it?

My intention is you could pass an argument at execution on command prompt, like the following:

`.\main.exe samplestring`

Still, if you pass no argument, the program will ask one to be provided at the console. At this moment, none of those options have influence on the final image, I'm using a fixed string to debug the code: 'Twas brilling'.

I dont know whats this means but it's the encoded message on Wikipedia's QR Code v1 example. Using this same string helps me to know if the result is right or not.

Still, you can enable the user's input feature. Go to the [source/main.cpp], at line 26 you will see the following:

`out.generate(21, "'Twas brilling", 0b011);`

change it to:

`out.generate(21, *(argv+1), 0b011);`

Now you will be able to pass any 20 or less characters string to be encoded. When the project is finished I will implement it as a standard behavior.

## Where to find my QR Code?

There is two options:

1) If you have ran the relese project it will be at bin/final.png
2) If you have run the debug project it will be at debug/final.png

## Be aware this is still an ongoing project

As an ongoing project, the code lacks the Reed Solomon correction code. Then none decoder can detect and transmit the data yet.

Reed Solomon Code is a very interesting and hard topic to study by your own (and that's what I'm doing), but if you'd like more info check this link [Reed-Solomon codes for coders][].

[Reed-Solomon codes for coders]: https://en.wikiversity.org/wiki/Reed–Solomon_codes_for_coders

## Some research sources

QR code generation, elements and features:

* [Wikipedia: QR Code][]
* [YouTube: The Math behind QR code, what happens inside there?][]
* [YouTube: How to Decode a QR Code by Hand][]
* [YouTube: How QR Codes Are Built][]

Reed Solomon code:

* [Wikiversity: Reed-Solomon codes for coders][]
* [YouTube: But what are Hamming codes? The origin of error correction][]
* [YouTube: Reed Solomon Codes: RISC Zero Study Club][]
* [Chat Open AI: QR Code: RS Explanation][]
* [QR Code Log Antilog Table for Galois Field 256][]

[Wikipedia: QR Code]: https://en.wikipedia.org/wiki/QR_code#
[YouTube: The Math behind QR code, what happens inside there?]: https://www.youtube.com/watch?v=Rc3ul6RRANU&
[YouTube: How to Decode a QR Code by Hand]: https://youtu.be/KA8hDldvfv0?si=ZHavlQTsIpW7EErZ
[YouTube: How QR Codes Are Built]: https://www.youtube.com/watch?v=142TGhaTMtI

[Wikiversity: Reed-Solomon codes for coders]: https://en.wikiversity.org/wiki/Reed–Solomon_codes_for_coders
[YouTube: But what are Hamming codes? The origin of error correction]: https://youtu.be/X8jsijhllIA?si=qCxaXryVOfoCisoy
[YouTube: Reed Solomon Codes: RISC Zero Study Club]: https://youtu.be/Yu9DHhdSqQo?si=oY8aAA648QZU0Nhe
[Chat Open AI: QR Code: RS Explanation]: https://chat.openai.com/share/4b56aa10-0122-48a4-a688-4e721591f160
[QR Code Log Antilog Table for Galois Field 256]: https://www.thonky.com/qr-code-tutorial/log-antilog-table

### todo

* LEARN REED SOLOMON CODE -> stopped at multiplications and logarithms
