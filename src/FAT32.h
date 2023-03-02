#pragma once

#include <vector>
#include "FileSystem.h"
#include "Disk.h"
#include "Utils.cpp"
#include "Entry.h"
#include "FAT32BootSector.h"
#include "FAT.h"
#include "RDET.h"

class FAT32 : public FileSystemInterface
{
private:
    Disk* disk;
    FAT32BootSector Boot_Sector;
    // FAT File_Allocation_Table;
    // RDET Root_Directory;
    
    // Entry RootEntry;

public:
    FAT32();
    FAT32(LPCWSTR);
    ~FAT32();

public:
    string Type ();
    void Show_Partition_Info();
    void Show_Txt();
    void Show_Current_Directory();
    void Enter_Child_Directory();
    void Return_Parent_Directory();

private:

};

FAT32::FAT32(LPCWSTR drive)
{
    disk = Disk::create(drive);
}

FAT32::FAT32()
{
    disk = Disk::create(L"////.//E:");
}

FAT32::~FAT32()
{
    delete disk;
}
