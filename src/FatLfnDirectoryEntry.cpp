#include "FatLfnDirectoryEntry.h"

FatLfnDirectoryEntry::FatLfnDirectoryEntry(FatLfnDirectory* parent, FatDirectoryEntry* realEntry, std::string fileName)
{
    this->parent = parent;
    this->realEntry = realEntry;
    this->fileName = fileName;
}

FatLfnDirectoryEntry* FatLfnDirectoryEntry::extract(FatLfnDirectory* dir, int offset, int len)
{
    FatDirectoryEntry* realEntry = dir->dir->getEntry(offset + len - 1);
    std::string fileName;

    if(len == 1) {
        fileName = realEntry->getShortName()->asSimpleString();
    }
    else 
    {
        std::stringstream name;
        for(int i = len - 2; i >= 0; i--) {
            FatDirectoryEntry* entry = dir->dir->getEntry(i + offset);
            name << entry->getLfnPart();
        }

        fileName = name.str();
    }

    return new FatLfnDirectoryEntry(dir, realEntry, fileName);
}

bool FatLfnDirectoryEntry::isHiddenFlag()
{
    return this->realEntry->isHiddenFlag();
}

bool FatLfnDirectoryEntry::isSystemFlag()
{
    return this->realEntry->isSystemFlag();
}

bool FatLfnDirectoryEntry::isReadOnlyFlag()
{
    return this->realEntry->isReadonlyFlag();
}

bool FatLfnDirectoryEntry::isArchiveFlag()
{
    return this->realEntry->isArchiveFlag();
}

bool FatLfnDirectoryEntry::isFile()
{
    return this->realEntry->isFile();
}

bool FatLfnDirectoryEntry::isDirectory()
{
    return this->realEntry->isDirectory();
}

std::string FatLfnDirectoryEntry::getName()
{
    
    return fileName;
}

FsDirectory* FatLfnDirectoryEntry::getParent()
{
    return parent;
}

FATFile* FatLfnDirectoryEntry::getFile()
{
    return parent->getFile(realEntry);
}

FatLfnDirectory* FatLfnDirectoryEntry::getDirectory()
{
    return parent->getDirectory(realEntry);
}