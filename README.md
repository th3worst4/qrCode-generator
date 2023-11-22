## qrCode-generator

Simple QR Code generator.

My purpose with this project is be able to create any QR Code v1. A v1(or version 1) QR Code is made by 21 by 21 data chunks and can storage 20 or less UTF-8 characters. 

On this code, I've used bitwise encoding method. Some different encoding methods can be used to store more data, but any of them have it's own limitation. You can check more about it on the wikipedia page about [QR Code][].

[QR Code]: https://en.wikipedia.org/wiki/QR_code#

You can start navigate on the code by the [source/main.cpp][] file, by there you will be lead to the [source/image.cpp] file. It's on this file that most of the functions are defined.

[source/main.cpp]: source/main.cpp
[source/image.cpp]: source/image.cpp

This code uses the [stb_image][] library. You can check their project on GitHub!

[stb_image]: https://github.com/nothings/stb/tree/master
 
Be aware this is still an ongoing project!

## todo
* LEARN REED SOLOMON CODE
