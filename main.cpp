
#include "Disk.h"
#include "FS.h"
#include <iostream>
#include <string.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	const char * path = "archivo.bin";
	Disk *disk = new Disk(path);
	disk->createDisk(20*4096);
	FS *fs = new FS(disk);
	fs->format();
	fs->mkdir("/root");
	fs->mkdir("/root/usb");
	fs->mkdir("/root/usb2");
	fs->createFile("/root/archivo.png");
	fs->ls("/root");
	cout << "size file /root/archivo.png " <<fs->getSizeFile("/root/archivo.png")<<endl;
	char *buffer = "este es una prueba de escritura de un archivo ";
	fs->writeFile("/root/archivo.png", 5000, (char *)buffer, strlen(buffer));
	char *buffer2=(char*)malloc(strlen(buffer));
	fs->readFile("/root/archivo.png", 5000, buffer2, strlen(buffer));
	cout<<buffer2<<endl;
	disk->close();
	delete fs;
	delete disk;

	return 0;
}