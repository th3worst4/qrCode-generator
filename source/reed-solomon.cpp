#include "image.hh"

/*
    this cpp file should contain all needed reed-solomon algorithms
    to perform the error correction task
    I must say pretty much of this code is a cpp adaptation of
    the python implementation presented at: 
    https://en.wikiversity.org/w/index.php?title=Reed–Solomon_codes_for_coders&oldid=2487070
*/

int gf_exp[512] = {0};
int gf_log[256] = {0};

int gf_add(int a, int b){
    return a ^ b;
}

int bit_length(int a){
    int bits = 0;
    while(a >> bits) bits++;
    return bits;
}

int gf_mult(int a, int b, int prim){ 
    if(!a || !b){
        return 0;
    } 
    return (gf_exp[gf_log[a] + gf_log[b]]);
}


int gf_mult_noLUT(int a, int b, int prim, int field_charac_full, bool carryless){
    int r = 0;
    while(b){
        if(b & 1){
            r = (carryless) ? r ^ a : r + a;
        }
        b = b >> 1;
        a = a << 1;

        if(prim && a & field_charac_full) a = a ^ prim;
    }
    return r;
}

void init_tables(int prim){
    /*
        there is no purpose on calling this function every time you run the code
        so on debug process you can call it on gdb by passing "call init_tables(0x11d)"
        on gdb console
        it will create two .dat files that contain the exp and log tables to be
        used on multiplication process
    */
    int gf_exptable[256] = {0};
    int gf_logtable[256] = {0};


    std::ofstream gf_log("../source/gf_log.dat");
    std::ofstream gf_exp("../source/gf_exp.dat");

    int x = 1;
    if(gf_log.is_open() && gf_exp.is_open()){
        for(int i = 0; i < 255; i++){
            gf_exptable[i] = x;
            gf_exp << x << std::endl;
            gf_logtable[x] = i;
            x = gf_mult_noLUT(x, 2, prim);
        }
        for(int i = 0; i < 255; i++){
            gf_exp << gf_exptable[i] << std::endl;
            gf_log << gf_logtable[i] << std::endl;
        }
    }

    gf_log.close();
    gf_exp.close();
}

void read_tables(){
    /*
        i found no really good way to read a determined line of file,
        so this function reads all two files and allocates all this data
        on two global int vectors
        i dont know if this is the smartest way to do it, but im really
        proud of thinking it
    */
    std::ifstream gf_expfile("../source/gf_exp.dat");
    std::ifstream gf_logfile("../source/gf_log.dat");

    std::string temp;

    int i = 0;
    while(std::getline(gf_expfile, temp)){
        gf_exp[i] = stoi(temp);
        i++;
    }

    i = 0;
    while(std::getline(gf_logfile, temp)){
        gf_log[i] = stoi(temp);
        i++;
    }

    gf_expfile.close();
    gf_logfile.close();
}