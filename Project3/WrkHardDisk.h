#pragma once
#include <string>
#include<iostream>
#include "ExtHardDisk.h"


using namespace std;

class WrkHardDisk
{
public:

	int sector_sz;
	int sector_unit;
	
	InodeDirectory rootDir;

	inodeBitmap inode_bitmap[SECTOR_SZ];
	int totalInode = 0;
	Sector diskSectors[SECTOR_SZ];
	
	bool data_bitmap[SECTOR_SZ];
	
	WrkHardDisk();

	int File_Create(string file);
	int File_Open(string file);
	int File_Read(int fd, string buffer, int size);
	int File_Write(int fd, string buffer, int size);
	int File_Seek(int fd, int offset);
	int File_Close(int fd);
	int File_Unlink(string file);

	void printInodeBitmap();
	void printHardDiskContent();
	void printDataBitMap();

};

