#pragma once

#include "FileSystem.h"
#include "Utils.cpp"

class NTFS : public FileSystemInterface
{
private:
    LPCWSTR drive;
    WORD bytes_per_sector;
    BYTE sectors_per_cluster;
    WORD reserved_sectors;
    BYTE media_descriptor;
    WORD sectors_per_track;
    WORD number_of_heads;
    DWORD hidden_sectors;
    LONGLONG total_sectors;
    LONGLONG logical_cluster_number_for_the_file_$MFT;
    LONGLONG logical_cluster_number_for_the_file_$MFTMirr;
    DWORD clusters_per_file_record_segment;
    BYTE clusters_per_index_buffer;
    LONGLONG volume_serial_number;
    DWORD checksum;

    
    BYTE* Partition_boot_sector;
    BYTE* Master_file_table;
public:
    NTFS(/* args */);
    ~NTFS();

public:
    string Type ();
    void Show_Partition_Info();
    void Show_Txt();
    void Show_Current_Directory();
    void Enter_Child_Directory();
    void Return_Parent_Directory();

private:
    void Read_Partition_Boot_Sector();
    void Read_Master_File_Table();
};

NTFS::NTFS(/* args */)
{
}

NTFS::~NTFS()
{
}
