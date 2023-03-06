#pragma once
#include <string>
#include <memory>
#include "FsDirectory.h"
#include "FsFile.h"
class FsDirectory;

class FsDirectoryEntry 
{
public:
    virtual std::string getName() = 0;
    virtual std::weak_ptr<FsDirectory> getParent() = 0;
    virtual std::weak_ptr<FsFile> getFile() = 0;
    virtual ~FsDirectoryEntry(){}
};  