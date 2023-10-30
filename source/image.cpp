#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "image.hh"
#include "stb_image.hh"
#include "stb_image_write.hh"

Image::Image(int w, int h, int channels) : w(w), h(h), channels(channels) {
    size = w*h*channels;
    data = new uint8_t[size];
    memset(data, 255, size);
}
Image::Image(const Image& img) : Image(img.w, img.h, img.channels){
    memcpy(data, img.data, img.size);
}
Image::~Image(){
    stbi_image_free(data);
}
bool Image::write(const char* filename){
    int sucess = stbi_write_png(filename, w, h, channels, data, w*channels);
    return sucess;
}
void Image::fillpixel(bool color, int step){
    if (color) {
        memset(data+step, 0, 1);
    }
    else {
        memset(data+step, 255, 1);
    }
}
void Image::positioning(){
    memset(data, 0, 7);
    //memset(data, 0, 1);
}