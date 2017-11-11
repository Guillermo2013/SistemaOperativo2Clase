#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "Disk.h"

#define directorySize 128
#define sizeChar sizeof(char)
#define sizeInt sizeof(int)
#define sizeName directorySize -sizeChar-sizeInt

class DirectoryEntry{
public:
    char nombre[sizeName];
    char typeDirectory;
    int block;
    char buffer[128];
    DirectoryEntry(char*buffer);
    void save();
};
class Directory{
    Disk * disk;
    
 public:    
    char buffer[4096];
     int block;
    DirectoryEntry  *directoryEntry[32];
    Directory(Disk * disk, int Block);
    void format();
    void save();
};

#endif
