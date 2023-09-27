#include <cstdlib>
#include <cstdio>
#include <cassert>

#include "sp130Encoder.hh"
#include "utilities.hh"
#include <cstring>
// Test for encoding a E_DISPLAY_IMAGE_REQUEST with specific image!

int main() {
    //printf("Lets encode a msg:\n");

    Sp130Encoder encoder;
    char test[2500];
    char imgData[5000];
    size_t total = 0; 

    //printf("ENDIAN IS: %d\n", check_for_endianness());--> It is Little endian my machine.

    //Get the image data:
    size_t totalImgRead = read_hex_file("testImg.PNG", imgData, sizeof(imgData));

    //IMAGE DATA:
    /*printf("TOTAL IMG DATA: ");
    print_hex(imgData,totalImgRead);
    printf("\n\n");*/

    memset(test,0,sizeof(test));
    ET_ErrorTypes res = encoder.encodeMsg(E_DISPLAY_IMAGE_REQUEST, test,sizeof(test), &total, imgData, totalImgRead);
    assert(res == E_OK);

    //printf("RES: %d\n", res);
    //printf("Print the msg...(%ld bytes) :\n", total);
    print_hex(test,total);
}

// Lines starting with "//!" define the expected output for this test.
// Data from datacheet ICD

//! 02 02 14 33 44 2F 00 00 00 00 00 02 0A 89 50 4E 47 0D 0A 1A 0A 00 00 00 0D 49 48 44 52 00 00 00 46 00 00 00 1A 08 06 00 00 00 0A 62 2A 08 00 00 00 01 73 52 47 42 00 AE CE 1C E9 00 00 00 04 67 41 4D 41 00 00 B1 8F 0B FC 61 05 00 00 00 09 70 48 59 73 00 00 12 74 00 00 12 74 01 DE 66 1F 78 00 00 01 9F 49 44 41 54 58 47 ED 96 6D 92 83 20 0C 40 3D A3 33 BD 50 87 AB D8 A3 E8 41 FA C3 63 64 03 04 85 90 28 2C BB 6B DB E5 CD 38 A3 F2 91 E4 01 B5 03 74 44 BA 18 85 2E 46 A1 8B 51 90 C5 2C 06 86 61 80 E1 3E D3 0B 06 B5 9B C5 3F AE 8F 11 9F 0D 28 BD DF 92 63 31 51 F1 09 4C CC 27 72 2A 46 DC 09 FF 5D 8C 59 66 30 56 0E 3F 52 4C 4C 7A 94 FC 98 F1 B1 C2 7C 0F 72 65 C1 7E 5C 68 1F 61 5A 26 18 F1 7E 13 EE E2 E0 FB 27 3D 3B 56 98 6E D8 FF 36 E1 9D A5 3C 5E BA E0 78 6D 73 E4 9C 88 61 F7 81 02 31 E9 18 7A 17 25 E2 8B 88 8A 7E 7A 29 C9 B8 0A 31 67 F1 C2 22 EC 7D 68 1E 49 20 72 2E 06 F1 45 44 13 94 88 61 BB 2C E9 43 12 EC 2A C7 64 C9 D7 88 39 8A 47 7D 78 3C 2D 0F 4B 91 98 2C 78 81 18 B9 68 EA 23 16 8C F0 B8 15 62 0E E3 91 80 BD 9E 00 CD 25 7C 7D 0B C5 20 F1 3B D6 5E 2E C6 17 19 DF 27 F0 02 9A C5 D0 58 A9 1E C7 4F 88 41 B6 23 D5 28 46 2E 18 E1 71 C5 7E DF 10 F3 AB 3B C6 E1 93 B0 6D 4D 62 9A 7E 63 28 87 1A 31 61 0C 17 D0 FE 1B 13 41 6D 4D 62 10 FD AB 14 8B C8 0B DA 3E C9 55 62 04 E9 61 B7 6C 79 A7 D4 8B 41 42 72 2D 62 2C 21 59 7F 61 9B FB 1F 93 F6 D9 85 F9 CB CE EB E2 57 8A 71 44 8B EA 2E E1 08 05 64 31 57 E1 12 97 57 F0 AF B9 46 8C 78 B6 F3 63 73 25 D7 ED 18 BE AD 33 51 D7 F2 5A 47 E9 85 E8 62 14 BA 18 85 2E 46 A1 8B 51 E8 62 14 BA 18 11 80 2F A8 D5 DA EB 2F 05 1B B1 00 00 00 00 49 45 4E 44 AE 42 60 82 03 E1
