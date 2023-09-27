#ifndef SP130_TYPES
#define SP130_TYPES 1

#define SIZE_SERIAL_NUM_REQUEST 8
#define SIZE_DISPLAY_IMAGE_REQUEST 13
#define SIZE_MSG_METADATA 5 /*header + end + size + CRC*/
#define COORDINATES_IMG_X 0
#define COORDINATES_IMG_Y 0
#define MAX_POSSIBLE_SIZE_IMG (0xFFFF - 10) /* MAX 2 bytes - 10 (type, sep, imgID,x,y,legth) */

#define START_MSG 0x02 
#define END_MSG 0x03 
#define SEPARATOR_A 0x2F
#define SEPARATOR_B 0x2E

typedef enum _ET_ErrorTypes
{
	E_OK,
	E_FAIL
} ET_ErrorTypes;

typedef enum _ET_MsgTypes
{
	E_SERIAL_NUM_REQUEST   	= 0x3634,
	E_SERIAL_NUM_RESPONSE 	= 0x3635,
	E_DISPLAY_IMAGE_REQUEST	= 0x3344
} ET_MsgTypes;

typedef enum _ET_EndianTypes
{
	E_BIG_ENDIAN  = 0,
	E_LITTLE_ENDIAN = 1
} ET_EndianTypes;


#endif