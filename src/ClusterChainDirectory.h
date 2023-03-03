#pragma once

#include "ClusterChain.h"

class ClusterChainDirectory
{
public:
    static const int MAX_SIZE = 65536 * 32;
    const ClusterChain* chain;

    static ClusterChainDirectory* readRoot(ClusterChain* chain);

protected:
    ClusterChainDirectory(ClusterChain* chain, bool isRoot);
};