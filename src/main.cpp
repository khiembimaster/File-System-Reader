#include <FileSystem.h>
#include <FAT32.h>
#include <NTFS.h>

int main()
{
    
    FileSystemInterface* fs = new FAT32(L"\\\\.\\C:");
    fs->Show_Partition_Info();
    fs->Show_Current_Directory();
    delete fs;
}   