#pragma once
#include "FsDirectoryEntry.h"
#include "FatDirectoryEntry.h"
#include "FatLfnDirectory.h"
#include <string>

class FatLfnDirectory;

class FatLfnDirectoryEntry : public FsDirectoryEntry
{
    FatDirectoryEntry* realEntry;

private:
    FatLfnDirectory* parent;
    std::string fileName;

public:
    // FatLfnDirectoryEntry(std::string name, ShortName sn, FatLfnDirectory* parent, bool directory);
    FatLfnDirectoryEntry(FatLfnDirectory* parent, FatDirectoryEntry* realEntry, std::string fileName);
    static FatLfnDirectoryEntry* extract(FatLfnDirectory* dir, int offset, int len);
public:
    bool isHiddenFlag();
    bool isSystemFlag();
    bool isReadOnlyFlag();
    bool isArchiveFlag();
    bool isFile();
    bool isDirectory();
public:
    std::string getName();
    FsDirectory* getParent();
    FATFile* getFile();
    FatLfnDirectory* getDirectory();
};