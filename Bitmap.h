#ifndef BITMAP_H
#define BITMAP_H
#include "Disk.h"
class Bitmap{
    Disk * disk;
public :
    int size;
    char * buffer;
    Bitmap(Disk * disk);
    ~Bitmap(){
        delete this->buffer;            
        }
    void save();
    void setBit(int numberBit,bool value);
    bool getBit(int numberBit);
};
#endif
