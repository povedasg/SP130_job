#include "sp130Manager.hh"
#include "utilities.hh"

Sp130Manager::Sp130Manager()
{

}
Sp130Manager::~Sp130Manager()
{

}

void Sp130Manager::setNewImage(const char* path)
{
	//TODO!! Link with serial communication:

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
		printf("___________________________________\n");
		print_hex(this->msg,total);
		printf("___________________________________\n");
	}
	else
	{
		printf("ERROR BUILDING MESSAGE!! Sp130Manager::setNewImage (%s)\n", path);

	}
}