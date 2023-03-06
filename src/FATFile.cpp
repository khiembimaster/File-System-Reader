
#include "FATFile.h"
FATFile::FATFile(std::shared_ptr<FatDirectoryEntry> myEntry, std::shared_ptr<ClusterChain> chain)
{
    this->entry = myEntry;
    this->chain = chain;
}

std::shared_ptr<FATFile> FATFile::get(std::shared_ptr<FAT> fat, std::shared_ptr<FatDirectoryEntry> entry)
{
    std::shared_ptr<ClusterChain> cluster_chain = std::make_shared<ClusterChain>(fat, entry->getStartCluster());

    std::stringstream err;
    err << "entry (" << entry->getLength() 
        << ") is larger than associated cluster chain ("
        << cluster_chain->getLengthOnDisk() << ")";
    
    std::shared_ptr<FATFile> result = std::make_shared<FATFile>(entry, cluster_chain); 
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

std::shared_ptr<ClusterChain> FATFile::getChain()
{
    return chain;
}

FATFile::~FATFile(){
}
