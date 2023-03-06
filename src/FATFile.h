#pragma once
#include "FsFile.h"
#include "FatDirectoryEntry.h"
#include "ClusterChain.h"
#include "FAT.h"
#include <memory>
class FatDirectoryEntry;
class FATFile : public FsFile
{
private:
    std::shared_ptr<FatDirectoryEntry> entry;
    std::shared_ptr<ClusterChain> chain;
    
    FATFile();
public:
    FATFile(std::shared_ptr<FatDirectoryEntry> myEntry, std::shared_ptr<ClusterChain> chain);

    static std::shared_ptr<FATFile> get(std::shared_ptr<FAT> fat, std::shared_ptr<FatDirectoryEntry> entry);

    long getLength();
    void read(long offset, BYTE* dest, int size);
    std::shared_ptr<ClusterChain> getChain();
    // std::string toString();
    ~FATFile();
};



