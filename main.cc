#include <cstdlib>
#include <cstdio>
#include <cstring>

#include "sp130Manager.hh"

int main(int argc, char **argv) 
{
    Sp130Manager manager;
    //
    if (argc == 1 || (argc > 1 && (strcmp(argv[1], "-h") == 0
                     || strcmp(argv[1], "--help") == 0))) {
        printf("Usage for sp130Manager:\n\
       --> ./sp130Manager TYPE [PATH]\n\
\n\
  Each TYPE is a real number.\n\
  \t 1 --> Set new Image (If no Path indicated the default is 'testImg.PNG'\n\
\n\
  Each PATH is a String. It Indicates the path of the file to use as data to set (optional depending on type).\n\
\n");
        exit(0);
    }

    if(argc > 1)
    {
        switch(strtol(argv[1],NULL,10))
        {
        case 1:
            //Set Image
            if(argc == 2)
            {
                manager.setNewImage("testImg.PNG");
            }
            else
            {
                manager.setNewImage(argv[2]);
            }

            break;
        default:
            printf("PLEASE INPUT A CORRECT TYPE!\n");
        }
    }
}