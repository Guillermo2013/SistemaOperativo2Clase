#include "FS.h"
#include "Bitmap.h"
#include <stdio.h>
#include <iostream>
FS :: FS(Disk * disk){
   this->disk = disk;
}
void FS :: format(){
  int sizeDisk = this->disk->getSizeDisk();
  int bitMapBlockSize = std::ceil(+( sizeDisk / 4096 / 8.0f / 4096  ));
  int BlockFree = std::ceil(+(sizeDisk   / 4096))- bitMapBlockSize - 2 ;
  char  buffer[4096];
  int i;
  for(i= 0 ;i<4096;i++){
    buffer[i] = NULL; 
  }
  for(i= 0 ;i<(sizeDisk/4096);i++){
    this->disk->writeBlock(i,buffer);
  }
  memcpy(&buffer,&bitMapBlockSize,sizeof( int));
  memcpy(&buffer[sizeof( int)],&BlockFree,sizeof( int));
  this->disk->writeBlock(1,buffer);
  Bitmap * bitmap = new Bitmap(disk);
  for(i=0;i<bitMapBlockSize+2; i++){
    bitmap->setBit(i,true);
  }
  bitmap->save();
  delete bitmap;
}
unsigned int FS :: allocateBlock(){
    
   Bitmap * bitmap = new Bitmap(this->disk);
   
   for(int i = 0; i<(this->disk->getSizeDisk()/4096);i++){
       if(bitmap->getBit(i)){
        printf("%d \n",i);
      }
   }
   delete bitmap;
}
void FS :: freeBlock(unsigned int numberBlock){

}
unsigned int FS :: getTotalFreeBlock(){

}