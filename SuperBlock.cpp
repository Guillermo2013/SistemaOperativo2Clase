#include "SuperBlock.h"
#include <stdio.h>
#include <string.h>
SuperBlock :: SuperBlock(Disk *disk){
    this->disk = disk;
    this->buffer = (char*)malloc(4096);
    this->disk->readBlock(1,buffer);
    memcpy(&(this->bitMapBlockSize),buffer,sizeof(int));
    memcpy(&(this->BlockFree),&buffer[sizeof(int)],sizeof(int));
}

void SuperBlock :: save(){
    this->buffer = (char*)malloc(4096);
    memcpy(buffer,&(this->bitMapBlockSize),sizeof(int));
    memcpy(&buffer[sizeof(int)],&(this->BlockFree),sizeof(int));
    disk->writeBlock(1,buffer);
}
