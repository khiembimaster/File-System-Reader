
#include <Windows.h>
class FsFile
{
public:
    virtual long getLength() = 0;
    virtual void read(long offset, BYTE* dest, int size) = 0;
    virtual~FsFile();
};