#include "Disk.h"

Disk :: Disk(const char * path){
	this->path = path;
	this->myFile = new std::fstream(path, std::fstream::binary | std::fstream::out | std::fstream::in | ios::trunc);

	if(!myFile->is_open()){
		perror("Error opening disk");
		exit(-1);
	}
}
void Disk:: createDisk(int bytes){

	if(bytes % 4096 == 0)
		myFile->seekp(bytes - 1);
	else
		// myFile.seekp(std::ceil(+(bytes / 4096 ))*4096);
		myFile->seekp((bytes)+ (4096 - (bytes % 4096))-1);	
	myFile->write("", 1);	
	myFile->flush();
}
void Disk:: readBlock( int blockNumber,void *buffer){
  myFile->seekg(blockNumber * 4096 ,std::ios::beg );
  myFile->read((char*)buffer,4096);
	 
}
void Disk:: writeBlock( int blockNumber,void *buffer){
	myFile->seekp((blockNumber * 4096) ,	ios	::	beg);
	myFile->write((char *)buffer,4096);
	myFile->flush();
}
unsigned int Disk::getSizeDisk(){
	
	myFile->seekg( 0, std::ios::end );
	long int fsize = myFile->tellg();
    return fsize;
}