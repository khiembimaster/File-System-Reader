#pragma once
#include "FAT.h"
#include "Disk.h"
class ClusterChain
{
private:
    FAT* fat;
    Disk* device;
    int clusterSize;
    long dataOffset;

    long startCluster;
public:
    ClusterChain(FAT*);
    ClusterChain(FAT*, long);

public:
    int getClusterSize();
    FAT* getFat();
    Disk* getDevice();
    long getStartCluster();
    long getLengthOnDisk();
    int getChainLength();

    void readData(long, BYTE*, int);
private:
    long getDevOffset(long, int);
};
