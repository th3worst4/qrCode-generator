#include <stdint.h>
#include <string.h>
#include <cstdio>

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
    void fillpixel(bool color, int step);
};