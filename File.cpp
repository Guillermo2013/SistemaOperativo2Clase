#include "File.h"
#include<istream>
#include <string.h>
#include <iostream>
#define directorySize 128
#define sizeChar sizeof(char)
#define sizeInt sizeof(int)
#define sizeName directorySize - sizeChar - sizeInt

File ::File(Disk *disk, int Block){
    this->disk = disk;
    this->block = Block;
    this->name = (char*)malloc(sizeName);
    this->disk->readBlock(this->block,this->buffer);
    memcpy(&(this->name), &(this->buffer), sizeName);
    memcpy(&(this->size), &buffer[sizeName], sizeInt);
    memcpy(&(this->head), &buffer[sizeName + sizeInt], sizeInt);
  
   
}

void File::save(){
    memcpy(&buffer, &(this->name), sizeName);
    memcpy(&buffer[sizeName], &(this->size), sizeInt);
    memcpy(&buffer[sizeName + sizeInt], &(this->head), sizeInt);
    disk->writeBlock(this->block,this->buffer);
   
}