
#include "FatLfnDirectory.h"
#include <algorithm>
#include <string>


FatLfnDirectory::FatLfnDirectory(std::shared_ptr<AbstractDirectory> dir, std::shared_ptr<FAT> fat)
{
    if ((dir == nullptr) || (fat == nullptr)) throw ("Null exception");

    this->fat = fat;
    this->dir = dir;

    parseLfn();
}

std::shared_ptr<FAT> FatLfnDirectory::getFat()
{
    return fat;
}

std::shared_ptr<FATFile> FatLfnDirectory::getFile(std::shared_ptr<FatDirectoryEntry> entry) 
{
    std::shared_ptr<FATFile> file = entryToFile[entry];

    if(file == nullptr)
    {
        file = FATFile::get(fat, entry);
    }

    return file;
}

std::shared_ptr<FatLfnDirectory> FatLfnDirectory::getDirectory(std::shared_ptr<FatDirectoryEntry> entry) {
    std::shared_ptr<FatLfnDirectory> result = entryToDirectory[entry];

    if (result == nullptr) {
        std::shared_ptr<ClusterChainDirectory> storage = read(entry, fat);
        result = std::make_shared<FatLfnDirectory>(storage, fat);
        entryToDirectory[entry] = result;
    }
    
    return result;
}


bool FatLfnDirectory::isFreeName(std::string name) {
    std::transform(name.begin(), name.end(), name.begin(), ::tolower);
    bool result = this->usedNames.find(name) == this->usedNames.end();
    return result;
}

void FatLfnDirectory::checkUniqueName(std::string name) 
{
    std::string lowerName = name;
    std::transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);
    if (this->usedNames.find(lowerName) != this->usedNames.end()) {
        std::stringstream err;
        err << "an entry named " << name << " already exists" ;
        throw (err.str());
    }
}

std::shared_ptr<FsDirectoryEntry> FatLfnDirectory::getEntry(std::string name) {
    std::transform(name.begin(), name.end(), name.begin(), ::tolower);
    
    std::shared_ptr<FatLfnDirectoryEntry> entry = longNameIndex[name];
    
    if (entry == nullptr) {
        if (!ShortName::canConvert(name)) return nullptr;
        return shortNameIndex[ShortName::get(name)];
    } else {
        return entry;
    }
}

void FatLfnDirectory::parseLfn() {
    int i = 0;
    int size = dir->getEntryCount();
    std::shared_ptr<FatLfnDirectoryEntry> current;
    std::string temp;
    while (i < size) {
        // jump over empty entries
        while (i < size && dir->getEntry(i) == nullptr) {
            i++;
        }

        if (i >= size) {
            break;
        }

        int offset = i; // beginning of the entry
        // check when we reach a real entry
        while (dir->getEntry(i)->isLfnEntry()) {
            i++;
            if (i >= size) {
                // This is a cutted entry, forgive it
                break;
            }
        }
        
        if (i >= size) {
            // This is a cutted entry, forgive it
            break;
        }
        
        current = FatLfnDirectoryEntry::extract(std::shared_ptr<FatLfnDirectory>(this), offset, ++i - offset);
        
        if (current->getName() != "" && !current->realEntry->isDeleted() ) {
            checkUniqueName(current->getName());
            temp = current->realEntry->getShortName()->asSimpleString();
            std::transform(temp.begin(), temp.end(), temp.begin(), tolower);
            this->usedNames.insert(temp);
            shortNameIndex[current->realEntry->getShortName()] = current;
            temp = current->getName();
            std::transform(temp.begin(), temp.end(), temp.begin(), tolower);
            longNameIndex[temp] = current;
        }else {
            deletedIndex.push_back(current);
        }
    }
}

std::shared_ptr<ClusterChainDirectory> FatLfnDirectory::read(std::shared_ptr<FatDirectoryEntry> entry, std::shared_ptr<FAT> fat){

    if (!entry->isDirectory()) throw ("NO directory");

    std::shared_ptr<ClusterChain> chain = std::make_shared<ClusterChain>(fat, entry->getStartCluster());

    std::shared_ptr<ClusterChainDirectory> result = std::make_shared<ClusterChainDirectory>(chain, false);

    result->readb();
    return result;
}

std::string FatLfnDirectory::showDirectory()
{
    std::stringstream sstr;
    for(auto index : longNameIndex){
        sstr << "\t" << index.first << std::endl;
    }
    return sstr.str();
}