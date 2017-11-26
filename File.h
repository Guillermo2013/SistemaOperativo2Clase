#ifndef FILE_H
#define FILE_H

#define directorySize 128
#define sizeChar sizeof(char)
#define sizeInt sizeof(int)
#define sizeName (directorySize - sizeChar - sizeInt)

#include "Disk.h"

class File
{
    Disk *disk;
  public:
    char buffer[4096];
    int block;
    int size;
    char name[sizeName];
    int head;
    File(Disk *disk, int Block); 
    void save();
};

#endif
