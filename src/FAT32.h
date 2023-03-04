#pragma once

#include <vector>
#include "FileSystem.h"
#include "Disk.h"
#include "FAT32BootSector.h"
#include "FAT.h"
#include "FatLfnDirectory.h"

// #include ""
class FAT32
{
private:
    FAT* fat;
    FAT32BootSector* bs;
    FatLfnDirectory* rootDir;
    AbstractDirectory* rootDirStore;
    long filesOffset;

public:
    FAT32(Disk* api);
    ~FAT32();

    static FAT32* read(Disk* device);

    long getFilesOffset();
    std::string getVolumeLabel();
    AbstractDirectory* getRootDirStore();
    FatLfnDirectory* getRoot();
    FAT* getFat();
    BootSector* getBootSector();

public:
    // string Type ();
    // void Show_Partition_Info();
    // void Show_Txt();
    // void Show_Current_Directory();
    // void Enter_Child_Directory();
    // void Return_Parent_Directory();

};

FAT32::FAT32(Disk* device)
{
    this->bs =(FAT32BootSector*) BootSector::read(device);
    if(bs->getNrFats() <= 0) throw ("boot sector says there are no FATs");

    this->filesOffset = bs->getFilesOffset(); 
    this->fat = FAT::read(this->bs, 0);
    
    ClusterChain* rootChain = new ClusterChain(fat,
            this->bs->getRootDirFirstCluster());
    this->rootDirStore = ClusterChainDirectory::readRoot(rootChain);
    
    this->rootDir = new FatLfnDirectory(rootDirStore, fat);
}

FAT32* FAT32::read(Disk* device)
{
    return new FAT32(device);
}

long FAT32::getFilesOffset()
{
    return filesOffset;
}

std::string FAT32::getVolumeLabel()
{
    std::string fromDir = rootDirStore->getLabel();
    return fromDir;
}

AbstractDirectory* FAT32::getRootDirStore()
{
    return rootDirStore;
}

FatLfnDirectory* FAT32::getRoot()
{
    return rootDir;
}

FAT* FAT32::getFat()
{
    return fat;
}

BootSector* FAT32::getBootSector()
{
    return bs;
}


