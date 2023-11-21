#include "image.hh"

int main(int argc, char** argv){

    if(argc <= 1){
        char buffer[20];
        std::cout<<"You have to pass data to be encoded\n";
        std::cout<<"e.g: \".\\main.exe samplestring\"\n";
        std::cin>>buffer;
        *(argv+1) = buffer;
    }

    int w = 21;
    Image out(21, 21, 1);
    bool test = true;

    out.generate(21, "'Twas brillig", 'L', 0b011);

    return 0;
}