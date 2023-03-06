#include "ClusterChain.h"
#include <algorithm>
#include <sstream>

ClusterChain::ClusterChain(std::shared_ptr<FAT>)
{
    ClusterChain(fat, 0);
}
ClusterChain::ClusterChain(std::shared_ptr<FAT> fat, long startCluster)
{
    this->fat = fat;

    if(startCluster != 0)
    {
        this->fat->testCluster(startCluster); // catch err here ?

        std::stringstream err;
        err << "cluster " << startCluster << " is free";
        if(this->fat->isFreeCluster(startCluster)) throw (err.str());
    }

    this->device = fat->getDevice();
    this->dataOffset = fat->getBootSector()->getFilesOffset();
    this->startCluster = startCluster;
    this->clusterSize = fat->getBootSector()->getBytesPerCluster();
}


int ClusterChain::getClusterSize() {
    return clusterSize;
}

std::shared_ptr<FAT> ClusterChain::getFat() {
    return fat;
}

std::shared_ptr<Disk> ClusterChain::getDevice() {
    return device;
}

long ClusterChain::getStartCluster() {
    return startCluster;
}

long ClusterChain::getDevOffset(long cluster, int clusterOffset) {
    return dataOffset + clusterOffset +
            ((cluster - fat->FIRST_CLUSTER) * clusterSize);
}

long ClusterChain::getLengthOnDisk() {
    if (getStartCluster() == 0) return 0;
    long result = getChainLength() * clusterSize; 
    return result;
}

int ClusterChain::getChainLength() {
    if (getStartCluster() == 0) return 0;
    
    std::vector<long> chain = getFat()->getChain(getStartCluster());
    return chain.size();
}

void ClusterChain::readData(long offset, BYTE* dest, int len)
{

    // int len = dest.remaining();
    // BYTE* = 

    if ((startCluster == 0 && len > 0)) {
        throw ("cannot read from empty cluster chain");
    }
    
    std::vector<long> chain = getFat()->getChain(startCluster);
    std::shared_ptr<Disk> dev = getDevice();

    int chainIdx = (int) (offset / clusterSize);
    
    if (offset % clusterSize != 0) {
        int clusOfs = (int) (offset % clusterSize);
        int temp = (int) (clusterSize - (offset % clusterSize)) ;
        const int size = (len < temp) ? len : temp;
        // dest.limit(dest.position() + size);

        dev->read(getDevOffset(chain[chainIdx], clusOfs), dest, size);
        
        len -= size;
        chainIdx++;
    }

    while (len > 0) {
        const int size = (len < clusterSize) ? len : clusterSize;
        // dest.limit(dest.position() + size);

        dev->read(getDevOffset(chain[chainIdx], 0), dest, size);

        len -= size;
        chainIdx++;
    }
}