#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <exception>
#include "FatDirectoryEntry.h"
class AbstractDirectory
{
public:
    static const int MAX_LABEL_LENGTH = 11;
private:
    std::vector<FatDirectoryEntry*> entries;
    bool isRoot;
    int capacity;
    std::string volumeLabel;

protected:
    AbstractDirectory(int capacity, bool isRoot) 
    {
        this->capacity = capacity;
        this->isRoot = isRoot;
    }

    virtual void read(BYTE* data, int size) = 0;
    virtual long getStorageCluster() = 0;

public:
    FatDirectoryEntry* getEntry(int idx) {
        return this->entries[idx];
    }

    int getCapacity() {
        return this->capacity;
    }

    int getEntryCount() {
        return this->entries.size();
    }

    boolean isRoot() {
        return this->isRoot;
    }

    int getSize() {
        return entries.size() + ((this->volumeLabel.size() > 0) ? 1 : 0);
    }

    void checkRoot() 
    {
        if (!isRoot) {
            throw ("only supported on root directories");
        }
    }

    std::string getLabel() {
        try{
            checkRoot();
        }catch(std::exception e) {
            std::cout << e.what();
            return "";
        }

        return volumeLabel;
    }

    void readb() {
        int size = getCapacity() * FatDirectoryEntry::SIZE;
        BYTE* data = new BYTE [size];
                
        read(data, size);
        // data.flip();
        
        for (int i=0; i < getCapacity(); i++) {
            FatDirectoryEntry* e = FatDirectoryEntry::read(data);
            
            if (e == nullptr) break;
            
            if (e->isVolumeLabel()) {
                if (!this->isRoot) throw("volume label in non-root directory");
                
                this->volumeLabel = e->getVolumeLabel();
            } else {
                entries.push_back(e);
            }
        }
    }
};  