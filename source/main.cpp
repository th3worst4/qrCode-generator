#include "image.hh"

int main(int agrc, char** argv){

    int w = 21;
    Image out(21, 21, 1);
    bool test = true;

    out.generate(21, *(argv+1), 'L');

    return 0;
}