#include "FAT.h"
#include <exception>


FAT::FAT(/* args */){}
FAT::~FAT(){}

FAT* FAT::read(FAT32BootSector* bs, int fatNr)
{
    if(fatNr > bs->getNrFats())
    {
        throw ("Invalid fat num!");
    }

    long fatOffset = bs->getFatOffset(fatNr);
    FAT* result = new FAT(bs, fatOffset);
    result->read();
    return result;
}

FAT::FAT(FAT32BootSector* bs, long offset) {
    this->bs = bs;

    this->sectorCount = (int) bs->getSectorsPerFat();
    this->sectorSize = bs->getBytesPerSector();
    this->device = bs->getDevice();
    this->offset = offset;
    this->lastAllocatedCluster = FIRST_CLUSTER;
    
    this->lastClusterIndex = (int) bs->getDataClusterCount() + FIRST_CLUSTER;

    entries.resize((int) ((sectorCount * sectorSize) / 4));
            
    std::stringstream err;
    err << "file system has " << this->lastClusterIndex <<
        "clusters but only " << entries.size() << " FAT entries";

    if (lastClusterIndex > entries.size()) throw (err);
}

void FAT::read() {
    BYTE* data = new BYTE [sectorCount * sectorSize];
    device->read(offset, data, sectorCount * sectorSize);

    for (int i = 0; i < entries.size(); i++)
        entries[i] = this->readEntry(data, i);
}

long FAT::readEntry(BYTE* data, int index)
{
    int idx = index * 4;
    long result = 0;
    memcpy (&result, data + idx, 4);
    return result;
}


long FAT::getEntry(int index)
{
    return (int) (entries[0] & 0xFF);
}

int FAT::getLastFreeCluster()
{   
    return this->lastAllocatedCluster;
}
std::vector<long> FAT::getChain(long startCluster)
{
    try{
        testCluster(startCluster);
    }catch(std::exception e){
        std::cout << e.what();
        return ;
    }

    int count = 1;
    long cluster = startCluster;
    std::vector<long> chain;
    while (!isEofCluster(entries[(int) cluster])) {
        count++;
        cluster = entries[(int) cluster];
        chain.push_back(cluster);
    }

    return chain;
}
void FAT::testCluster(long cluster)
{
    std::stringstream err;
    err << "invalid cluster value " + cluster;
    if ((cluster < FIRST_CLUSTER) || (cluster >= entries.size())) {
        throw (err);
    }
}

boolean FAT::isEofCluster(long entry)
{
    return (entry >= 0x0FFFFFF8);
}

long FAT::getNextCluster(long cluster)
{
    try{
        testCluster(cluster);
    }catch(std::exception e){
        std::cout << e.what();
        return ;
    }

    long entry = entries[(int) cluster];
    if (isEofCluster(entry)) {
        return -1;
    } else {
        return entry;
    }
}
int FAT::getFreeClusterCount()
{
    int result = 0;
    for (int i=FIRST_CLUSTER; i < lastClusterIndex; i++) {
        try {
            if (isFreeCluster(i)) result++;
        }catch (std::exception e){
            return -1;
        }
    }
    return result;
}

boolean FAT::isFreeCluster(long entry) {
    if (entry > INT_MAX) throw ("Out of range");
    return (entries[(int) entry] == 0);
}

int FAT::getLastAllocatedCluster()
{
    return this->lastAllocatedCluster;
}