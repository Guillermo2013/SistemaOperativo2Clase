
#include "Disk.h"
#include "FS.h"
#include <iostream>
int main(int argc, char const *argv[])
{
	const char * path = "archivo.bin";
	Disk *disk = new Disk(path);
	disk->createDisk(10*4096);
	FS *fs = new FS(disk);
	fs->format();
	std::cout<<"bloque alocado "<<fs->allocateBlock()<<std::endl;
	std::cout<<"cantidad de bloques libres "<<fs->getTotalFreeBlock()<<std::endl;
	fs->freeBlock(5);
	std::cout<<"cantidad de bloques libres "<<fs->getTotalFreeBlock()<<std::endl;
	fs->printfBlockAllocate();
	disk->close();
	return 0;
}