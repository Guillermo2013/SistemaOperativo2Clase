#include "Directory.h"
#include <istream>
#include <string.h>
#include <stdio.h>

#define directorySize 128
#define sizeChar sizeof(char)
#define sizeInt sizeof(int)
#define sizeName directorySize -sizeChar-sizeInt

DirectoryEntry::DirectoryEntry(char* buffer){
    memcpy(this->nombre,buffer,sizeName);
    memcpy(&(this->typeDirectory),&buffer[sizeName],sizeChar);
    memcpy(&(this->block),&buffer[sizeName+sizeChar],sizeInt);
}

void DirectoryEntry:: save(){
    memcpy(buffer,this->nombre,sizeName);
    memcpy(&buffer[sizeName],&(this->typeDirectory),sizeChar);
    memcpy(&buffer[sizeName+sizeChar],&(this->block),sizeInt);
}
Directory::Directory(Disk *disk,  int Block){
    this->disk =disk;
    this->block = Block;
    this->disk->readBlock(this->block,this->buffer);
    for(int i = 0;i<4096/directorySize;i++){
        this->directoryEntry[i] = new DirectoryEntry(buffer + (i*directorySize));
    }
}

void Directory :: save(){
    for(int i = 0;i<4096/directorySize;i++){
        this->directoryEntry[i]->save();
        memcpy(&(this->buffer[i*directorySize]),this->directoryEntry[i]->buffer,directorySize);
    }
    this->disk->writeBlock(this->block,this->buffer);
}
void Directory::format(){
    for (int i = 0; i < 32; i++)
    {
        memset(this->directoryEntry[i]->nombre, 0, sizeof(sizeName));
        this->directoryEntry[i]->typeDirectory = 'E';
        this->directoryEntry[i]->block = -1;
    }
}