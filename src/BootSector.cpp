#include "BootSector.h"
#include "FAT32BootSector.h"
#include <iostream>

class FAT32BootSector;
BootSector::BootSector(){}

std::shared_ptr<BootSector> BootSector::read(std::shared_ptr<Disk> device)
{
    BYTE* bb = new BYTE [512];
    device->read(0, bb, 512);
    if((bb[510]& 0xff) != 0x55 || (bb[511]& 0xff) != 0xAA)
    {
        throw ("Missing boot sector signature!");
    }
    else std::cout << "Im a boot sector";

    std::shared_ptr<BootSector> result;
    if(bb[FAT_COUNT_OFFSET] == 0)
    {
        // result = new NTFSBootSector(device);
    }
    else if(0 < bb[FAT_COUNT_OFFSET] <= 2)
    {
        result =  std::make_shared<FAT32BootSector>(device);
    }
    else throw("To much fats ?");

    result->Sector::read();
    return result;
}

BootSector::BootSector(std::shared_ptr<Disk> device):Sector(device, 0, SIZE){}

BootSector::~BootSector(){}