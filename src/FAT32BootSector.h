#pragma once
#include "Utils.cpp"

class FAT32BootSector
{
private:

    WORD bytes_per_sector;
    BYTE sectors_per_cluster;
    WORD sectors_of_bootsector;
    BYTE numbers_of_fats;
    DWORD sectors_of_Volume; 
    DWORD sectors_per_FAT;
    DWORD first_cluster_of_RDET;

    BYTE* Buffer;

public:
    WORD Byte_Per_Sector();
    BYTE Sectors_Per_Cluster();
    WORD Sectors_Of_Bootsector();
    BYTE Numbers_Of_Fats();
    DWORD Sectors_Of_Volume(); 
    DWORD Sectors_Per_FAT();
    DWORD First_Cluster_Of_RDET();
    
    int START_OF_FAT1();
    int START_OF_RDET();
    int START_OF_DATA();

    void Init(LPCWSTR);
public:
    FAT32BootSector();
    ~FAT32BootSector();
};

int FAT32BootSector::START_OF_FAT1()
{
    return sectors_of_bootsector + 1; // +1 ?
}

int FAT32BootSector::START_OF_DATA()
{
    return START_OF_FAT1() + sectors_per_FAT * numbers_of_fats;
}

int FAT32BootSector::START_OF_RDET()
{
    return first_cluster_of_RDET * sectors_per_cluster * bytes_per_sector;
}



WORD FAT32BootSector::Byte_Per_Sector()
{
    return bytes_per_sector;
}

BYTE FAT32BootSector::Sectors_Per_Cluster()
{
    return sectors_per_cluster;
}
WORD FAT32BootSector::Sectors_Of_Bootsector()
{
    return sectors_of_bootsector;
}
BYTE FAT32BootSector::Numbers_Of_Fats()
{
    return numbers_of_fats;
}
DWORD FAT32BootSector::Sectors_Of_Volume()
{
    return sectors_of_Volume;
}
DWORD FAT32BootSector::Sectors_Per_FAT()
{
    return sectors_per_FAT;
}
DWORD FAT32BootSector::First_Cluster_Of_RDET()
{
    return first_cluster_of_RDET;
}


void FAT32BootSector::Init(LPCWSTR drive) 
{
    Buffer = new BYTE [512];
    bool result = ReadSector(drive, 0, Buffer, 512);
    
    if(result){
        if(ReadBytes(Buffer, 0x1FE, 2) == 43605){
            bytes_per_sector = ReadBytes(Buffer, 0xB, 2);
            sectors_per_cluster = ReadBytes(Buffer, 0xD, 1);
            sectors_of_bootsector = ReadBytes(Buffer, 0xE, 2);
            numbers_of_fats = ReadBytes(Buffer, 0x10 , 1);
            sectors_of_Volume = ReadBytes(Buffer, 0x20, 4); 
            sectors_per_FAT = ReadBytes(Buffer, 0x24, 4);
            first_cluster_of_RDET = ReadBytes(Buffer, 0x2C, 4);
        }
    }
}

FAT32BootSector::FAT32BootSector()
{
}

FAT32BootSector::~FAT32BootSector()
{
    delete[] Buffer;
}
