
#include "FS.h"
#include <stdio.h>
#include <iostream>

FS :: FS(Disk * disk){
   this->disk = disk;
}

void FS :: format(){
 
  SuperBlock * superBlock = new SuperBlock(this->disk);
  int sizeDisk = this->disk->getSizeDisk();
  superBlock->bitMapBlockSize = std::ceil(+( sizeDisk / 4096 / 8.0f / 4096  ));
  superBlock->BlockFree = std::ceil(+(sizeDisk   / 4096)) - superBlock->bitMapBlockSize - 2 ;
  superBlock->save();
  Bitmap * bitmap = new Bitmap(this->disk);

  for(int i=0;i<superBlock->bitMapBlockSize*4096; i++){
    bitmap->setBit(i,false);
  }
  for(int i=0;i<superBlock->bitMapBlockSize +2; i++){
    bitmap->setBit(i,true);
  }
  bitmap->save();
  delete superBlock;
  delete bitmap;
  
}
unsigned int FS :: allocateBlock(){
  
  
   SuperBlock * superBlock = new SuperBlock(this->disk); 
   Bitmap * bitmap = new Bitmap(this->disk);
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
  SuperBlock * superBlock = new SuperBlock(this->disk);
  Bitmap * bitmap = new Bitmap(this->disk);
  if(bitmap->getBit(numberBlock) == true){
    cout<<"freeblock if"<<endl;
    bitmap->setBit(numberBlock,false);
    superBlock->BlockFree++;
    superBlock->save();
    bitmap->save();
    
  }
  delete bitmap;
  delete superBlock;
}
unsigned int FS :: getTotalFreeBlock(){
  SuperBlock * superBlock = new SuperBlock(this->disk);
  int cantidadLibre = superBlock->BlockFree;
  superBlock->~SuperBlock();
  return cantidadLibre; 
}
void FS::printfBlockAllocate(){
    SuperBlock * superBlock = new SuperBlock(this->disk);
    Bitmap * bitmap = new Bitmap(this->disk);
    for(int i=0 ;i<superBlock->bitMapBlockSize*4096;i++){
        if(bitmap->getBit(i)){
          cout<<"bloque Alocado "<<i<<endl;
        }
    }

}