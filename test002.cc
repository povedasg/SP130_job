#include <cstdlib>
#include <cstdio>
#include <cassert>

#include "sp130Encoder.hh"
#include "utilities.hh"
#include <cstring>
// Test for encoding a E_DISPLAY_IMAGE_REQUEST with no specific image!

int main() {
    //printf("Lets encode a msg:\n");

    Sp130Encoder encoder;
    char test[2500];
    size_t total = 0; 

    //printf("ENDIAN IS: %d\n", check_for_endianness());--> It is Little endian my machine.

    memset(test,0,sizeof(test));
    ET_ErrorTypes res = encoder.encodeMsg(E_DISPLAY_IMAGE_REQUEST, test,sizeof(test), &total);
    assert(res == E_OK);

    //printf("RES: %d\n", res);
    //printf("Print the msg...(%ld bytes) :\n", total);
    print_hex(test,total);
}

// Lines starting with "//!" define the expected output for this test.
// Data from datacheet ICD

//! 02 00 08 33 44 2F 01 00 00 00 00 03 52
