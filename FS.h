#ifndef FS_H
#define FS_H
#include <stdio.h>


#include <stdlib.h>
#include <cmath>
#include <string.h>
#include "Disk.h"
#include "FS.h"
#include "Bitmap.h"
#include "SuperBlock.h"
#include "Directory.h"
#include "File.h"

class FS{
   Disk * disk;
public:
    FS(Disk * disk);
    void format();
    unsigned int allocateBlock();
    void freeBlock(unsigned int numberBlock);
    void mkdir(const char *name);
    void ls(const char *name);
    void rm(const char *name);
    void createFile(const char * name);
    void deleteFile(const char * name);
    void writeFile(const char *name,int position,void *buffer,int size);
    void readFile(const char *name, int position, void *buffer, int size);
    unsigned int getSizeFile(const char *name);
    unsigned int getTotalFreeBlock();
    void printfBlockAllocate();

};

#endif