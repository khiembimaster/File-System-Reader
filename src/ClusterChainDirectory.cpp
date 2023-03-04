#include "ClusterChainDirectory.h"

ClusterChainDirectory::ClusterChainDirectory(ClusterChain* chain, bool isRoot): 
    AbstractDirectory((int) chain->getLengthOnDisk() / FatDirectoryEntry::SIZE, isRoot)
{
    this->chain = chain;
}

ClusterChainDirectory* ClusterChainDirectory::readRoot(ClusterChain* chain)
{
    ClusterChainDirectory* result = new ClusterChainDirectory(chain, true);
    result->readb();
    return result;
}

void ClusterChainDirectory::read(BYTE* data, int size)
{
    this->chain->readData(0, data, size);
}

long ClusterChainDirectory::getStorageCluster() {
    return isRoot() ? 0 : chain->getStartCluster();
}
