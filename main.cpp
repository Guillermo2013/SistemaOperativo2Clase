
#include "Disk.h"
#include "FS.h"
#include <iostream>
int main(int argc, char const *argv[])
{
	const char * path = "archivo.bin";
	Disk *disk = new Disk(path);
	disk->createDisk(20*4096);
	FS *fs = new FS(disk);
	fs->format();	
	
	fs->mkdir("/root");
	fs->mkdir("/root/usb");
	fs->mkdir("/root/usb/carpeta");
	fs->createFile("/root/archivo.png");
	fs->ls("/root");
	cout << "size file /root/archivo.png " <<fs->getSizeFile("/root/archivo.png")<<endl;
	

	disk->close();
	delete fs;
	delete disk;
	return 0;
}