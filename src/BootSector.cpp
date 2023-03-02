#include "BootSector.h"

BootSector::BootSector(){}

BootSector* BootSector::read(Disk* device)
{
    BYTE* bb = new BYTE [512];
    device->read(0, bb, 512);

    if(bb[510] != 0x55 || bb[511] != 0xAA)
    {
        throw ("Missing boot sector signature!");
        // return nullptr;
    }
    BootSector * result;
    if(bb[FAT_COUNT_OFFSET] == 0)
    {
        // result = new NTFSBootSector(device);
    }
    else if(0 < bb[FAT_COUNT_OFFSET] <= 2)
    {
        result = new FAT32BootSector(device);
    }
    else throw("To much fats ?");

    result->Sector::read();
    return result;
}

BootSector::BootSector(Disk* device):Sector(device, 0, SIZE){}

BootSector::~BootSector(){}