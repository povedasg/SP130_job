#include "sp130Manager.hh"
#include "utilities.hh"

using mn::CppLinuxSerial::BaudRate;
using mn::CppLinuxSerial::NumDataBits;
using mn::CppLinuxSerial::Parity;
using mn::CppLinuxSerial::NumStopBits;
using mn::CppLinuxSerial::HardwareFlowControl;
using mn::CppLinuxSerial::SoftwareFlowControl;

Sp130Manager::Sp130Manager()
{
	//Set up the serial port:
	serialManager = new SerialPort(SERIAL_PORT, 
		BaudRate::B_115200, 
		NumDataBits::EIGHT, 
		Parity::NONE, 
		NumStopBits::ONE, 
		HardwareFlowControl::ON, 
		SoftwareFlowControl::OFF);

	printf("SET UP SERIAL PORT: %s with baud: 115200\n",SERIAL_PORT);

	serialManager->SetTimeout(1000); // Block when reading for 1000ms

	serialManager->Open();
}
Sp130Manager::~Sp130Manager()
{

}

void Sp130Manager::setNewImage(const char* path)
{
	//Get img data:
	ET_ErrorTypes res;
	size_t totalImgRead = read_hex_file(path, this->img, sizeof(this->img));
	// Now get the msg to send:
	size_t total = 0;
	if(totalImgRead > 0 && totalImgRead <= MAX_POSSIBLE_SIZE_IMG)
	{
		res = encoder.encodeMsg(E_DISPLAY_IMAGE_REQUEST, this->msg,sizeof(this->msg), &total, this->img, totalImgRead);
	}
	else
	{
		printf("SIZE OF IMAGE NOT VALID (must be between 1-%d)...actual size is: %ld\n",MAX_POSSIBLE_SIZE_IMG, totalImgRead);
		res = E_FAIL;
	}

	if(res == E_OK)
	{
		printf("SENDING MESSAGE TO SP130 to change Image for (%s) (%ld bytes): \n", path, total);
		printf("________MSG SENT SERIAL ___________________________\n");
		print_hex(this->msg,total);
		printf("________MSG SENT SERIAL ___________________________\n");
	}
	else
	{
		printf("ERROR BUILDING MESSAGE!! Sp130Manager::setNewImage (%s)\n", path);

	}
	/* NOW SEND TO SERIAL PORT: */
	std::vector<unsigned char> data (this->msg, this->msg + total / sizeof(this->msg[0]) );
	serialManager->WriteBinary(data);

}