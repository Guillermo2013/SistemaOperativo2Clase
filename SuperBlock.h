#ifndef SUPERBLOCK_H
#define SUPERBLOCK_H

#include "Disk.h"
class SuperBlock{
    Disk *disk;
    char *buffer;  
public:
    int bitMapBlockSize;
    int BlockFree;
    SuperBlock(Disk *disk);
    ~SuperBlock();
    void save();
};

#endif