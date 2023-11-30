#include "image.hh" // this header contains all declarations

int main(int argc, char** argv){

    read_tables();

    /*
        checks if any argv was given at execution time
        if not, asks the user to input someone
    */
    if(argc <= 1){
        char buffer[20]; // buffer only to down 19 chars + '\n' , v1 qrcode limit
        std::cout<<"you have to pass data to be encoded\n";
        std::cout<<"e.g: \".\\main.exe samplestring\"\n";
        std::cout<<"you can pass it at runtime too\n";
        std::cout<<"(main) ";
        std::cin>> std::setw(20) >> buffer; // setw(20) limits the size of data input to 19 + \0
        *(argv+1) = buffer; // places the buffer on same adress as argv+1, i think it leads to less code
    }

    Image out(21, 21, 1); // Creates an Image object

    try{
        /*
            cals the generate function,
            this function contains all other instructions
        */
        out.generate(21, "'Twas brillig", 0b011);
    }catch (...){
        // pretty sure it isn't a good error handler
        return -1;
    }
    return 0;
}