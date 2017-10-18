#include "FS.h"
#include <stdio.h>
FS :: FS(Disk * disk){
   this->disk = disk;
}
void FS :: format(){

   int sizeDisk = disk->getSizeDisk();
   int mapBytesSize = std::ceil(+( sizeDisk / 4096 / 8.0f / 4096  ));
   int BlockFree = std::ceil(+(sizeDisk   / 4096))- mapBytesSize - 2 ;
  printf("mapByteSize %d \n",mapBytesSize);
  printf("block free %d \n",BlockFree);
  char  buffer[4096];

 memcpy(&buffer,&mapBytesSize,sizeof( int));
 memcpy(&buffer[sizeof( int)],&BlockFree,sizeof( int));
 int i;
  for(i= 8 ;i<4096;i++){
  buffer[i] = NULL; 
  }
  disk->writeBlock(1,buffer);

}
unsigned int FS :: allocateBlock(){
   
}
void FS :: freeBlock(unsigned int numberBlock){

}
unsigned int FS :: getTotalFreeBlock(){

}