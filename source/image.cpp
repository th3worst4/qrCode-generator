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
    for(int j = 0; j < 7; j++){
        memset(data+j*w, 0, 7);
        memset(data+(w-7)+j*w, 0, 7);
        memset(data+(h-7)*w+j*w, 0, 7);
    }
    for(int i = 0; i < 5; i++){
        memset(data+(i+1)*w+1, 255, 5);
        memset(data+(w-6)+(i+1)*w, 255, 5);
        memset(data+(h-6)*w+i*w+1, 255, 5);
    }
    for(int k = 0; k < 3; k++){
        memset(data+(k+2)*w+2, 0, 3);
        memset(data+(w-5)+(k+2)*w, 0, 3);
        memset(data+(h-5)*w+k*w+2, 0, 3);
    }
    timing();
}
void Image::timing(){
    bool pixel = 1;
    for(int i = 0; i < w-15; i++){
        *(data+w*6+7+i) = pixel*255;
        *(data+w*(7+i)+6) = pixel*255;
        pixel = !pixel;
    }
}