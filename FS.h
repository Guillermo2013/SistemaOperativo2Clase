#ifndef FS_H
#define FS_H

#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <string.h>

#include "Disk.h"
class FS{
   Disk * disk;
public:
    FS(Disk * disk);
    void format();
    unsigned int allocateBlock();
    void freeBlock(unsigned int numberBlock);
    unsigned int getTotalFreeBlock();
};

#endif