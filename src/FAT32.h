#pragma once

#include <vector>
#include "FileSystem.h"
#include "Utils.cpp"
#include "Entry.h"
#include "FAT32BootSector.h"
#include "FAT.h"
#include "RDET.h"

class FAT32 : public FileSystemInterface
{
private:
    LPCWSTR drive;
    FAT32BootSector Boot_Sector;
    FAT File_Allocation_Table;
    RDET Root_Directory;
    
    Entry RootEntry;

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
    bool Init();
};

bool FAT32::Init() {

    // Update volume info
    Boot_Sector.Init(this->drive);
    // size_t fat_size = Boot_Sector.Numbers_Of_Fats() * Boot_Sector.Sectors_Per_FAT();
    File_Allocation_Table.Init(this->drive, Boot_Sector.START_OF_FAT1(), Boot_Sector.Sectors_Per_FAT());
    Root_Directory.Init(this->drive, Boot_Sector.START_OF_RDET(), 512);
    
    return 1;
}

FAT32::FAT32(LPCWSTR drive)
{
    this->drive = drive;
    Init();
}

FAT32::FAT32()
{
    this->drive = L"////.//E:";
    Init();
}

FAT32::~FAT32()
{
}
