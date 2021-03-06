#include "Disk.h"
#include <iostream>
Disk :: Disk(const char * path){
	this->path = path;
	this->myFile = new std::fstream(path, std::fstream::binary | std::fstream::out | std::fstream::in);

	if(!this->myFile->is_open()){
		perror("Error opening disk");
		exit(-1);
	}
}
void Disk:: createDisk(int bytes){

	if(bytes % 4096 == 0)
	this->myFile->seekp(bytes - 1);
	else{
		// myFile.seekp(std::ceil(+(bytes / 4096 ))*4096);
		this->myFile->seekp((bytes)+ (4096 - (bytes % 4096))-1);
	}	
	this->myFile->write("", 1);	
	this->myFile->flush();
}
void Disk:: readBlock( int blockNumber,void *buffer){
	this->myFile->seekg(blockNumber * 4096 ,std::ios::beg );
	this->myFile->read((char*)buffer,4096);
	 
}
void Disk:: writeBlock( int blockNumber,void *buffer){
	this->myFile->seekp((blockNumber * 4096) ,	ios	::	beg);
	this->myFile->write((char *)buffer,4096);
	this->myFile->flush();
}
 long int Disk::getSizeDisk(){
    this->myFile->seekg( 0, std::ios::end );
    long int fsize = this->myFile->tellg();
    return fsize;
}
void Disk::close(){
	this->myFile->close();
}