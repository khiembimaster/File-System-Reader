#pragma once

#include <vector>
#include "Utils.cpp"
#include "Entry.h"

class RDET
{
private:
    BYTE* Buffer;

    std::vector<Entry> directory;
public:
    void Init(LPCWSTR, int, size_t);
    RDET(/* args */);
    ~RDET();
};


void RDET::Init(LPCWSTR drive, int readpoint, size_t size)
{
    Buffer = new BYTE [size];
    ReadSector(drive, readpoint, Buffer, size);

    while(true){
        switch (ReadBytes(Buffer, 0x0B, 1))
        {
        case 0x00:
            return;
        case 0x0F:
            /* code */
            break;
        case 0x01:
            /* code */
            break;
        
        default:
            break;
        }
    }

}

RDET::RDET(/* args */)
{
}

RDET::~RDET()
{
    delete [] Buffer;
}
