#pragma once
#include <vector>
#include <string>

#include "Utils.cpp"
#include <Entry.h>

class Entry
{
private:
    std::string name;
    BYTE type;
    int deft;
    size_t size;
    int64_t start_sector;
    // std::vector<Entry> directory;

public:
    Entry(/* args */);
    Entry(string, BYTE, size_t, int64_t);
    ~Entry();

public:
    std::string Name()
    {
        return name;
    }
    BYTE Type()
    {
        return type;
    }
    size_t Size()
    {
        return size;
    }
    int64_t Start_Sector()
    {
        return start_sector;
    }
    int Deft()
    {
        return deft;
    }
};

Entry::Entry(/* args */)
{

}

Entry::~Entry()
{
}
