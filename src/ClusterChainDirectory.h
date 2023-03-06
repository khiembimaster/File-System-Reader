#pragma once
#include <memory>
#include "ClusterChain.h"
#include "AbstractDirectory.h"
#include "FatDirectoryEntry.h"

class ClusterChainDirectory : public AbstractDirectory
{
public:
    static const int MAX_SIZE = 65536 * 32;
    std::shared_ptr<ClusterChain> chain;

    static std::shared_ptr<ClusterChainDirectory> readRoot(std::shared_ptr<ClusterChain> chain);

    ClusterChainDirectory(std::shared_ptr<ClusterChain> chain, bool isRoot);
    void read(BYTE* data, int size);
    long getStorageCluster();
};

