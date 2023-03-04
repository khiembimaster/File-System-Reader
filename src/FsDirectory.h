#pragma once
#include <string>
class FsDirectory {
public:
    virtual std::string getName() = 0;
    virtual FsDirectory* getParent() = 0;
    virtual FsDirectory* getDirectory() = 0; 
    virtual ~FsDirectory() = 0;
};
