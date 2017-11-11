#include "Directory.h"
#include <istream>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#define directorySize 128
#define sizeChar sizeof(char)
#define sizeInt sizeof(int)
#define sizeName directorySize -sizeChar-sizeInt

Directory :: Directory(Disk * disk,unsigned int Block){
    this->disk = disk;
    this->block = Block;
    disk->readBlock(Block,this->buffer);
    for(int i = 0;i<32;i++){
        memcpy(&(this->directoryEntry[i].nombre),&(this->buffer[i*directorySize]),sizeName);
        memcpy(&(this->directoryEntry[i].typeDirectory),&(this->buffer[(i*directorySize)+sizeName]),sizeChar);
        memcpy(&(this->directoryEntry[i].block),&(this->buffer[(i*directorySize)+sizeName+sizeChar]),sizeInt);
        
    }
    
}



void Directory :: save(){
    
    for(int i = 0;i<32;i++){
        
        memcpy(&(this->buffer[i * directorySize]), &(this->directoryEntry[i].nombre[0]), sizeName);
        memcpy(&(this->buffer[(i*directorySize)+sizeName]),&(this->directoryEntry[i].typeDirectory),sizeChar);
        memcpy(&(this->buffer[(i*directorySize)+sizeName+sizeChar]),&(this->directoryEntry[i].block),sizeInt);
    }
    
    disk->writeBlock(this->block,this->buffer);
}