
#include "Disk.h"
#include "FS.h"
int main(int argc, char const *argv[])
{
	const char * path = "prueba";
	char buffer[4096];
	
	Disk *disk = new Disk(path);
	disk->createDisk(10*4096);
	FS *fs = new FS(disk);
	fs->format();
	/*for(block = 0;block<10;block++){
		for(i=0;i<4096;i++){
			buffer[i] = block +'0';	
		}
		disco->writeBlock(block,buffer);
	}

	disco->readBlock(5,&buffer);
	for(i=0;i<4096;i++){
		printf("%c",buffer[i]);	
	}
	printf("size disk %d ", disco->getSizeDisk());
	*/
	
	return 0;
}