#pragma once
#include <string>
#include "FsDirectory.h"
#include "FsFile.h"
class FsDirectory;
class FsDirectoryEntry 
{
public:
    virtual std::string getName() = 0;
    virtual FsDirectory* getParent() = 0;
    virtual FsFile* getFile() = 0;
    virtual ~FsDirectoryEntry();
};  