#pragma once
#include <Windows.h>
#include <string>
#include <sstream>
#include <memory>
#include "ShortName.h"
// class ShortName;
class FatDirectoryEntry
{
public:
    static const int MAX_LABEL_LENGTH = 11;
    static const int SIZE = 32;
private:
    static const int OFFSET_ATTRIBUTES = 0x0B;
    
    static const int OFFSET_FILE_SIZE = 0x1C;

    static const int F_READONLY = 0x01;
    static const int F_HIDDEN = 0x02;
    static const int F_SYSTEM = 0x04;
    static const int F_VOLUME_ID = 0x08;
    static const int F_DIRECTORY = 0x10;
    static const int F_ARCHIVE = 0x20;
public:
    static const int ENTRY_DELETED = 0xe5;

private:
    BYTE* data;

    
public:
    FatDirectoryEntry(BYTE* data);
    static std::shared_ptr<FatDirectoryEntry> read(BYTE* buffer, long position, long sizeof_buffer);
    bool isVolumeLabel();
    bool isSystemFlag();
    bool isArchiveFlag();
    bool isHiddenFlag();
    bool isVolumeIdFlag();
    bool isLfnEntry();
    bool isDirectory();
    std::string getVolumeLabel();
    long getLength();
    bool isFile();
    long getStartCluster();
    bool isReadonlyFlag();
    std::string getLfnPart();
    bool isDeleted();

    std::shared_ptr<ShortName> getShortName();

    ~FatDirectoryEntry();
private:
    int getFlags();
};
