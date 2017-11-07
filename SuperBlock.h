#ifndef SUPERBLOCK_H
#define SUPERBLOCK_H

#include "Disk.h"
class SuperBlock{
    Disk *disk;
    char *buffer;  
public:
    int bitMapBlockSize;
    int BlockFree;
    int Blockroot;
    SuperBlock(Disk *disk);
    void save();
};

#endif