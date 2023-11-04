#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "image.hh"
#include "stb_image.hh"
#include "stb_image_write.hh"

Image::Image(int w, int h, int channels) : w(w), h(h), channels(channels) {
    size = w*h*channels;
    data = new uint8_t[size];
    dataslots = (h*w-81-2*9*8-2*(w-17)-16)/8;
    datavslots = dataslots-(w-9)/2+1;
    datahslots = dataslots-datavslots;
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
void Image::generate(int w, const char* mess, const char level){
    positioning();
    messengedata(mess);
    errorcorrection(level);
    write("out.png");

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
void Image::errorcorrection(const char level){
    uint8_t* error = new uint8_t[2];

    switch (level){
    case 'L':
        *error = 0;
        *(error+1) = 0;
        break;
    case 'M':
        *error = 0;
        *(error+1) = 1;
        break;
    case 'Q':
        *error = 1;
        *(error+1) = 0;
        break;
    case 'H':
        *error = 1;
        *(error+1) = 1;
        break;
    default:
        *error = 0;
        *(error+1) = 0;
        break;
    }

    for(int i = 0; i < 2; i++){
        *(data+8*w+i) = *(error+i)*255;
        *(data+w*(h-i)-(w-8)) = *(error+i)*255;
    }
}
size_t Image::getlen(const char* mess){
    size_t iterator = 0;
    while(*(mess+iterator) != '\0' || *(mess+iterator) != 0){
        iterator++;
    }
    return iterator;
}
void Image::messengedata(const char* mess){
    *(data+w*h-1) = 0;

    size_t len = getlen(mess);
    std::string binary = std::bitset<8>(len).to_string();

    std::string encmess;
    for(int i = 0; i < len; i++){
        encmess = encmess + std::bitset<8>(*(mess+i)).to_string();
    }
    encmess = encmess + '\0';
    
    int iterator = 0;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 2; j++){
            *(data+(h-2-i)*w-1-j) = !(binary[iterator]-'0')*255;
            iterator++;
        }
    }
    writedata(encmess, len);
}
std::string Image::orientation(const size_t len){
    std::string ori;
    int i = h-6;
    int j = w;
    int vdir = 1;
    for(int index = 0; index < len; index++){
        if(j > w-8){
            if(vdir == 1){
                if(i-4 > 9){
                    ori = ori + "V";
                    i-=4;
                }else {
                    ori = ori + "H";
                    vdir = -1;
                    j-=2;
                }
            }else if(vdir == -1){
                if(i+4 < 21){
                    ori = ori + "V";
                    i+=4;
                }else {
                    ori = ori + "H";
                    vdir = 1;
                    j-=2;
                }
            }
        }else {
            break;
        }
    }
    return ori;
}
void Image::writedata(const std::string encmess, const size_t len){
    std::string ori = orientation(len);
    std::cout<<ori;
    /*for(int i = 0; i < len; i++){
        for(int index = 0; index < 8; index++){

        }
    }*/
}
