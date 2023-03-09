#pragma once
#include "FAT.h"
#include "Disk.h"
#include <memory>
class ClusterChain
{
private:
    std::shared_ptr<FAT> fat;
    std::shared_ptr<Disk> device;
    int clusterSize;
    

    long startCluster;
public:
    long dataOffset;
    ClusterChain(std::shared_ptr<FAT>);
    ClusterChain(std::shared_ptr<FAT>, long);

public:
    int getClusterSize();
    std::shared_ptr<FAT> getFat();
    std::shared_ptr<Disk> getDevice();
    long getStartCluster();
    long getLengthOnDisk();
    int getChainLength();

    void readData(long, BYTE*, int);
private:
    long getDevOffset(long, int);
};
