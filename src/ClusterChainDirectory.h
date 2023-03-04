#pragma once

#include "ClusterChain.h"
#include "AbstractDirectory.h"
#include "FatDirectoryEntry.h"

class ClusterChainDirectory : public AbstractDirectory
{
public:
    static const int MAX_SIZE = 65536 * 32;
    ClusterChain* chain;

    static ClusterChainDirectory* readRoot(ClusterChain* chain);

    ClusterChainDirectory(ClusterChain* chain, bool isRoot);
    void read(BYTE* data, int size);
    long getStorageCluster();
};

