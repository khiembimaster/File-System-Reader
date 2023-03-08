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



