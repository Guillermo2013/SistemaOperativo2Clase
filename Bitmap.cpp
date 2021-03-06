#include "Bitmap.h"
#include <iostream>
Bitmap :: Bitmap(Disk * disk){
    char rootblock[4096];
    this->disk = disk;
    disk->readBlock(1,rootblock);
    this->size = *((int *)rootblock);
    this->buffer = (char*)malloc(this->size*4096);
    for (int i=0;i<this->size;i++){
        disk->readBlock(i+2,buffer+i*4096);
    }
}

void Bitmap :: save(){
    
    for (int i=0;i<this->size;i++){
        disk->writeBlock(i+2,buffer+i*4096);
    }
    
}

void Bitmap ::setBit(int numberBit,bool value){
 int bytes = numberBit / 8;
 int bit = numberBit % 8;
 if(value != false){
   buffer[bytes] |= (value<<bit);
 }else{ 
    buffer[bytes] ^= (1<<bit);
 }
}
bool Bitmap :: getBit(int numberBit){
    int bytes = numberBit / 8;
    int bit = numberBit % 8;
    return ((this->buffer[bytes]) & 1 << bit)? true:false;
         
}

void Bitmap::printBitmap()
{
    for(int i=0;i<(this->size*4096);i++)
        cout<<(int)this->buffer[i];
}