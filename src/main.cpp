//#include <FileSystem.h>
#include "FAT32.h"
#include "Disk.h"
//#include <NTFS.h>
#include <exception>
#include <iostream>
#include <memory>
int main()
{
    std::shared_ptr<Disk> usb = Disk::create(L"\\\\.\\E:");
    std::shared_ptr<FAT32> file_system;
    try{
        file_system = FAT32::read(usb);
        // std::cout << file_system->getRoot()->getEntry("kh.txt")->getName();
        std::cout <<file_system->getVolumeLabel() << std::endl;
        std::cout << file_system->getRoot()->showDirectory();
        auto entry = std::dynamic_pointer_cast<FatLfnDirectoryEntry>(file_system->getRoot()->getEntry("kh.txt"));
        if(entry->isDirectory()){
            std::cout << entry->getDirectory()->showDirectory();
        }else if(entry->isFile()){
            auto file = std::dynamic_pointer_cast<FATFile> (entry->getFile());
            BYTE* result = new BYTE[file->getLength()];
            file->getChain()->readData(0, result, file->getLength());
            // std::cout << std::string(result);
            delete result;
        }
        
        
        
        // file_system->getRoot()->getDirectory(entry)->showDirectory();

        system("pause");
    }catch (std::exception e) {
        std::cout << e.what();
    }
    
    system("pause");
}