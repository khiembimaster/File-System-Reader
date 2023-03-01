#pragma once

#include "Utils.cpp"

class FAT
{
private:
    BYTE* Buffer;
public:
    void Init(LPCWSTR, DWORD, size_t);
    FAT(/* args */);
    ~FAT();

public:
    int64_t ReadFAT(int);
};

void FAT::Init(LPCWSTR drive, DWORD start, size_t size)
{
    Buffer = new BYTE [size];
    ReadSector(drive, start, Buffer, size);
}

int64_t FAT::ReadFAT(int offset)
{
    return ReadBytes(Buffer, offset, 4);
}

FAT::FAT(/* args */)
{
}

FAT::~FAT()
{
    delete [] Buffer;
}
