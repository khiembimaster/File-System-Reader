#pragma once

#include <Windows.h>
#include <fstream>
#include <iostream>
#include <memory>
class Disk
{
public:
    static const int BYTES_PER_SECTOR = 512;

private:
    LPCWSTR drive = L"\\\\.\\E:";
    HANDLE device;
    // std::istream file_stream;

    
    Disk();
public:
    Disk(LPCWSTR, HANDLE);
    static std::shared_ptr<Disk> create(LPCWSTR);
    DWORD getSize();
    void read(long, BYTE*, DWORD);
};
