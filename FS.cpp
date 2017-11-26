
#include "FS.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

FS :: FS(Disk * disk){
   this->disk = disk;
}

void FS :: format(){
  int sizeDisk = this->disk->getSizeDisk();
  for (int i = 0; i <= sizeDisk/4096; i++)
  {
    char buffer[4096];
    memset(buffer, 0, 4096);
    this->disk->writeBlock(i, buffer);
  }
  SuperBlock * superBlock = new SuperBlock(this->disk); 
  superBlock->bitMapBlockSize = std::ceil(+( sizeDisk / 4096 / 8.0f / 4096  ));
  superBlock->Blockroot = superBlock->bitMapBlockSize + 2;
  superBlock->BlockFree = std::ceil(+(sizeDisk   / 4096.0)) - superBlock->bitMapBlockSize - 3 ;
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
    int acumulado = 0, inicio = 0;
    char *prueba = new char(), *path = new char();
    memset(path, 0, strlen(path));
    memset(prueba, 0, strlen(prueba));
    while (acumulado<strlen(name))
    {
      acumulado = split(name, acumulado + 1);
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
    delete path;
    delete superBlock;
    delete directory;
}

void FS :: ls(const char * name){
  SuperBlock *superBlock = new SuperBlock(this->disk);
  Directory *directory = new Directory(this->disk, superBlock->Blockroot);
  int acumulado = 0, inicio = 0;
  char *path;
  memset(&path[0], 0, strlen(path));
  while (acumulado < strlen(name))
  {
    acumulado = split(name, acumulado + 1);
    memcpy(&path[0], &name[inicio], acumulado-inicio); 
    for (int i = 0; i < 32; i++)
    {
      if (strcmp(&(directory->directoryEntry[i]->nombre[0]), &path[0]) == 0)
      {
        directory = new Directory(this->disk, directory->directoryEntry[i]->block);
        inicio += strlen(path); 
      }
    }

    memset(&path[0], 0, strlen(path));
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
  delete path;
  delete superBlock;
  delete directory;
}

void FS::createFile(const char * name){
  SuperBlock *superBlock = new SuperBlock(this->disk);
  Directory *directory = new Directory(this->disk, superBlock->Blockroot);
  int acumulado = 0, inicio = 0;
  char *prueba = new char(),*path = new char();
  memset(&path[0], 0, strlen(path));
  memset(&prueba[0], 0, strlen(prueba));
  while (acumulado < strlen(name))
  {
    acumulado = split(name, acumulado + 1);
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
      delete file;
      break;
    }
  }
  
  delete prueba;
  delete path;
  delete superBlock;
  delete directory;
}

unsigned int FS ::getSizeFile(const char *name)
{
  SuperBlock *superBlock = new SuperBlock(this->disk);
  Directory *directory = new Directory(this->disk, superBlock->Blockroot);
  int acumulado = 0, inicio = 0,block = 0;
  char *path =(char*)malloc(0);
  memset(&path[0], 0, strlen(path));
  while (acumulado < strlen(name))
  {
   acumulado = split(name, acumulado + 1);
    memcpy(&path[0], &name[inicio], acumulado - inicio);
    for (int i = 0; i < 32; i++)
    {
      if (strcmp(&(directory->directoryEntry[i]->nombre[0]), &path[0]) == 0)
      {
        if(acumulado < strlen(name)){
          directory = new Directory(this->disk, directory->directoryEntry[i]->block);
          inicio += strlen(&path[0]);
        }else{
          block = directory->directoryEntry[i]->block;
        }
      }
    }
    memset(&path[0], 0, strlen(path));
 }

  File *file = new File(this->disk, block);
  int size = file->size;
  delete file;
  delete directory;
  delete superBlock;
  return size;
}

void FS::deleteFile(const char * name){
  SuperBlock *superBlock = new SuperBlock(this->disk);
  Directory *directory = new Directory(this->disk, superBlock->Blockroot);
  int acumulado = 0, inicio = 0, block = 0;
  while (acumulado < strlen(name))
  {
    acumulado = split(name, acumulado + 1);
    char *path = new char();
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
          memset(directory->directoryEntry[i]->nombre, 0, sizeName);
          directory->directoryEntry[i]->typeDirectory = 'E';
          directory->directoryEntry[i]->block = -1;
        }
      }
    }
    memset(path, 0, strlen(path));
  }
  directory->save();
  File *file = new File(this->disk, block);
  inicio = file->head;
  char * buffer;
  while(inicio != 0){  
    this->disk->readBlock(inicio,buffer);
    int nextBlock =0;
    memcpy(&nextBlock,&buffer[4092],sizeof(int));
    memset(buffer, 0, 4096);
    this->disk->writeBlock(inicio,buffer);
    freeBlock(inicio);
    inicio = nextBlock;
  }
  delete superBlock;
  delete directory;
  delete buffer;
}

void FS::writeFile(const char *name, int position, void *buffer, int size)
{
  SuperBlock *superBlock = new SuperBlock(this->disk);
  Directory *directory = new Directory(this->disk, superBlock->Blockroot);
  int acumulado = 0, inicio = 0, block = 0;
  char *path = (char *)malloc(0);
  memset(&path[0], 0, strlen(path));
  while (acumulado < strlen(name))
  {
    acumulado = split(name, acumulado + 1);
    strncpy(&path[0], &name[inicio], acumulado - inicio);
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
   memset(&path[0],0,strlen(path));
 
  }
  File *file = new File(this->disk, block);
  if(file->head == 0)
    file->head = allocateBlock();
  int initialblockWrite = file->head;
  int writePositioBlock = std::ceil(+((position+size )/ (4096.0 - sizeof(int))));
  file->save();
  char *bufferBlock= (char*)malloc(4096);
  int inicioBlock = 0;
  int sizeInt2 = size;
  for (int i = 0; i < writePositioBlock; i++)
  {
     this->disk->readBlock(initialblockWrite,bufferBlock);
    if (((position) >= (i * 4096))&& ((position + sizeInt2) < (((i + 1) * 4096)-sizeof(int))))
    {
      memcpy(&bufferBlock[position - (i * 4092)], &((char *)buffer)[inicioBlock], sizeInt2);
      this->disk->writeBlock(initialblockWrite, bufferBlock);
    }
    else if (((position) < ((i + 1) * 4096) - sizeof(int)) && ((position) > (i * 4092)) && ((position + sizeInt2) > ((i + 1) * 4096) - sizeof(int)))
    {
      int escribir = (((i+1)*4096)-sizeof(int))-position;
      memcpy(&bufferBlock[position - ((i * 4096) - sizeof(int))], &((char *)buffer)[inicioBlock], escribir);
      this->disk->writeBlock(initialblockWrite, bufferBlock);
      sizeInt2 = sizeInt2 - escribir;
      position += escribir;
      inicioBlock += sizeInt2;
    }
    int nextBlock = 0;
    memcpy(&nextBlock,&bufferBlock[4096 - sizeof(int)],sizeof(int));
    if (nextBlock <= 0 && i < writePositioBlock-1)
    {
      nextBlock = allocateBlock();
      memcpy( &bufferBlock[4096 - sizeof(int)],&nextBlock, sizeof(int));
      this->disk->writeBlock(initialblockWrite, bufferBlock);
    }
    initialblockWrite = nextBlock;
    }
  file->size += size;
  file->save();
  delete bufferBlock;
  delete path;
  delete file;
  delete directory;
  delete superBlock;
}
void FS::readFile(const char *name, int position, void *buffer, int size){
  SuperBlock *superBlock = new SuperBlock(this->disk);
  Directory *directory = new Directory(this->disk, superBlock->Blockroot);
  int acumulado = 0, inicio = 0, block = 0;
  char *path = (char *)malloc(0);
  memset(&path[0], 0, strlen(path));
  while (acumulado < strlen(name))
  {
    acumulado = split(name, acumulado + 1);
    strncpy(&path[0], &name[inicio], acumulado - inicio);
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
    memset(&path[0], 0, strlen(path));
  }
  File *file = new File(this->disk, block);
  int initialblockWrite = file->head;
   int writePositioBlock = std::ceil(+((position + size) / (4096.0 - sizeof(int))));
  char *bufferBlock = (char *)malloc(4096);
  int inicioBlock = 0;
  int sizeInt2 = size;
  for (int i = 0; i < writePositioBlock; i++)
  {
    this->disk->readBlock(initialblockWrite, bufferBlock);
    if (((position) >= (i * 4096)) && ((position + sizeInt2) < (((i + 1) * 4096) - sizeof(int))))
    {
      this->disk->readBlock(initialblockWrite, bufferBlock);
      memcpy (&((char *)buffer)[inicioBlock],&bufferBlock[position - (i * 4092)], sizeInt2);
    }
    else if (((position) < ((i + 1) * 4096) - sizeof(int)) && ((position) > (i * 4092)) && ((position + sizeInt2) > ((i + 1) * 4096) - sizeof(int)))
    {
      int leer = (((i + 1) * 4096) - sizeof(int)) - position;
      this->disk->readBlock(initialblockWrite, bufferBlock);
      memcpy(&((char *)buffer)[inicioBlock], &bufferBlock[position - (i * 4092)], sizeInt2);
      sizeInt2 = sizeInt2 - leer;
      position += leer;
      inicioBlock += sizeInt2;
    }
    int nextBlock = 0;
    memcpy(&nextBlock, &bufferBlock[4096 - sizeof(int)], sizeof(int));
    initialblockWrite = nextBlock;

  }
  delete bufferBlock;
  delete path;
  delete file;
  delete directory;
  delete superBlock;
}
void FS::rm(const char *name)
{
  
}