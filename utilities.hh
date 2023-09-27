#ifndef UTILITIES
#define UTILITIES 1

#include "sp130Types.hh"
#include <cstdint>
#include <stdint.h>
#include <stdio.h>

ET_EndianTypes check_for_endianness();

//! Byte swap unsigned short
uint16_t swap_uint16( uint16_t val );

//! Byte swap short
int16_t swap_int16( int16_t val );

//! Byte swap unsigned int
uint32_t swap_uint32( uint32_t val );

//! Byte swap int
int32_t swap_int32( int32_t val );


void convert_to_endian(ET_EndianTypes type, void* data, size_t size);

char calculate_checksum(char* data, size_t size);

void print_hex(char* data, size_t size);

/* Returns the bytes read */
size_t read_hex_file(const char* path, char* data, size_t sizeData);

#endif