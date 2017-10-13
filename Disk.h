#ifndef DISK_H
#define DISK_H
#include <stdio.h>
#include <stdlib.h>
using namespace std;
class Disk {
	const char * path;
public :
     Disk(const char * path);
	void createDisk(int bytes);
	void writeBlock(unsigned int blockNumber,void *buffer);
	void readBlock(unsigned int blockNumber,void *buffer);
	

};
#endif 