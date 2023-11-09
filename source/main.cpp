#include "image.hh"

int main(int argc, char** argv){

    if(argc <= 1){
        std::cout<<"You have to pass data to be encoded\n";
        std::cout<<"e.g: \".\\main.exe samplestring\"\n";
        return -1;
    }

    int w = 21;
    Image out(21, 21, 1);
    bool test = true;

    out.generate(21, *(argv+1), 'L');

    return 0;
}