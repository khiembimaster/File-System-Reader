#pragma once

#include <string>
#include <sstream>
#include "Disk.h"
#include "BootSector.h"


class FAT32BootSector: public BootSector{
public:
    static const int SECTORS_PER_FAT_OFFSET = 0x24;
    static const int ROOT_DIR_FIRST_CLUSTER_OFFSET = 0x2C;
    static const int RESERVED_SECTORS_OFFSET = 14;
    static const int TOTAL_SECTORS_32_OFFSET = 32;

public:
    FAT32BootSector(){}
    FAT32BootSector(Disk* device);
    ~FAT32BootSector(){}
public:
    long getBytesPerSector();
    long getSectorsPerCluster();
    std::string getType();
    std::string toString();

public:
    long getSectorsPerFat();
    long getSectorCount();
    long getNrReservedSectors();
    long getNrFats();
    long getRootDirFirstCluster();
    long getFatOffset(int fatNr);
    
    long getFilesOffset();
    long getRootDirOffset();

    int getBytesPerCluster();
    long getDataClusterCount();
    
private:
    long getDataSize();
};

