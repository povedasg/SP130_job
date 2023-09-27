#include "utilities.hh"

#include <sys/stat.h> 
#include <cstring>
ET_EndianTypes check_for_endianness()
{
  ET_EndianTypes type = E_BIG_ENDIAN;
  unsigned int x = 1;
  char *c = (char*) &x;
  if((int)*c ==1)
  {
  	type = E_LITTLE_ENDIAN;
  }
  else
  {
  	type = E_BIG_ENDIAN;
  }
  return type;
}

//! Byte swap unsigned short
uint16_t swap_uint16( uint16_t val ) 
{
    return (val << 8) | (val >> 8 );
}

//! Byte swap short
int16_t swap_int16( int16_t val ) 
{
    return (val << 8) | ((val >> 8) & 0xFF);
}

//! Byte swap unsigned int
uint32_t swap_uint32( uint32_t val )
{
    val = ((val << 8) & 0xFF00FF00 ) | ((val >> 8) & 0xFF00FF ); 
    return (val << 16) | (val >> 16);
}

//! Byte swap int
int32_t swap_int32( int32_t val )
{
    val = ((val << 8) & 0xFF00FF00) | ((val >> 8) & 0xFF00FF ); 
    return (val << 16) | ((val >> 16) & 0xFFFF);
}

void convert_to_endian(ET_EndianTypes type, void* data, size_t size)
{
	uint16_t auxU16;
	if(type != check_for_endianness())
	{
		switch(size)
		{
		case 2:
			auxU16 = swap_uint16( *((uint16_t*) data) );
			memcpy(data,&auxU16,sizeof(auxU16));
			break;
		default:
			break;
		}
	}

}

char calculate_checksum(char* data, size_t size)
{
	char res = 0;

	for ( size_t i = 0; i < size; ++i )
      res ^= data[ i ];

	return res;
}

void print_hex(char* data, size_t size)
{
	for(size_t i = 0; i < size; ++i)
    {
        if(i == size - 1)
        	printf("%02X", (unsigned char) data[i]);
        else
        	printf("%02X ", (unsigned char) data[i]);
    }
    printf("\n");
}

size_t read_hex_file(const char* path, char* data, size_t sizeData) 
{
    FILE *fp;
    size_t res = 0;

    if ((fp = fopen (path, "rb")) != NULL) {
        struct stat st;
        stat(path, &st);                

        if((size_t)st.st_size <= sizeData)
        {
        	for (size_t i = 0; i < (size_t) st.st_size; i++) 
        	{
            	data[i] = fgetc(fp);
        	}
    		res = st.st_size;
    	}
    	else
    	{
    		printf("Error lectura de archivo(read_hex_file)\n");
    	}

        fclose(fp);
    }
    else
    {
    	printf("Error lectura de archivo(read_hex_file)\n");
    }

    return res;
}