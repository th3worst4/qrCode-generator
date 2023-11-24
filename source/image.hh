/*
    this header file contais all functions declarations
    and includes some c or cpp standard libraries
    major of functions names are self explained,
    still you can find more details about
    each one on the image.cpp file
*/

#include <stdint.h>
#include <string.h>
#include <bitset>
#include <iostream>
#include <iomanip>
#include <cmath>

struct Image {
    uint8_t* data = NULL;
    size_t size = 0;
    int w, h, channels;

    Image(int w, int h, int channels);
    Image(const Image& img);

    bool write(const char* filename);
    void generate(int w, const char* mess, const int mask);
    void positioning();
    void timing();
    void errorcorrection(const size_t len);
    const size_t messengedata(const char* mess);
    size_t getlen(const char* mess);
    void writedata(const std::string encmes, const size_t len);
    void masking(const int mask);
    void resize(const int factor);
};