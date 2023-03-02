#include "FAT32BootSector.h"

FAT32BootSector::FAT32BootSector(Disk* device): BootSector(device){}

long FAT32BootSector::getRootDirFirstCluster() {
    return getNum(ROOT_DIR_FIRST_CLUSTER_OFFSET, 4);
}

long FAT32BootSector::getSectorsPerFat() {
    return getNum(SECTORS_PER_FAT_OFFSET, 4);
}

std::string FAT32BootSector::getType() {
    return "FAT32";
}

long FAT32BootSector::getSectorCount() {
    return getNum(TOTAL_SECTORS_32_OFFSET, 4);
}

std::string FAT32BootSector::toString()
{
    std::stringstream builder;
    builder << "Bootsector :" << std::endl
            << "Type = " << getType() << std::endl
            << "Sectors per fat = " << getSectorsPerFat() << std::endl
            << "Sectors of Volume = " << getSectorCount() << std::endl
            << "Sectors per cluster = " << getSectorsPerCluster() << std::endl
            << "Bytes per sector = " << getBytesPerSector() << std::endl
            << "Root directory first cluster = " << getRootDirFirstCluster() << std::endl
            << "Reserved sectors = " << getNrReservedSectors() <<std::endl;
    return builder.str();            
}

long FAT32BootSector::getBytesPerSector()
{
    return getNum(BYTES_PER_SECTOR_OFFSET, 2);
}
  
long FAT32BootSector::getSectorsPerCluster()
{
    return getNum(SECTORS_PER_CLUSTER_OFFSET, 1) ;
}

long FAT32BootSector::getNrReservedSectors()
{
    return getNum(RESERVED_SECTORS_OFFSET, 2);
}

long FAT32BootSector::getFatOffset(int fatNr) {
    long sectSize = this->getBytesPerSector();
    long sectsPerFat = this->getSectorsPerFat();
    long resSects = this->getNrReservedSectors();

    long offset = resSects * sectSize;
    long fatSize = sectsPerFat * sectSize;

    offset += fatNr * fatSize;

    return offset;
}

