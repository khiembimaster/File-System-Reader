#pragma once

#include <vector>
// #include "FileSystem.h"
#include <memory>
#include "Disk.h"
#include "FAT32BootSector.h"
#include "FAT.h"
#include "AbstractDirectory.h"
#include "ClusterChainDirectory.h"
#include "ClusterChain.h"
#include "FatLfnDirectory.h"

// #include ""
class FAT32
{
private:
    std::shared_ptr<FAT> fat;
    std::shared_ptr<FAT32BootSector> bs;
    std::shared_ptr<FatLfnDirectory> rootDir;
    std::shared_ptr<AbstractDirectory> rootDirStore;
    long filesOffset;

public:
    FAT32(std::shared_ptr<Disk> api);
    ~FAT32(){
    }

    static std::shared_ptr<FAT32> read(std::shared_ptr<Disk> device);

    long getFilesOffset();
    std::string getVolumeLabel();
    std::shared_ptr<AbstractDirectory> getRootDirStore();
    std::shared_ptr<FatLfnDirectory> getRoot();
    std::shared_ptr<FAT> getFat();
    std::shared_ptr<BootSector> getBootSector();

public:
    // string Type ();
    // void Show_Partition_Info();
    // void Show_Txt();
    // void Show_Current_Directory();
    // void Enter_Child_Directory();
    // void Return_Parent_Directory();

};

FAT32::FAT32(std::shared_ptr<Disk> device)
{
    
    this->bs = std::dynamic_pointer_cast<FAT32BootSector>(BootSector::read(device));
    if(bs->getNrFats() <= 0) throw ("boot sector says there are no FATs");

    this->filesOffset = bs->getFilesOffset(); 
    this->fat = FAT::read(this->bs, 0);
    
    std::shared_ptr<ClusterChain> rootChain = std::make_shared<ClusterChain>(fat,
            this->bs->getRootDirFirstCluster());
    this->rootDirStore = ClusterChainDirectory::readRoot(rootChain);
    
    this->rootDir = std::make_shared<FatLfnDirectory>(rootDirStore, fat);
}

std::shared_ptr<FAT32> FAT32::read(std::shared_ptr<Disk> device)
{
    return std::make_shared<FAT32>(device);
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

std::shared_ptr<AbstractDirectory> FAT32::getRootDirStore()
{
    return rootDirStore;
}

std::shared_ptr<FatLfnDirectory> FAT32::getRoot()
{
    return rootDir;
}

std::shared_ptr<FAT> FAT32::getFat()
{
    return fat;
}

std::shared_ptr<BootSector> FAT32::getBootSector()
{
    return bs;
}


