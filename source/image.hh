#include <stdint.h>
#include <string.h>
#include <cstdio>
#include <bitset>
#include <iostream>

struct Image {
    uint8_t* data = NULL;
    size_t size = 0;
    int w, h, channels;

    Image(const char* filename);
    Image(int w, int h, int channels);
    Image(const Image& img);
    ~Image();

    bool read(const char* filename);
    bool write(const char* filename);
    void generate(int w, const char* mess, const char level);
    void positioning();
    void timing();
    void errorcorrection(const char level);
    void messengedata(const char* mess);
    size_t getlen(const char* mess);
};