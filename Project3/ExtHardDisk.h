#pragma once
#include <string>
#include "InodeBlock.h"
#include "FileSystem.h"
#define SECTOR_SZ 1000
#define SECTOR_UNIT 512



using namespace std;


struct Sector
{
	InodeBlock inode;
	InodeDirectory directory; 
	bool data_bitmap[SECTOR_SZ];
	bool inode_bitmap[SECTOR_SZ];

}; typedef struct Sector Sector;


class ExtHardDisk
{
public:

	int sector_sz ;
	int sector_unit; 
	int magicnum;

	FileSystem myFileSys;
	Sector diskSectors[SECTOR_SZ];
	
	ExtHardDisk();

	int Disk_Init();
	int Disk_Load();
	int Disk_Save();
	int Disk_Write(int sector, string buffer);
	int Disk_Read(int sector, string buffer);
	
};

