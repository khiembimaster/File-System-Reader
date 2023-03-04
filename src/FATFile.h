#pragma once
#include "FsFile.h"
#include "FatDirectoryEntry.h"
#include "ClusterChain.h"
#include "FAT.h"

class FatDirectoryEntry;
class FATFile : public FsFile
{
private:
    FatDirectoryEntry* entry;
    ClusterChain* chain;
    
    FATFile();
    FATFile(FatDirectoryEntry* myEntry, ClusterChain* chain);
public:
    static FATFile* get(FAT* fat, FatDirectoryEntry* entry);

    long getLength();
    void read(long offset, BYTE* dest, int size);
    ClusterChain* getChain();
    // std::string toString();
    ~FATFile();
};

FATFile::FATFile(FatDirectoryEntry* myEntry, ClusterChain* chain)
{
    this->entry = myEntry;
    this->chain = chain;
}

FATFile* FATFile::get(FAT* fat, FatDirectoryEntry* entry)
{
    ClusterChain* cluster_chain = new ClusterChain(fat, entry->getStartCluster());

    std::stringstream err;
    err << "entry (" << entry->getLength() 
        << ") is larger than associated cluster chain ("
        << cluster_chain->getLengthOnDisk() << ")";
    
    FATFile * result = new FATFile(entry, cluster_chain); 
    return result;
}

long FATFile::getLength()
{
    return entry->getLength();
}

void FATFile::read(long offset, BYTE* dest, int size)
{
    if (offset + size > getLength())
        throw ("Over flow");
    
    chain->readData(offset, dest, size);
}

ClusterChain* FATFile::getChain()
{
    return chain;
}

FATFile::~FATFile(){
    delete entry;
    delete chain;
}



