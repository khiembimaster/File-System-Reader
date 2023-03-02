#pragma once

#include <sstream>
#include "Disk.h"

#include "BootSector.h"
class BootSector;

class FAT32BootSector: public BootSector 
{
public:
    static const int SECTORS_PER_FAT_OFFSET = 0x24;
    static const int ROOT_DIR_FIRST_CLUSTER_OFFSET = 0x2C;
    static const int RESERVED_SECTORS_OFFSET = 14;
    static const int TOTAL_SECTORS_32_OFFSET = 32;

public:
    FAT32BootSector();
    FAT32BootSector(Disk* device);

public:
    long getBytesPerSector();
    long getSectorsPerCluster();
    std::string getType();
    std::string toString();

public:
    long getSectorsPerFat();
    long getSectorCount();
    long getNrReservedSectors();
    long getRootDirFirstCluster();
    long getFatOffset(int fatNr);
    
};
