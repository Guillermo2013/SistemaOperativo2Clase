#ifndef FILE_H
#define FILE_H

#include "Disk.h"

class File
{
    Disk *disk;

  public:
    char *buffer;
    int block;
    int size;
    char *name;
    int head;
    File(Disk *disk, int Block); 
    void save();
};

#endif
