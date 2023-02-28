#pragma once

#include <vector>
#include "FileSystem.h"
#include "Utils.cpp"



class FAT32 : public FileSystemInterface
{
private:
    LPCWSTR drive;
    WORD bytes_per_sector;
    BYTE sectors_per_cluster;
    WORD sectors_of_bootsector;
    BYTE numbers_of_fats;
    WORD sector_of_RDET;
    WORD sector_per_FAT;
    unsigned int first_sector_of_data;

    BYTE* Boot_Sector;
    BYTE* File_Allocation_Table;
    
    // std::<Entry> 

public:
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
    void Read_Boot_Sector();
    void Read_RDET();
    void Read_FAT();
};

FAT32::FAT32(LPCWSTR drive)
{
    this->drive = drive;
}

FAT32::~FAT32()
{
    delete[] File_Allocation_Table;
    delete[] Boot_Sector;
}
