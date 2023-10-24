#include "includes/image.h"

int main(int agrc, char** argv){
    int w, h;

    w = 72;
    h = 72;

    Image out(w, h, 3);
    bool test = true;

    for(int i = 0; i < out.size ; i += out.channels){
        out.fillpixel(test, i);
        test = !test;
    }

    out.write("out.png");

    return 0;
}