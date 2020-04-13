#pragma once
#include <string>
#include "InodeBlock.h"
#define SECTOR_SZ 1000
#define SECTOR_UNIT 512

using namespace std;

//=================================SECTOR DATA STRUCTURE===============================================
/* Data structure for each of the sectors within the hard disk. 
   The data structure is contains its address, occupancy state, dataBlock occupancy size, 
   directory block, data bitmaps, and inode bitmaps*/

struct inodeBitmap
{
	int address;
	InodeDirectory inode;

}; typedef struct inodeBitmap inodeBitmap;

struct Sector
{
	int address;
	bool state = 0;
	InodeDirectory directory; 
	bool data_bitmap[SECTOR_SZ];

}; typedef struct Sector Sector;


class ExtHardDisk
{
public:

	int sector_sz ;
	int sector_unit; 
	int magicnum;
	int inode_num_a = 1;
	bool init = false;
	InodeDirectory rootDir;

	Sector diskSectors[SECTOR_SZ];
	
	inodeBitmap inode_bitmap[SECTOR_SZ];
	int totalInode = 0;

	ExtHardDisk();

	int Disk_Init();
	int Disk_Load();
	int Disk_Save();
	int Disk_Write(int sector, string buffer);
	int Disk_Read(int sector, string buffer);
	
	int Dir_Create(string path);
	int Dir_Size(string path);
	int Dir_Read(string path, string buffer, int size);
	int Dir_Unlink(string path);

	void printInodeBitmap();
	void printHardDiskContent();
};

