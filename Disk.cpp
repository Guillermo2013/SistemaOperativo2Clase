#include "Disk.h"
#include <fstream>
#include <cmath>
Disk :: Disk(const char * path){
	this->path = path;
}
void Disk:: createDisk(int bytes){
	ofstream myFile;
	myFile.open(path);
	if(bytes % 4096 == 0)
	 myFile.seekp(bytes - 1);
	else
		// myFile.seekp(ceil(+(bytes / 4096 ))*4096);
		myFile.seekp((bytes)+ (4096 - (bytes % 4096))-1);

	myFile<<'.';
	myFile.close();
}
void Disk:: readBlock(unsigned int blockNumber,void *buffer){
  ifstream myFile(path, std::ifstream::in);;
  myFile.seekg(blockNumber * 4096 ,std::ios::beg );
  myFile.read((char*)buffer,4096);
  myFile.close();	 
}
void Disk:: writeBlock(unsigned int blockNumber,void *buffer){
	ofstream myFile(path, ofstream::out | ofstream::app);
	myFile.seekp(blockNumber * 4096 );
	myFile<< (char *)buffer;
	myFile.close();
}
