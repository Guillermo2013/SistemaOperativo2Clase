
#include "FS.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

FS :: FS(Disk * disk){
   this->disk = disk;
}

void FS :: format(){
 
  SuperBlock * superBlock = new SuperBlock(this->disk);
  int sizeDisk = this->disk->getSizeDisk();
  superBlock->bitMapBlockSize = std::ceil(+( sizeDisk / 4096 / 8.0f / 4096  ));
  superBlock->Blockroot = superBlock->bitMapBlockSize + 2;
  superBlock->BlockFree = std::ceil(+(sizeDisk   / 4096)) - superBlock->bitMapBlockSize - 3 ;
  
  superBlock->save();
  Bitmap * bitmap = new Bitmap(this->disk);
  for(int i=0;i<superBlock->bitMapBlockSize +3; i++){
    bitmap->setBit(i,true);
  }
  bitmap->save();
  Directory *directory = new Directory(this->disk,superBlock->Blockroot);
  for(int i = 0; i<32;i++){
    for(int j = 0;j<123;j++)
     directory->directoryEntry[i].nombre[j] = ' '; 
    
    memcpy(&(directory->directoryEntry[i].typeDirectory), new char('E'),sizeof(char));
    memcpy(&(directory->directoryEntry[i].block) ,new int(-1), sizeof(int));
  }
  directory->save();
 
  delete directory;
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
   delete superBlock;
   delete bitmap;
   return blockAllocate;
   
  }
void FS :: freeBlock(unsigned int numberBlock){
  SuperBlock * superBlock = new SuperBlock(this->disk);
  Bitmap * bitmap = new Bitmap(this->disk);
  if(bitmap->getBit(numberBlock) == true){
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
  delete superBlock;
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
  delete superBlock;
  delete bitmap;
}

int split(const char *name,int acumulado)
{

  char nameArray[strlen(name)];
  strcpy(nameArray, name);

  for (int i = acumulado; i < strlen(name); i++)
  {
    if (nameArray[i] == '/')
    {
     
      acumulado = i ;
     return acumulado;
    }
  
  }
 return strlen(name);
}
void FS:: mkdir(const char*name){
  SuperBlock * superBlock = new  SuperBlock(this->disk);  
  Directory * directory = new Directory(this->disk,superBlock->Blockroot);
    int acumulado = 0;
    int inicio = 0;
    char* prueba;
    while (acumulado<strlen(name))
    {
      acumulado = split(name,acumulado+1);
      char *path = (char *)malloc(acumulado);
      memcpy(&path[0], &name[inicio], acumulado);
      for (int i = 0; i < 32; i++)
      {
        if (strcmp(directory->directoryEntry[i].nombre, path) == 0)
        {
          directory = new Directory(this->disk, directory->directoryEntry[i].block);
          path =  (char *)malloc(strlen(name));
           inicio = acumulado;
        }
      }
     strcpy(prueba,path);
    }
    for (int i = 0; i < 32; i++)
    {
        memcpy(&(directory->directoryEntry[i].nombre), prueba, 123);
        memcpy(&(directory->directoryEntry[i].typeDirectory), new char('D'), sizeof(char));
        int block = allocateBlock();
        memcpy(&(directory->directoryEntry[i].block), new int(block), sizeof(int));
        directory->save();
        Directory *directory = new Directory(this->disk, block);
        for (int i = 0; i < 32; i++)
        {
          for (int j = 0; j < 123; j++)
            directory->directoryEntry[i].nombre[j] = ' ';

          memcpy(&(directory->directoryEntry[i].typeDirectory), new char('E'), sizeof(char));
          memcpy(&(directory->directoryEntry[i].block), new int(-1), sizeof(int));
        }
        directory->save();
      
    }
    
    delete superBlock;
    delete directory;
}

void FS :: ls(const char * path){
  SuperBlock *superBlock = new SuperBlock(this->disk);
  Directory *directory = new Directory(this->disk, superBlock->Blockroot);
  int acumulado = 0;
  int inicio = 0;
  while (acumulado < strlen(path))
  {
    acumulado = split(path, acumulado + 1);
    char *path = (char *)malloc(acumulado);
    memcpy(&path[0], &path[inicio], acumulado);
    for (int i = 0; i < 32; i++)
    {
      if (strcmp(directory->directoryEntry[i].nombre, path) == 0)
      {
        directory = new Directory(this->disk, directory->directoryEntry[i].block);
        path = (char *)malloc(strlen(path));
        inicio = acumulado;
      }
    }
  }
  for (int i = 0; i < 32; i++)
  {
      cout << "carpetas " << directory->directoryEntry[i].nombre;
      cout << " tipo " << directory->directoryEntry[i].typeDirectory;
      cout << " block " << directory->directoryEntry[i].block << endl;
   
  }
    delete superBlock;
    delete directory;
}
