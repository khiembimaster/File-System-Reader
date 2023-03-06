#pragma once
#include <string>
#include <memory>
#include "FsDirectoryEntry.h"
class FsDirectoryEntry;
class FsDirectory {
public:
    virtual std::shared_ptr<FsDirectoryEntry> getEntry(std::string name) = 0;
    virtual ~FsDirectory(){}
};
