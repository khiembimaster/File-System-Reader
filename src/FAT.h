#pragma once

#include "BootSector.h"
#include "FAT32BootSector.h"
#include "Disk.h"
#include <vector>
#include <climits>
#include <memory>
class FAT
{
public:
    static const int FIRST_CLUSTER = 2;

private:
    std::vector<long> entries;
    int sectorCount;
    int sectorSize;
    std::shared_ptr<Disk> device;
    std::shared_ptr<FAT32BootSector> bs;
    long offset;
    int lastClusterIndex; 
    int lastAllocatedCluster;
public:
    FAT(/* args */);
    ~FAT();
private:
    
    void read();
public:
    FAT(std::shared_ptr<FAT32BootSector>, long);
    static std::shared_ptr<FAT> read(std::shared_ptr<FAT32BootSector>, int);
    long readEntry(BYTE*, int);

public:
    std::shared_ptr<Disk> getDevice();
    std::shared_ptr<FAT32BootSector> getBootSector();

    long getEntry(int);
    int getLastFreeCluster();
    std::vector<long> getChain(long startCluster);
    long getNextCluster(long cluster);
    int getFreeClusterCount();
    int getLastAllocatedCluster();



public:
    void testCluster(long);
    boolean isFreeCluster(long entry);
    // boolean isReservedCluster(long entry);
    boolean isEofCluster(long entry);
};


// boolean FAT::isReservedCluster(long entry) {
//     ((entry >= minReservedEntry) && (entry <= maxReservedEntry))
//     return fatType.isReservedCluster(entry);
// }



