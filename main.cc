#include <cstdlib>
#include <cstdio>

#include "sp130Encoder.hh"
#include "utilities.hh"
#include <cstring>

int main(int argc, char **argv) 
{
    printf("Lets encode a msg:\n");

    Sp130Encoder encoder;
    char test[250];
    size_t total = 0; 

    printf("ENDIAN IS: %d\n", check_for_endianness());

    memset(test,0,sizeof(test));
    ET_ErrorTypes res = encoder.encodeMsg(E_SERIAL_NUM_REQUEST, test,sizeof(test), &total);

    printf("RES: %d\n", res);
    printf("Print the msg...(%ld bytes) :\n", total);
    for(size_t i = 0; i < total; ++i)
    {
        printf("%02X ", test[i]);
    }
    printf("\n");
    printf("Should be:\n02 00 03 36 34 2F 03 2D\n");
    
}