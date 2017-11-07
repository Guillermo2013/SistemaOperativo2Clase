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

class FS{
   Disk * disk;
public:
    FS(Disk * disk);

    void format();
    unsigned int allocateBlock();
    void freeBlock(unsigned int numberBlock);
    void mkdir(const char * path);
    void ls(const char * path);
    unsigned int getTotalFreeBlock();
    void printfBlockAllocate();

};

#endif