#include "File.h"
#include<istream>
#include <string.h>
#include <iostream>


File ::File(Disk *disk, int Block){
    this->disk = disk;
    this->block = Block;
    this->disk->readBlock(this->block,this->buffer);
    memcpy(this->name, this->buffer, sizeName);
    memcpy(&(this->size), &buffer[sizeName], sizeInt);
    memcpy(&(this->head), &buffer[sizeName + sizeInt], sizeInt);

}

void File::save(){
    memcpy(this->buffer, this->name,sizeName);
    memcpy(&(this->buffer[sizeName]), &(this->size), sizeInt);
    memcpy(&(this->buffer[sizeName + sizeInt]), &(this->head), sizeInt);
    disk->writeBlock(this->block,this->buffer);
    
}