
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
	
	fs->mkdir("/s/d/v");
    fs->mkdir("/s/d/v/test");

	fs->ls("/");
	disk->close();
	return 0;
}