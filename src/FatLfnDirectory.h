#pragma once 
#include "FsDirectory.h"
#include <map>
#include <algorithm>
#include <string>
#include <set>
#include "FAT.h"
#include "FatDirectoryEntry.h"
#include "ClusterChainDirectory.h"
#include "AbstractDirectory.h"
#include "FATFile.h"
#include "FatLfnDirectoryEntry.h"


// TODO: implement these classes
// class ShortName;
class FatLfnDirectoryEntry;

class FatLfnDirectory : public FsDirectory
{
private:
    std::set<std::string> usedNames;
    FAT* fat;
    std::map<std::string, FatLfnDirectoryEntry*> shortNameIndex;
    std::map<std::string, FatLfnDirectoryEntry*> longNameIndex;
    std::map<FatDirectoryEntry*, FATFile*> entryToFile;
    std::map<FatDirectoryEntry*, FatLfnDirectory*> entryToDirectory;
    // ShortNameGenerator sng;
public:
    AbstractDirectory* dir;

public:
    FatLfnDirectory(AbstractDirectory* dir, FAT* fat)
    {
        if ((dir == nullptr) || (fat == nullptr)) throw ("Null exception");

        this->fat = fat;
        this->dir = dir;

        parseLfn();
    }

    FAT* getFat()
    {
        return fat;
    }

    FATFile* getFile(FatDirectoryEntry * entry) 
    {
        FATFile* file = entryToFile[entry];

        if(file == nullptr)
        {
            file = FATFile::get(fat, entry);
        }

        return file;
    }

    FatLfnDirectory* getDirectory(FatDirectoryEntry* entry) {
        FatLfnDirectory* result = entryToDirectory[entry];

        if (result == nullptr) {
            ClusterChainDirectory* storage = read(entry, fat);
            result = new FatLfnDirectory(storage, fat);
            entryToDirectory[entry] = result;
        }
        
        return result;
    }

    bool isFreeName(std::string name) {
        std::transform(name.begin(), name.end(), name.begin(), ::tolower);
        bool result = this->usedNames.find(name) == this->usedNames.end();
        return result;
    }

private:
    void checkUniqueName(std::string name) {
        std::string lowerName = name;
        std::transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);
        if (this->usedNames.find(lowerName) != this->usedNames.end()) {
            std::stringstream err;
            err << "an entry named " << name << " already exists" ;
            throw (err.str());
        }
    }

public:
    FatLfnDirectoryEntry* getEntry(std::string name) {
        std::transform(name.begin(), name.end(), name.begin(), ::tolower);
        
        FatLfnDirectoryEntry* entry = longNameIndex[name];
        
        if (entry == nullptr) {
            // if (!ShortName.canConvert(name)) return null;
            // return shortNameIndex.get(ShortName.get(name));
        } else {
            return entry;
        }
    }
private:
    void parseLfn() {
        int i = 0;
        int size = dir->getEntryCount();
        
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
            
            FatLfnDirectoryEntry* current =
                    FatLfnDirectoryEntry::extract(this, offset, ++i - offset);
            
            if (!current->realEntry->isDeleted() && current->isValid()) {
                checkUniqueName(current.getName());
                this.usedNames.add(current.realEntry.getShortName().asSimpleString().toLowerCase(Locale.ROOT));
                
                shortNameIndex.put(current.realEntry.getShortName(), current);
                longNameIndex.put(current
                        .getName()
                        .toLowerCase(Locale.ROOT), current);
            }
        }
    }

    static ClusterChainDirectory* read(FatDirectoryEntry* entry, FAT* fat){

        if (!entry->isDirectory()) throw ("NO directory");

        ClusterChain* chain = new ClusterChain(fat, entry->getStartCluster());

        ClusterChainDirectory* result = new ClusterChainDirectory(chain, false);

        result->readb();
        return result;
    }
};