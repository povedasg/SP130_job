#ifndef SP130_MANAGER
#define SP130_MANAGER 1

#include "sp130Encoder.hh"

#include "SerialPort.hh"

#define MAX_SIZE_MSG 70000 
#define MAX_SIZE_IMG 1000000//Image store even if its higher that size MSG available

#define SERIAL_PORT "/dev/pts/4" //change to real port

using mn::CppLinuxSerial::SerialPort; 

/*
Class that represents the manager for the SP130
*/

class Sp130Manager
{
public:
	Sp130Manager();
	~Sp130Manager();
	//Functions to call:
	void setNewImage(const char* path);

private:
	Sp130Encoder encoder;
	char msg[MAX_SIZE_MSG];
	char img[MAX_SIZE_IMG];

	SerialPort *serialManager;

};

#endif