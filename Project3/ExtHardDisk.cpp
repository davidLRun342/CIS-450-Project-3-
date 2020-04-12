#include "ExtHardDisk.h"


ExtHardDisk::ExtHardDisk()
{
	magicnum = 0;
	sector_sz = 0;
	sector_unit = 0;
}
int ExtHardDisk:: Disk_Init()
{
	magicnum = 4;
	sector_sz = SECTOR_SZ;
	sector_unit = SECTOR_UNIT;

	return 0;
}
int ExtHardDisk::Disk_Load()
{
	return 0;
}
int ExtHardDisk::Disk_Save()
{
	return 0;
}
int ExtHardDisk::Disk_Write(int sector, string buffer)
{
	return 0;
}
int ExtHardDisk::Disk_Read(int sector, string buffer)
{
	return 0;
}
