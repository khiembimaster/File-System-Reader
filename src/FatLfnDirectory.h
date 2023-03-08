#pragma once 
#include "FsDirectory.h"
#include <map>
#include <memory>
#include <set>
#include "FAT.h"
#include "FatDirectoryEntry.h"
#include "ClusterChainDirectory.h"
#include "AbstractDirectory.h"
#include "FATFile.h"
#include "FatLfnDirectoryEntry.h"
#include "ShortName.h"

// TODO: implement these classes
class ShortName;
class FatLfnDirectoryEntry;
class FATFile;
class FatDirectoryEntry;
class AbstractDirectory;

class FatLfnDirectory : public FsDirectory
{
private:
    std::set<std::string> usedNames;
    std::shared_ptr<FAT> fat;
    std::map<std::shared_ptr<ShortName>, std::shared_ptr<FatLfnDirectoryEntry>> shortNameIndex;
    std::map<std::string, std::shared_ptr<FatLfnDirectoryEntry>> longNameIndex;
    std::vector<std::shared_ptr<FatLfnDirectoryEntry>> deletedIndex;
    std::map<std::shared_ptr<FatDirectoryEntry>, std::shared_ptr<FATFile>> entryToFile;
    std::map<std::shared_ptr<FatDirectoryEntry>, std::shared_ptr<FatLfnDirectory>> entryToDirectory;
    // ShortNameGenerator sng;
public:
    std::shared_ptr<AbstractDirectory> dir;
    ~FatLfnDirectory(){}
public:
    FatLfnDirectory(std::shared_ptr<AbstractDirectory> dir, std::shared_ptr<FAT> fat);
    std::shared_ptr<FAT> getFat();
    std::shared_ptr<FATFile> getFile(std::shared_ptr<FatDirectoryEntry> entry);
    std::shared_ptr<FatLfnDirectory> getDirectory(std::shared_ptr<FatDirectoryEntry> entry);
    std::shared_ptr<FsDirectoryEntry> getEntry(std::string name);
    bool isFreeName(std::string name);
    std::string showDirectory();
private:
    void checkUniqueName(std::string name) ;
    void parseLfn();
    static std::shared_ptr<ClusterChainDirectory> read(std::shared_ptr<FatDirectoryEntry> entry, std::shared_ptr<FAT> fat);
    
};
