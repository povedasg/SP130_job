#include "sp130Encoder.hh"
#include "utilities.hh"

#include <cstring>
Sp130Encoder::Sp130Encoder()
{
	counterImgID = 1;
}
Sp130Encoder::~Sp130Encoder()
{

}

ET_ErrorTypes Sp130Encoder::encodeMsg(ET_MsgTypes type, char* buffer, size_t sizeBuff, size_t* bytesMsgRes)
{
	return encodeMsg(type,buffer,sizeBuff,bytesMsgRes, nullptr, 0);	
}

ET_ErrorTypes Sp130Encoder::encodeMsg(ET_MsgTypes type, char* buffer, size_t sizeBuff, size_t* bytesMsgRes, 
		char* extraData, size_t sizeExtraData)
{
	ET_ErrorTypes res = E_FAIL;
	*bytesMsgRes = 0;

	switch (type)
	{
	case E_SERIAL_NUM_REQUEST:
		res = buildSerialNumMsg(buffer, sizeBuff, bytesMsgRes);
		break;
	case E_DISPLAY_IMAGE_REQUEST:
		res = buildDisplayImgMsg(buffer, sizeBuff, bytesMsgRes, extraData, sizeExtraData);
		break;
	default:
		*bytesMsgRes = 0;
		res = E_FAIL;
		break;
	}

	return res;
}

ET_ErrorTypes Sp130Encoder::buildSerialNumMsg(char* buffer, size_t sizeBuff, size_t* bytesMsgRes)
{
	ET_ErrorTypes res = E_FAIL;
	int currentIndex = 0;

	if(sizeBuff >= SIZE_SERIAL_NUM_REQUEST)
	{
		//Build up the message:
		/*
		Message Type 2 A “64”
		Separator 1 A
		Example:  02 00 03 36 34 2F 03 2D
		*/
		//Build Header:
		buffer[currentIndex] = START_MSG;
		currentIndex++;
		//LLL
		uint16_t length = SIZE_SERIAL_NUM_REQUEST - SIZE_MSG_METADATA;
		convert_to_endian(E_BIG_ENDIAN,(void *)&length, sizeof(length));
		memcpy(&buffer[currentIndex],&length,sizeof(length));
		currentIndex += sizeof(length);

		//Message type
		uint16_t type = E_SERIAL_NUM_REQUEST;
		convert_to_endian(E_BIG_ENDIAN,(void *)&type, sizeof(type));
		memcpy(&buffer[currentIndex],&type,sizeof(type));
		currentIndex += sizeof(type);

		//Separator
		buffer[currentIndex] = SEPARATOR_A;
		currentIndex++;

		//Data
		//NONE

		//END
		buffer[currentIndex] = END_MSG;
		currentIndex++;	

		//CheckSum
		buffer[currentIndex] = calculate_checksum(&buffer[1],currentIndex-1);
		currentIndex++;	

		*bytesMsgRes = currentIndex;
		res = E_OK;

	}

	return res;
}

ET_ErrorTypes Sp130Encoder::buildDisplayImgMsg(char* buffer, size_t sizeBuff, size_t* bytesMsgRes, char* img, size_t sizeImg)
{
	ET_ErrorTypes res = E_FAIL;
	int currentIndex = 0;

	//+2 for the Length if sizeImg > 0. Could implement logic in future, not important now.
	if(sizeBuff >= SIZE_DISPLAY_IMAGE_REQUEST + sizeImg + 2)
	{
		//Build up the message:
		/*
		Message Type 2 A “3D”
		Separator 1 A
		Image ID 1 B Image ID, 1..250, if ID = 0, show the image data on following field in this CMD
		X 2 B Display X coordinate, big endian
		Y 2 B Display Y coordinate, big endian
		Image Data Length 2 B Length of the image data, big endian. *
		Image Data … B Image data. *
		Example:  NA
		*/
		//Build Header:
		buffer[currentIndex] = START_MSG;
		currentIndex++;
		//LLL
		uint16_t extraDataSize = 0;
		if(sizeImg > 0)
			extraDataSize = sizeImg + 2;
		uint16_t length = SIZE_DISPLAY_IMAGE_REQUEST - SIZE_MSG_METADATA + extraDataSize;
		convert_to_endian(E_BIG_ENDIAN,(void *)&length, sizeof(length));
		memcpy(&buffer[currentIndex],&length,sizeof(length));
		currentIndex += sizeof(length);

		//Message type
		uint16_t type = E_DISPLAY_IMAGE_REQUEST;
		convert_to_endian(E_BIG_ENDIAN,(void *)&type, sizeof(type));
		memcpy(&buffer[currentIndex],&type,sizeof(type));
		currentIndex += sizeof(type);

		//Separator
		buffer[currentIndex] = SEPARATOR_A;
		currentIndex++;

		//Image ID:
		if(sizeImg > 0)
		{
			buffer[currentIndex] = 0;
			currentIndex++;
		}
		else
		{
			buffer[currentIndex] = counterImgID++;
			currentIndex++;
		}

		//Coordinates X
		uint16_t coordinatesX = COORDINATES_IMG_X;
		convert_to_endian(E_BIG_ENDIAN,(void *)&coordinatesX, sizeof(coordinatesX));
		memcpy(&buffer[currentIndex],&coordinatesX,sizeof(coordinatesX));
		currentIndex += sizeof(coordinatesX);

		//Coordinates Y
		uint16_t coordinatesY = COORDINATES_IMG_Y;
		convert_to_endian(E_BIG_ENDIAN,(void *)&coordinatesY, sizeof(coordinatesY));
		memcpy(&buffer[currentIndex],&coordinatesY,sizeof(coordinatesY));
		currentIndex += sizeof(coordinatesY);

		//Data
		if(sizeImg > 0)
		{
			//Size Img:
			uint16_t auxSize = (uint16_t) sizeImg;
			convert_to_endian(E_BIG_ENDIAN,(void *)&auxSize, sizeof(auxSize));
			memcpy(&buffer[currentIndex],&auxSize,sizeof(auxSize));
			currentIndex += sizeof(auxSize);

			//Img Data
			memcpy(&buffer[currentIndex],img,(uint16_t)sizeImg);
			currentIndex += (uint16_t) sizeImg;
		}

		//END
		buffer[currentIndex] = END_MSG;
		currentIndex++;	

		//CheckSum
		buffer[currentIndex] = calculate_checksum(&buffer[1],currentIndex-1);
		currentIndex++;	

		*bytesMsgRes = currentIndex;
		res = E_OK;

	}

	return res;
}