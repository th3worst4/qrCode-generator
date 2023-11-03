#include "image.hh"
#include <string>

std::string UTF8toISO8859_1(const char* in){
    std::string out;
    if (in == NULL)
        return out;

    unsigned int codepoint;
    while (*in != 0){
        unsigned char ch = static_cast<unsigned char>(*in);
        if (ch <= 0x7f)
            codepoint = ch;
        else if (ch <= 0xbf)
            codepoint = (codepoint << 6) | (ch & 0x3f);
        else if (ch <= 0xdf)
            codepoint = ch & 0x1f;
        else if (ch <= 0xef)
            codepoint = ch & 0x0f;
        else
            codepoint = ch & 0x07;
        ++in;
        if (((*in & 0xc0) != 0x80) && (codepoint <= 0x10ffff)){
            if (codepoint <= 255){
                out.append(1, static_cast<char>(codepoint));
            }
        }
    }
    return out;
}

int main(int agrc, char** argv){

    Image out(33, 33, 1);
    bool test = true;

    /*for(int i = 0; i < out.size ; i += out.channels){
        out.fillpixel(test, i);
        test = !test;
    }*/

    out.positioning();
    out.errorcorrection('L');
    out.write("out.png");

    /*std::string out = UTF8toISO8859_1(*(argv+1));

    printf("%s", out);*/

    return 0;
}