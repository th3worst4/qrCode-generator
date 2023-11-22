#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "image.hh"
#include "stb_image.hh"
#include "stb_image_write.hh"

Image::Image(int w, int h, int channels) : w(w), h(h), channels(channels) {
    size = w*h*channels;
    data = new uint8_t[size];
    dataslots = (h*w-81-2*9*8-2*(w-17)-16)/8;
    memset(data, 255, size);
}
Image::Image(const Image& img) : Image(img.w, img.h, img.channels){
    memcpy(data, img.data, img.size);
}
bool Image::write(const char* filename){
    int sucess = stbi_write_png(filename, w, h, channels, data, w*channels);
    return sucess;
}
void Image::generate(int w, const char* mess, const char level, const int mask){
    messengedata(mess);
    errorcorrection(level);
    masking(mask);
    positioning();
    write("out.png");
}
void Image::positioning(){
    for(int i = 0; i < 8; i++){
        memset(data+i*21, 255, 8);
        memset(data+13+i*21, 255, 8);
        memset(data+273+i*21, 255, 8);
    }
    for(int j = 0; j < 7; j++){
        memset(data+j*w, 0, 7);
        memset(data+(w-7)+j*w, 0, 7);
        memset(data+(h-7)*w+j*w, 0, 7);
    }
    for(int k = 0; k < 5; k++){
        memset(data+(k+1)*w+1, 255, 5);
        memset(data+(w-6)+(k+1)*w, 255, 5);
        memset(data+(h-6)*w+k*w+1, 255, 5);
    }
    for(int l = 0; l < 3; l++){
        memset(data+(l+2)*w+2, 0, 3);
        memset(data+(w-5)+(l+2)*w, 0, 3);
        memset(data+(h-5)*w+l*w+2, 0, 3);
    }
    timing();
}
void Image::timing(){
    bool pixel = 1;
    for(int i = 0; i < 7; i++){
        *(data+133+i) = pixel*255;
        *(data+21*(7+i)+6) = pixel*255;
        pixel = !pixel;
    }
}
void Image::errorcorrection(const char level){
    int* error = new int[2];

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
        *(data+168+i) = *(error+i)*255;
        *(data+21*(21-i)-13) = *(error+i)*255;
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
    *(data+w*h-2) = 0;

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
            *(data+(19-i)*21-1-j) = !(binary[iterator]-'0')*255;
            iterator++;
        }
    }
    writedata(encmess, len);
}
void Image::writedata(const std::string encmes, const size_t len){
    std::string ori;
    int i = 15;
    int j = 21;
    int vdir = 1;
    for(int byte = 0; byte < len; byte++){
        int iterator = 0;    
        if(j > w-8){
            if(vdir == 1){
                if(i-4 > 9){
                    ori = ori + "V";
                    for(int a = 0; a < 4; a++){
                        for(int b = 0; b < 2; b++){
                            *(data+(i-a-1)*w+j-b-1) = !(encmes[byte*8 + iterator]-'0')*255;
                            iterator++;
                        }
                    }
                    i-=4;
                }else {
                    ori = ori + "H";
                    vdir = -1;
                    for(int a = 0; a < 2; a++){
                        for(int b = 0; b < 2; b++){
                            *(data+(i-a-1)*w+j-b-1) = !(encmes[byte*8 + iterator]-'0')*255;
                            iterator++;
                        }
                    }
                    j-=2;
                    for(int a = 0; a < 2; a++){
                        for(int b = 0; b < 2; b++){
                            *(data+(i+a-2)*w+j-b-1) = !(encmes[byte*8 + iterator]-'0')*255;
                            iterator++;
                        }
                    }
                    i = h -9;
                }
            }else if(vdir == -1){
                if(i+4 < h){
                    ori = ori + "v";
                    for(int a = 0; a < 4; a++){
                        for(int b = 0; b < 2; b++){
                            *(data+(i+a-1)*w+j-b-1) = !(encmes[byte*8 + iterator]-'0')*255;
                            iterator++;
                        }
                    }
                    i+=4;
                }else {
                    ori = ori + "h";
                    vdir = 1;
                    for(int a = 0; a < 2; a++){
                        for(int b = 0; b < 2; b++){
                            *(data+(i+a-1)*w+j-b-1) = !(encmes[byte*8 + iterator]-'0')*255;
                            iterator++;
                        }
                    }
                    j-=2;
                    for(int a = 0; a < 2; a++){
                        for(int b = 0; b < 2; b++){
                            *(data+(i-a)*w+j-b-1) = !(encmes[byte*8 + iterator]-'0')*255;
                            iterator++;
                        }
                    }
                    i = h - 2;
                }
            }
        }else if(j <= w-8 && j > 9){
            if(vdir == 1){
                if(i-4 > 1){
                    (i == 7) ? i-=1 : i = i;
                    ori = ori + "V";
                    for(int a = 0; a < 4; a++){
                        for(int b = 0; b < 2; b++){
                            *(data+(i-a-1)*w+j-b-1) = !(encmes[byte*8 + iterator]-'0')*255;
                            iterator++;
                        }
                    }
                    i-=4;
                }else {
                    ori = ori + "H";
                    for(int a = 0; a < 2; a++){
                        for(int b = 0; b < 2; b++){
                            *(data+(i-a-1)*w+j-b-1) = !(encmes[byte*8 + iterator]-'0')*255;
                            iterator++;
                        }
                    }
                    j-=2;
                    for(int a = 0; a < 2; a++){
                        for(int b = 0; b < 2; b++){
                            *(data+(i+a-2)*w+j-b-1) = !(encmes[byte*8 + iterator]-'0')*255;
                            iterator++;
                        }
                    }
                    i = 3;
                    vdir = -1;
                }
            }else if(vdir == -1){
                if(i+4 < h){
                    ori = ori + "v";
                    (i == 7) ? i+=1 : i = i;
                    for(int a = 0; a < 4; a++){
                        for(int b = 0; b < 2; b++){
                            *(data+(i+a-1)*w+j-b-1) = !(encmes[byte*8 + iterator]-'0')*255;
                            iterator++;
                        }
                    }
                    i+=4;
                }else {
                    ori = ori + "h";
                    vdir = 1;
                    for(int a = 0; a < 2; a++){
                        for(int b = 0; b < 2; b++){
                            *(data+(i+a-1)*w+j-b-1) = !(encmes[byte*8 + iterator]-'0')*255;
                            iterator++;
                        }
                    }
                    j-=2;
                    for(int a = 0; a < 2; a++){
                        for(int b = 0; b < 2; b++){
                            *(data+(i-a)*w+j-b-1) = !(encmes[byte*8 + iterator]-'0')*255;
                            iterator++;
                        }
                    }
                    i = h - 2;
                }
            }
        }
    }
    ori = ori + "e";
    for(int a = 0; a < 2; a++){
        for(int b = 0; b < 2; b++){
            *(data+(i-a-1)*w+j-b-1) = 255;
        }
    }
}
void Image::masking(const int mask){
    //0b011
    for(int i = 0; i < 3; i++){
        *(data+170+i) = !((mask>>(2-i))&0b001)*255;
        *(data+(18-i)*21+8) = !((mask>>(2-i))&0b001)*255;
    }

    const int line[21] = {0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1};
    for(int i = 0; i < 21; i++){
        if(i > 8 && i < 15){
            continue;
        }else{
            *(data+168+i) = line[20-i]? !(*(data+168+i))*255 : *(data+168+i);
            *(data+21*i+8) = line[i]? !(*(data+21*i+8))*255 : *(data+21*i+8);
        }
    }

    switch (mask){
    case 0b000:
        for(int i = 0; i < 21; i++){
            for(int j = 0; j < 21; j++){                
                if(i == 8 || j == 8){
                    if((j > 8 && j < 13) || (i > 8 && i < 15)){
                         *(data+i*21+j) = ((i+j)%2 == 0)? !(*(data+i*21+j))*255 : (*(data+i*21+j));
                    }else{
                        continue;
                    }
                }else{
                    *(data+i*21+j) = ((i+j)%2 == 0)? !(*(data+i*21+j))*255 : (*(data+i*21+j)); 
                }
            }
        }
        break;
    case 0b001:
        for(int i = 0; i < 21; i++){
            for(int j = 0; j < 21; j++){
                if(i == 8 || j == 8){
                    if((j > 8 && j < 13) || (i > 8 && i < 15)){
                         *(data+i*21+j) = (i%2 == 0)? !(*(data+i*21+j))*255 : (*(data+i*21+j));
                    }else{
                        continue;
                    }
                }else{
                    *(data+i*21+j) = (i%2 == 0)? !(*(data+i*21+j))*255 : (*(data+i*21+j)); 
                }
            }
        }
        break;
    case 0b010:
        for(int i = 0; i < 21; i++){
            for(int j = 0; j < 21; j++){
                if(i == 8 || j == 8){
                    if((j > 8 && j < 13) || (i > 8 && i < 15)){
                        *(data+i*21+j) = (j%3 == 0)? !(*(data+i*21+j))*255 : (*(data+i*21+j)); 
                    }else{
                        continue;
                    }
                }else{
                    *(data+i*21+j) = (j%3 == 0)? !(*(data+i*21+j))*255 : (*(data+i*21+j)); 
                }
            }
        }
        break;
    case 0b011:
        for(int i = 0; i < 21; i++){
            for(int j = 0; j < 21; j++){
                if(i == 8 || j == 8){
                    if((j > 8 && j < 13) || (i > 8 && i < 15)){
                         *(data+i*21+j) = ((i+j)%3 == 0)? !(*(data+i*21+j))*255 : (*(data+i*21+j));
                    }else{
                        continue;
                    }
                }else{
                    *(data+i*21+j) = ((i+j)%3 == 0)? !(*(data+i*21+j))*255 : (*(data+i*21+j)); 
                }
            }
        }
        break;
    case 0b100:
        for(int i = 0; i < 21; i++){
            for(int j = 0; j < 21; j++){        
                if(i == 8 || j == 8){
                    if((j > 8 && j < 13) || (i > 8 && i < 15)){
                         *(data+i*21+j) = ((i/2+j/3)%2 == 0)? !(*(data+i*21+j))*255 : (*(data+i*21+j));
                    }else{
                        continue;
                    }
                }else{
                    *(data+i*21+j) = ((i/2+j/3)%2 == 0)? !(*(data+i*21+j))*255 : (*(data+i*21+j)); 
                }
            }
        }
        break;
    case 0b101:
        for(int i = 0; i < 21; i++){
            for(int j = 0; j < 21; j++){                
                if(i == 8 || j == 8){
                    if((j > 8 && j < 13) || (i > 8 && i < 15)){
                         *(data+i*21+j) = ((i*j)%2 + (i*j)%3 == 0)? !(*(data+i*21+j))*255 : (*(data+i*21+j));
                    }else{
                        continue;
                    }
                }else{
                *(data+i*21+j) = ((i*j)%2 + (i*j)%3 == 0)? !(*(data+i*21+j))*255 : (*(data+i*21+j));
                }
            }
        }
        break;
    case 0b110:
        for(int i = 0; i < 21; i++){
            for(int j = 0; j < 21; j++){               
                if(i == 8 || j == 8){
                    if((j > 8 && j < 13) || (i > 8 && i < 15)){
                        *(data+i*21+j) = (((i*j)%3+i*j)%2 == 0)? !(*(data+i*21+j))*255 : (*(data+i*21+j));
                    }else{
                        continue;
                    }
                }else{
                    *(data+i*21+j) = (((i*j)%3+i*j)%2 == 0)? !(*(data+i*21+j))*255 : (*(data+i*21+j));
                }
                
            }
        }
        break;
    case 0b111:
        for(int i = 0; i < 21; i++){
            for(int j = 0; j < 21; j++){                
                if(i == 8 || j == 8){
                    if((j > 8 && j < 13) || (i > 8 && i < 15)){
                        *(data+i*21+j) = (((i*j)%3+i+j)%2 == 0)? !(*(data+i*21+j))*255 : (*(data+i*21+j)); 
                    }else{
                        continue;
                    }
                }else{
                    *(data+i*21+j) = (((i*j)%3+i+j)%2 == 0)? !(*(data+i*21+j))*255 : (*(data+i*21+j)); 
                }
                
            }
        }
        break; 
    default:
        break;
    }
}

void Image::resize(const int factor){
    Image resized(21*factor, 21*factor, 1);
    uint8_t* r_data = resized.data;
    
    for(int i1 = 0; i1 < 21; i1++){
        for(int j1 = 0; j1 < 21; j1++){
            for(int i2 = 0; i2 < factor; i2++){
                for(int j2 = 0; j2 < factor; j2++){
                    *(r_data+j1*factor+i1*21*(int)pow(factor,2)+j2+i2*21*factor) = *(data+j1+21*i1);
                }
            }
        }
    }

    resized.write("final.png");

}