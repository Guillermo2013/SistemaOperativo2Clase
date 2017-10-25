
#include "FS.h"
#include <stdio.h>
#include <iostream>

FS :: FS(Disk * disk){
   this->disk = disk;
}

void FS :: format(){
 
  Bitmap * bitmap = new Bitmap(this->disk);
  SuperBlock * superBlock = new SuperBlock(this->disk);
  int sizeDisk = this->disk->getSizeDisk();
  superBlock->bitMapBlockSize = std::ceil(+( sizeDisk / 4096 / 8.0f / 4096  ));
  superBlock->BlockFree = std::ceil(+(sizeDisk   / 4096)) - superBlock->bitMapBlockSize - 2 ;
  for(int i=0;i<superBlock->bitMapBlockSize +2; i++){
    bitmap->setBit(i,true);
  }
 
  bitmap->save();
  superBlock->save();
  superBlock->~SuperBlock();
  bitmap->~Bitmap();
  
}
unsigned int FS :: allocateBlock(){
  
   Bitmap * bitmap = new Bitmap(this->disk);
   SuperBlock * superBlock = new SuperBlock(this->disk); 
   unsigned int blockAllocate;
   for(int i = 0; i<(this->disk->getSizeDisk()/4096);i++){
       if(bitmap->getBit(i) == false){
        bitmap->setBit(i,true);
        blockAllocate = i;
        break;
      }
     
   }
 
   bitmap->save();
   superBlock->BlockFree--;
   superBlock->save();
   superBlock->~SuperBlock();
   bitmap->~Bitmap();
   return blockAllocate;
   
  }
void FS :: freeBlock(unsigned int numberBlock){
  Bitmap * bitmap = new Bitmap(this->disk);
  SuperBlock * superBlock = new SuperBlock(this->disk);
  if(bitmap->getBit(numberBlock) == true){
    bitmap->setBit(numberBlock,false);
    superBlock->BlockFree++;
    superBlock->save();
    bitmap->save();
    
  }
  superBlock->~SuperBlock();
  bitmap->~Bitmap();
}
unsigned int FS :: getTotalFreeBlock(){
  SuperBlock * superBlock = new SuperBlock(this->disk);
  int cantidadLibre = superBlock->BlockFree;
  superBlock->~SuperBlock();
  return cantidadLibre; 
}