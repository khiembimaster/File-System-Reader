#pragma once

#include <memory>
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
    std::vector<std::shared_ptr<FatDirectoryEntry>> entries;
    bool IsRoot;
    int capacity;
    std::string volumeLabel;

protected:
    AbstractDirectory(int capacity, bool isRoot) 
    {
        this->capacity = capacity;
        this->IsRoot = isRoot;
    }

    virtual void read(BYTE* data, int size) = 0;
    virtual long getStorageCluster() = 0;

public:
    std::shared_ptr<FatDirectoryEntry> getEntry(int idx) {
        return this->entries[idx];
    }

    int getCapacity() {
        return this->capacity;
    }

    int getEntryCount() {
        return this->entries.size();
    }

    boolean isRoot() {
        return this->IsRoot;
    }

    int getSize() {
        return entries.size() + ((this->volumeLabel.size() > 0) ? 1 : 0);
    }

    void checkRoot() 
    {
        if (!IsRoot) {
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
        long position = 0;
        for (int i=0; i < getCapacity(); i++) {
            std::shared_ptr<FatDirectoryEntry> e = FatDirectoryEntry::read(data, position, size);
            position += FatDirectoryEntry::SIZE;
            if (e == nullptr) break;
            
            if (e->isVolumeLabel()) {
                if (!this->IsRoot) throw("volume label in non-root directory");
                
                this->volumeLabel = e->getVolumeLabel();
            } else {
                entries.push_back(e);
            }
        }
    }
};  