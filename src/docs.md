# Overview of the system 

# How I read raw data ?
// The __*Disk*__ class
# How I parse the __*Boot sector*__?
// The __*BootSector*__ class and its derived one
## FAT32BootSector
## NTFSBootSector

# How I find the the __*Directories*__ and __*Files*__ ?
## FAT32 
### Read the file allocation table (__FAT__)
### Chaining the clusters (__Cluster chain__)
### Parse the raw bytes into meaningful Dirctory Entry
### In RAM files directory system for 
## NTFS
### The Master file table 
# How I display the __*%.txt*__ ?