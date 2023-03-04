#include "Disk.h"


void Disk::read(long offset, BYTE* dest, size_t size)
{
    
    if(this == nullptr)
        return;

    DWORD bytesRead;

    SetFilePointer(device, offset, NULL, FILE_BEGIN);//Set a Point to Read

    if (!ReadFile(device, dest, size, &bytesRead, NULL))
    {
        std::cout << "ReadFile: " << GetLastError() << std::endl;
    }
    else
    {
        std::cout << "Success!" << std::endl;
    }
}

Disk* Disk::create(LPCWSTR drive)
{
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
        std::cout << "CreateFile: " << GetLastError() << std::endl;
        return nullptr;
    }
    else {
        std::cout << "CreateFile Succeeded " << std::endl;
        return new Disk(drive, device);
    }
}

DWORD Disk::getSize()
{
    if(this == nullptr)
        return 0;
    DWORD size = GetFileSize( this->device, NULL);
    if(size == INVALID_FILE_SIZE) // Get size error
    {
        std::cout << "GetFileSize: " << GetLastError() << std::endl;
        return 0;
    }
    return size;
}

Disk::Disk() {}

Disk::Disk(LPCWSTR drive, HANDLE device): drive{drive}, device{device} {}

// int main()
// {
//     Disk* disk= Disk::create(L"\\\\.\\E:");
//     std::cout << disk->getSize();
    
//     BYTE* buffer = new BYTE [512];
//     disk->read(0, buffer, 512);
//     std::wcout << buffer;
//     delete disk;
//     delete [] buffer;
//     system("pause");
// }