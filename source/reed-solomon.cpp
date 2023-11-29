#include "image.hh"

/*
    this cpp file should contain all needed reed-solomon algorithms
    to perform the error correction task
    I must say pretty much of this code is a cpp adaptation of
    the python implementation presented at: 
    https://en.wikiversity.org/w/index.php?title=Reed–Solomon_codes_for_coders&oldid=2487070
*/

int gf_add(int a, int b){
    return a ^ b;
}

int bit_length(int a){
    int bits = 0;
    while(a >> bits) bits++;
    return bits;
}

int gf_mult(int a, int b, int prim, int field_charac_full, bool carryless){
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