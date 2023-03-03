#include <Windows.h>
#include <string>
#include <sstream>
class ShortName;
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

    FatDirectoryEntry(BYTE* data);
public:
    static FatDirectoryEntry* read(BYTE* buffer);
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


    ~FatDirectoryEntry();
private:
    int getFlags();
};

FatDirectoryEntry::FatDirectoryEntry(BYTE* data): data{data} {}

FatDirectoryEntry* FatDirectoryEntry::read(BYTE* buffer)
{
    BYTE* data = new BYTE [SIZE];
    memcpy (data, buffer, SIZE);
    return new FatDirectoryEntry(data);
}

bool FatDirectoryEntry::isVolumeLabel()
{
    if(isLfnEntry()) return false;
    else return ((getFlags() & (F_DIRECTORY | F_VOLUME_ID)) == F_VOLUME_ID);
}

bool FatDirectoryEntry::isSystemFlag()
{
    return ((getFlags() & F_SYSTEM) != 0);
}

bool FatDirectoryEntry::isArchiveFlag()
{
    return ((getFlags() & F_ARCHIVE) != 0);
}

bool FatDirectoryEntry::isHiddenFlag()
{
    return ((getFlags() & F_HIDDEN) != 0);
}
bool FatDirectoryEntry::isVolumeIdFlag()
{
    return ((getFlags() & F_VOLUME_ID) != 0);
}

bool FatDirectoryEntry::isLfnEntry()
{
    return isReadonlyFlag() && isSystemFlag() &&
                isHiddenFlag() && isVolumeIdFlag();
}

bool FatDirectoryEntry::isDirectory()
{
    return ((getFlags() & (F_DIRECTORY | F_VOLUME_ID)) == F_DIRECTORY);
}

std::string FatDirectoryEntry::getVolumeLabel()
{
    if (!isVolumeLabel())
        throw ("not a volume label");
        
    std::stringstream sstr;
    
    for (int i=0; i < MAX_LABEL_LENGTH; i++) {
        BYTE b = this->data[i];
        
        if (b != 0) {
            sstr << char(b);
        } else {
            break;
        }
    }
    
    return sstr.str();
}

long FatDirectoryEntry::getLength()
{
    long result = 0;
    memcpy (&result, data + OFFSET_FILE_SIZE, 4);
    return result;
}

// public ShortName getShortName() {
//         if (this.data[0] == 0) {
//             return null;
//         } else {
//             return ShortName.parse(this.data);
//         }
//     }

bool FatDirectoryEntry::isFile()
{
    return ((getFlags() & (F_DIRECTORY | F_VOLUME_ID)) == 0);
}

long FatDirectoryEntry::getStartCluster()
{
    WORD high = 0;
    WORD low = 0;
    
    memcpy (&high, data + 0x14, 2);
    memcpy (&low, data + 0x1A, 2);

    return ((high << 16) | low);
}

bool FatDirectoryEntry::isReadonlyFlag()
{
    return ((getFlags() & F_READONLY) != 0);
}

std::string FatDirectoryEntry::getLfnPart()
{
    char unicodechar[13] {0};
    
    for(int i = 0, offset = 1; i <= 4; i++, offset += 2)
    {
        WORD temp = 0;
        memcpy (&temp, data + offset, 2);
        unicodechar[i] = (char) temp;
    }

    for(int i = 5, offset = 14; i <= 12; i++, offset += 2)
    {
        WORD temp = 0;
        memcpy (&temp, data + offset, 2);
        unicodechar[i] = (char) temp;
    }   

    // int end = 0;

    // while ((end < 13) && (unicodechar[end] != '\0')) {
    //     end++;
    // }
        
    return std::string(unicodechar);
}

FatDirectoryEntry::~FatDirectoryEntry()
{
    delete [] data;
}

int FatDirectoryEntry::getFlags()
{
    int result = 0;
    memcpy (&result, data + OFFSET_ATTRIBUTES, 1);
    return result;
}