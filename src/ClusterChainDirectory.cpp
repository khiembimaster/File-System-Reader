#include "ClusterChainDirectory.h"

ClusterChainDirectory::ClusterChainDirectory(std::shared_ptr<ClusterChain> chain, bool isRoot): 
    AbstractDirectory((int) chain->getLengthOnDisk() / FatDirectoryEntry::SIZE, isRoot)
{
    this->chain = chain;
}

std::shared_ptr<ClusterChainDirectory> ClusterChainDirectory::readRoot(std::shared_ptr<ClusterChain> chain)
{
    std::shared_ptr<ClusterChainDirectory> result = std::make_shared<ClusterChainDirectory>(chain, true);
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
