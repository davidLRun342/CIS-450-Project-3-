#pragma once
#include <string>
#include<iostream>
#include "ExtHardDisk.h"

#define SECTOR_SZ 1000
#define  SECTOR_UNIT 512
#define BUFF_NUM 5
using namespace std;

struct Buffer
{
	InodeDirectory inodeblock;
	int size=0;

}; typedef struct Buffer Buffer;

struct otableEntry
{
	InodeDirectory inodeblock;
	int address = -1;
	int fDes = -1;
	int state = 0;

}; typedef struct otableEntry otableEntry;

struct openFileTable
{
	otableEntry entries[10];

}; typedef struct openFileTable openFileTable;

class WrkHardDisk
{
public:

	int sector_sz;
	int sector_unit;
	
	int filePointer=0;
	int fileDescr = 0;

	string osErrMsg = "";

	InodeDirectory rootDir;

	inodeBitmap inode_bitmap[SECTOR_SZ];
	int totalInode = 0;
	Sector diskSectors[SECTOR_SZ];
	
	bool data_bitmap[SECTOR_SZ];
	
	Buffer buffer;
	int buff_cnt = 0;

	ExtHardDisk *extHardDisk;
	openFileTable opFileTable;
	int numOpenFile = 0;

	WrkHardDisk();

	int File_Create(string file, string directory);
	int File_Open(string file);
	int File_Read(int fd);
	int File_Write(int fd, int size);
	int File_Seek(int fd, int size, int offset);
	int File_Close(int fd);
	int File_Unlink(string file);

	void diskAlloc();
	void printInodeBitmap();
	void printHardDiskContent();
	void printDataBitMap();
	void printAllInode();
	void printBufferContent();
	void printOpenFileTable();

};

