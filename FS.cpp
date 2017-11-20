
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
  Directory *directory = new Directory(this->disk,superBlock->Blockroot);
  directory->format();
  directory->save();
  Bitmap *bitmap = new Bitmap(this->disk);
  for (int i = 0; i < (sizeDisk/4096) ; i++)
  {
    bitmap->buffer[i] = 0;
    if (i >= 0 && i < superBlock->bitMapBlockSize + 3)
      bitmap->setBit(i, true); 
  }
  bitmap->save();
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
  for (int i = acumulado; i < strlen(name); i++)
  {
    if (name[i] == '/')
     return i;
  }
 return strlen(name);
}
void FS:: mkdir(const char*name){
  SuperBlock * superBlock = new  SuperBlock(this->disk);  
  Directory * directory = new Directory(this->disk,superBlock->Blockroot);
    int acumulado = 0;
    int inicio = 0;
    char *prueba = new char();
    while (acumulado<strlen(name))
    {
      acumulado = split(name, acumulado + 1);
      char *path;
      memcpy(&path[0], &name[inicio], acumulado-inicio);
      for (int i = 0; i < 32; i++)
      {
        if (strcmp(&(directory->directoryEntry[i]->nombre[0]), &path[0]) == 0)
        {
          directory = new Directory(this->disk, directory->directoryEntry[i]->block);
          inicio +=strlen(path); 
        }
      }
     strcpy(&prueba[0],&path[0]);
     memset(path, 0, strlen(path));
    
    }
    if(inicio == strlen(name)){
      cout<<"la direccion ya existe "<<name<<endl;
      return;
    }
    for (int i = 0; i < 32; i++)
    {
        if(directory->directoryEntry[i]->block == -1){
        memcpy(&(directory->directoryEntry[i]->nombre[0]), &prueba[0], 123);
        directory->directoryEntry[i]->typeDirectory = 'D';
        directory->directoryEntry[i]->block = allocateBlock();
        directory->save();
        Directory *directory2 = new Directory(this->disk, directory->directoryEntry[i]->block);
        directory2->format();
        directory2->save();
        delete directory2;
        return;
      }
    }
    delete prueba;
    delete superBlock;
    delete directory;
}

void FS :: ls(const char * name){
  SuperBlock *superBlock = new SuperBlock(this->disk);
  Directory *directory = new Directory(this->disk, superBlock->Blockroot);
  int acumulado = 0;
  int inicio = 0;
  while (acumulado < strlen(name))
  {
    acumulado = split(name, acumulado + 1);
    char *path;
    memcpy(&path[0], &name[inicio], acumulado-inicio); 
    for (int i = 0; i < 32; i++)
    {
      if (strcmp(&(directory->directoryEntry[i]->nombre[0]), &path[0]) == 0)
      {
        directory = new Directory(this->disk, directory->directoryEntry[i]->block);
        inicio += strlen(path); 
      }
    }
    memset(path, 0, strlen(path));
  }
  if (inicio != strlen(name))
  {
    cout << "la direccion no  existe " << name << endl;
    return;
  }
  for (int i = 0; i < 32; i++)
  {
    if(directory->directoryEntry[i]->block != -1){
      cout << "carpetas " << directory->directoryEntry[i]->nombre;
      cout << " tipo " << directory->directoryEntry[i]->typeDirectory;
      cout << " block " << directory->directoryEntry[i]->block << endl;
    }
  }
    delete superBlock;
    delete directory;
}
void FS::createFile(const char * name){
  SuperBlock *superBlock = new SuperBlock(this->disk);
  Directory *directory = new Directory(this->disk, superBlock->Blockroot);
  int acumulado = 0;
  int inicio = 0;
  char *prueba = new char();
  while (acumulado < strlen(name))
  {
    acumulado = split(name, acumulado + 1);
    char *path = new char();
    memcpy(&path[0], &name[inicio], acumulado - inicio); 
    for (int i = 0; i < 32; i++)
    {
      if (strcmp(&(directory->directoryEntry[i]->nombre[0]), &path[0]) == 0)
      {
        directory = new Directory(this->disk, directory->directoryEntry[i]->block);
        inicio += strlen(path);
      }
    }
    strcpy(&prueba[0], &path[0]);
    memset(&path[0], 0, strlen(path));
  }
  if(split(prueba,1) != strlen(prueba)){
    cout<<"no existe la direccion "<<prueba <<endl;
    return;
  }
  for (int i = 0; i < 32; i++)
  {
    if (directory->directoryEntry[i]->block == -1)
    {
      memcpy(&(directory->directoryEntry[i]->nombre[0]), &prueba[0], 123);
      directory->directoryEntry[i]->typeDirectory = 'F';
      directory->directoryEntry[i]->block = allocateBlock();
      directory->save();
      File *file = new File(this->disk, directory->directoryEntry[i]->block);
      memcpy(file->name, &prueba[0],123);
      file->size = 0;
      file->head = 0;
      file->save();
      break;
    }
  }
  
  delete prueba;
  delete superBlock;
  delete directory;
}
unsigned int FS ::getSizeFile(const char *name)
{
  SuperBlock *superBlock = new SuperBlock(this->disk);
  Directory *directory = new Directory(this->disk, superBlock->Blockroot);
  int acumulado = 0, inicio = 0,block = 0;
  char *prueba = new char();
  while (acumulado < strlen(name))
  {
    acumulado = split(name, acumulado + 1);
    char *path;
    memcpy(&path[0], &name[inicio], acumulado - inicio);
    for (int i = 0; i < 32; i++)
    {
      if (strcmp(&(directory->directoryEntry[i]->nombre[0]), &path[0]) == 0)
      {
        if(acumulado < strlen(name)){
          directory = new Directory(this->disk, directory->directoryEntry[i]->block);
          inicio += strlen(path);
        }else{
          block = directory->directoryEntry[i]->block;
        }
      }
    }
    strcpy(&prueba[0], &path[0]);
    memset(path, 0, strlen(path));
  }
  
  File *file = new File(this->disk,block);
  delete prueba;
  delete superBlock;
  return file->size;
}

void FS:: writeFile(const char *name, int position, void *buffer, int size){

  SuperBlock *superBlock = new SuperBlock(this->disk);
  Directory *directory = new Directory(this->disk, superBlock->Blockroot);
  int acumulado = 0, inicio = 0, block = 0;
  while (acumulado < strlen(name))
  {
    acumulado = split(name, acumulado + 1);
    char *path;
    memcpy(&path[0], &name[inicio], acumulado - inicio);
    for (int i = 0; i < 32; i++)
    {
      if (strcmp(&(directory->directoryEntry[i]->nombre[0]), &path[0]) == 0)
      {
        if (acumulado < strlen(name))
        {
          directory = new Directory(this->disk, directory->directoryEntry[i]->block);
          inicio += strlen(path);
        }
        else
        {
          block = directory->directoryEntry[i]->block;
        }
      }
    }

    memset(path, 0, strlen(path));
  }
  File *file = new File(this->disk, block);
  if(file->head == 0)
    file->head = allocateBlock();
  
  delete superBlock;
}
void FS::readFile(const char *name, int position, void *buffer, int size){

}