#ifndef DISK_H
#define DISK_H
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <cmath>
using namespace std;
class Disk {
	const char * path;
	fstream *myFile;
public :
     Disk(const char * path);
	void createDisk(int bytes);
	void writeBlock( int blockNumber,void *buffer);
	void readBlock( int blockNumber,void *buffer);
	unsigned int getSizeDisk();

};
#endif 