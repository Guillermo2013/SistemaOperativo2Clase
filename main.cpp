
#include "Disk.h"
int main(int argc, char const *argv[])
{
	const char * path = "prueba.txt";
	char buffer[4096];
	int i;
	int block;
	Disk *disco = new Disk(path);
	disco->createDisk(2332);
	for(block = 0;block<10;block++){
		for(i=0;i<4096;i++){
			buffer[i] = block +'0';	
		}
		disco->writeBlock(block,buffer);
	}
	disco->readBlock(5,&buffer);
	for(i=0;i<4096;i++){
		printf("%c",buffer[i]);	
	}
	return 0;
}