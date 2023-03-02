#pragma once

#include "Disk.h"
class Sector {
private:
    Disk* device;
    long offset;
    int size = 0;
protected:
    BYTE* buffer;
    Sector() {}

    Sector(Disk* device, long offset, int size)
    {
        this->device = device;
        this->offset = offset;
        this->size = size;
        this->buffer = new BYTE [size];
    }

    virtual ~Sector()
    {
        delete[] buffer;
    }

    void read()
    {
        device->read(offset, buffer, size);
    }

    int64_t getNum(int offset, int number)
    {
        int64_t result = 0;
        memcpy(&result, buffer + offset, number);
        return result;
    }

    long getOffset()
    {
        return this->offset;
    }

public:
    Disk* getDevice()
    {
        return this->device;
    }


};