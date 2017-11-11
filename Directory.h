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

};
class Directory{
    Disk * disk;
    unsigned int block;
 public:    
    char buffer[4096];
    DirectoryEntry  directoryEntry[32];
    Directory(Disk * disk,unsigned int Block);
    void save();
};

#endif
