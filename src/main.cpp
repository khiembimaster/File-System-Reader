//#include <FileSystem.h>
// #include "FAT32.h"
#include "Disk.h"
//#include <NTFS.h>


int main()
{
    Disk* usb = Disk::create(L"\\\\.\\E:");
    
    // FAT32* p = FAT32::read(usb);
    
    delete usb;
    
    system("pause");
}