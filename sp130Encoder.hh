#ifndef SP130_ENCODER
#define SP130_ENCODER 1

#include "sp130Types.hh"
#include <stdio.h>
#include <stdint.h>

/*
Class to build messages to Send to the SP130 device
*/

class Sp130Encoder
{
public:
	Sp130Encoder();
	~Sp130Encoder();
	//Functions to call:
	ET_ErrorTypes encodeMsg(ET_MsgTypes type, char* buffer, size_t sizeBuff, size_t* bytesMsgRes);

	ET_ErrorTypes encodeMsg(ET_MsgTypes type, char* buffer, size_t sizeBuff, size_t* bytesMsgRes, 
		char* extraData, size_t sizeExtraData);

private:
	ET_ErrorTypes buildSerialNumMsg(char* buffer, size_t sizeBuff, size_t* bytesMsgRes);
	ET_ErrorTypes buildDisplayImgMsg(char* buffer, size_t sizeBuff, size_t* bytesMsgRes, char* img, size_t sizeImg);

	//Variables
	uint8_t counterImgID;

};

#endif