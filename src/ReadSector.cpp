#include <windows.h>

#include <iostream>
using namespace std;

int ReadSector(LPCWSTR  drive, int readPoint, BYTE sector[512])
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

    if (!ReadFile(device, sector, 512, &bytesRead, NULL))
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

int main(int argc, char ** argv)
{
    
    BYTE sector[512];
    ReadSector(L"\\\\.\\C:",0, sector);
    return 0;
}