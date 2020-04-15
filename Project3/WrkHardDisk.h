#pragma once
#include <string>
#include<iostream>
#include "ExtHardDisk.h"

#define SECTOR_SZ 1000
#define  SECTOR_UNIT 512

using namespace std;

struct Buffer
{
	InodeDirectory inodeblock;
	int size=0;

}; typedef struct Buffer Buffer;

class WrkHardDisk
{
public:

	int sector_sz;
	int sector_unit;
	
	int filePointer=0;

	InodeDirectory rootDir;

	inodeBitmap inode_bitmap[SECTOR_SZ];
	int totalInode = 0;
	Sector diskSectors[SECTOR_SZ];
	
	bool data_bitmap[SECTOR_SZ];
	
	Buffer buffer;

	ExtHardDisk *extHardDisk;

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
	void printAllInode();
	void printBufferContent();

};

