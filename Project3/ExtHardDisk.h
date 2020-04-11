#pragma once
#include <string>
#define SECTOR_SZ 1000
#define SECTOR_UNIT 512

using namespace std;


class ExtHardDisk
{
public:
	
	int sector_sz = SECTOR_SZ;
	int sector_unit = SECTOR_UNIT; 
	
	
	ExtHardDisk();

	int Disk_Init();
	int Disk_Load();
	int Disk_Save();
	int Disk_Write(int sector, string buffer);
	int Disk_Read(int sector, string buffer);

	
};

