#include "FatLfnDirectoryEntry.h"

FatLfnDirectoryEntry::FatLfnDirectoryEntry(std::shared_ptr<FatLfnDirectory> parent, std::shared_ptr<FatDirectoryEntry> realEntry, std::string fileName)
{
    this->parent = parent;
    this->realEntry = realEntry;
    this->fileName = fileName;
}

std::shared_ptr<FatLfnDirectoryEntry> FatLfnDirectoryEntry::extract(std::shared_ptr<FatLfnDirectory> dir, int offset, int len)
{
    std::shared_ptr<FatDirectoryEntry> realEntry = dir->dir->getEntry(offset + len - 1);
    std::string fileName;

    if(len == 1) {
        fileName = realEntry->getShortName()->asSimpleString();
    }
    else 
    {
        std::stringstream name;
        for(int i = len - 2; i >= 0; i--) {
            std::shared_ptr<FatDirectoryEntry> entry = dir->dir->getEntry(i + offset);
            name << entry->getLfnPart();
        }

        fileName = name.str();
    }

    return std::make_shared<FatLfnDirectoryEntry>(dir, realEntry, fileName);
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

std::weak_ptr<FsDirectory> FatLfnDirectoryEntry::getParent()
{
    return parent;
}

std::weak_ptr<FsFile> FatLfnDirectoryEntry::getFile()
{
    return parent->getFile(realEntry);
}

std::shared_ptr<FatLfnDirectory> FatLfnDirectoryEntry::getDirectory()
{
    return parent->getDirectory(realEntry);
}