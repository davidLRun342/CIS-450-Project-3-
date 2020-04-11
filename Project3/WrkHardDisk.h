#pragma once
#include <string>

#define SECTOR_SZ 1000
#define SECTOR_UNIT 512

using namespace std;

class WrkHardDisk
{
public:

	int sector_sz = SECTOR_SZ;
	int sector_unit = SECTOR_UNIT;
	
	WrkHardDisk();
	int File_Create(string file);
	int File_Open(string file);
	int File_Read(int fd, string buffer, int size);
	int File_Write(int fd, string buffer, int size);
	int File_Seek(int fd, int offset);
	int File_Close(int fd);
	int File_Unlink(string file);
};

