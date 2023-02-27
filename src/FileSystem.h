#pragma once

#include <string>
using namespace std;

class FileSystemInterface
{
private:
    /* data */
public:
    FileSystemInterface(/* args */);
    virtual ~FileSystemInterface();

public:
    virtual string Type () = 0;
    virtual void Show_Partition_Info() = 0;
    virtual void Show_Txt() = 0;
    virtual void Show_Current_Directory() = 0;
    virtual void Enter_Child_Directory() = 0;
    virtual void Return_Parent_Directory() = 0;
};

FileSystemInterface::FileSystemInterface(/* args */)
{
}

FileSystemInterface::~FileSystemInterface()
{
}
