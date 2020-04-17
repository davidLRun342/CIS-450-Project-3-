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
	int size = 0;
	bool state = 0;
	InodeDirectory inode; 

}; typedef struct Sector Sector;


class ExtHardDisk
{
public:

	int sector_sz ;
	int sector_unit; 
	int magicnum;
	int inode_num_a = 1;

	string dskErrMsg = "";

	bool init = false;
	InodeDirectory rootDir;

	Sector diskSectors[SECTOR_SZ];
	
	inodeBitmap inode_bitmap[SECTOR_SZ];
	bool data_bitmap[SECTOR_SZ];

	int totalInode = 0;

	ExtHardDisk();

	int Disk_Init();
	
	int Dir_Create(string path, string parent);
	int Dir_Size(string path);
	
	void diskAlloc();
	void printInodeBitmap();
	void printDataBitMap();
	void printHardDiskContent();
	void printAllInode();

};

