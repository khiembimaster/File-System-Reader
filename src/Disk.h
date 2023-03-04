#pragma once

#include <Windows.h>
#include <fstream>
#include <iostream>

class Disk
{
public:
    static const int BYTES_PER_SECTOR = 512;

private:
    LPCWSTR drive = L"\\\\.\\E:";
    HANDLE device;
    // std::istream file_stream;

    Disk(LPCWSTR, HANDLE);
    Disk();
public:
    static Disk* create(LPCWSTR);
    DWORD getSize();
    void read(long, BYTE*, size_t);
};
