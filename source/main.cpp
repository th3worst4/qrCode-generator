#include "image.hh"

int main(int agrc, char** argv){

    Image out(21, 21, 1);
    bool test = true;

    /*for(int i = 0; i < out.size ; i += out.channels){
        out.fillpixel(test, i);
        test = !test;
    }*/

    out.positioning();
    out.messengedata(*(argv+1));
    out.errorcorrection('L');
    out.write("out.png");

    return 0;
}