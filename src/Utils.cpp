#pragma once
#include <windows.h>

#include <iostream>
using namespace std;

bool ReadSector(LPCWSTR  drive, int readPoint, BYTE* sector, size_t size)
{
    int retCode = 0;
    DWORD bytesRead;
    HANDLE device = NULL;

    device = CreateFileW(drive,    // Drive to open
        GENERIC_READ,           // Access mode
        FILE_SHARE_READ | FILE_SHARE_WRITE,        // Share Mode
        NULL,                   // Security Descriptor
        OPEN_EXISTING,          // How to create
        0,                      // File attributes
        NULL);                  // Handle to template

    if (device == INVALID_HANDLE_VALUE) // Open Error
    {
        cout << "CreateFile: " << GetLastError() << endl;
        return 0;
    }

    SetFilePointer(device, readPoint, NULL, FILE_BEGIN);//Set a Point to Read

    if (!ReadFile(device, sector, size, &bytesRead, NULL))
    {
        cout << "ReadFile: " << GetLastError() << endl;
        return 0;
    }
    else
    {
        cout << "Success!" << endl;
    }

    return 1;
}

int64_t ReadBytes(BYTE* sector, int offset, int number)
{
    int64_t result = 0;
    memcpy(&result, sector + offset, number);
    return result;
}

string Get_String(BYTE* DATA, int offset, int number)
{
    char* tmp = new char[number + 1];
    memcpy(tmp, DATA + offset, number);
    string s = "";
    for (int i = 0; i < number; i++)
        if (tmp[i] != 0x00 && tmp[i] != 0xFF)
            s += tmp[i];
    return s;
}

int main(int argc, char ** argv)
{
    
    BYTE sector[512];
    ReadSector(L"\\\\.\\C:",0, sector, 512);
    return 0;
}