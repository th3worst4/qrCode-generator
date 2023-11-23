#include "image.hh" // this header contains all declarations

int main(int argc, char** argv){

    /* checks if any argv was given at execution time
    if not, asks the user to input someone */
    if(argc <= 1){
        char buffer[20]; // buffer only to down 20 chars, v1 qrcode limit
        std::cout<<"You have to pass data to be encoded\n";
        std::cout<<"e.g: \".\\main.exe samplestring\"\n";
        std::cin>>buffer; // unsafe approach
        *(argv+1) = buffer; // places the buffer on same adress as argv+1, i think it leads to less code
    }

    Image out(21, 21, 1); // Creates an Image object

    /* cals the generate function,
    this function contains all other instructions */
    out.generate(21, "'Twas brillig", 'L', 0b011);

    return 0;
}