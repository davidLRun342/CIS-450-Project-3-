#include "WrkHardDisk.h"


WrkHardDisk::WrkHardDisk()
{
	sector_sz = 0;
	sector_unit = 0;

	for (int i = 0; i < SECTOR_SZ; i++)
	{
		diskSectors[i].address = i;
		data_bitmap[i] = 0;
	}
}


int WrkHardDisk::File_Create(string file)
{
	return 0;
}
int WrkHardDisk::File_Open(string file)
{
	return 0;
}
int WrkHardDisk::File_Read(int fd, string buffer, int size)
{
	return 0;
}
int WrkHardDisk::File_Write(int fd, string buffer, int size)
{
	return 0;
}
int WrkHardDisk::File_Seek(int fd, int offset)
{
	return 0;
}
int WrkHardDisk::File_Close(int fd)
{
	return 0;
}
int WrkHardDisk::File_Unlink(string file)
{
	return 0;
}


void WrkHardDisk::printInodeBitmap()
{
	cout << "WORKING HARD DISK INODE BITMAP ENTRY: " << endl << endl;

	if (totalInode == 0)
	{
		cout << "NONE CURRENTLY" << endl << endl;
	}
	for (int i = 0; i < totalInode; i++)
	{
		cout << "Inode number: " << inode_bitmap[i].inode.inode_num << endl;
		cout << "file name: " << inode_bitmap[i].inode.direct_name << endl;
		cout << "address: " << inode_bitmap[i].address << endl << endl;
	}
}

void WrkHardDisk::printHardDiskContent()
{
	cout << "WORKING HARD DISK CONTENT:" << endl << endl;
	cout << "Address " << "state" << "    File name  " << endl;
	for (int i = 0; i < SECTOR_SZ; i++)
	{
		cout << diskSectors[i].address << "         " << diskSectors[i].state << "         " << diskSectors[i].directory.direct_name << endl;
	}

}void WrkHardDisk::printDataBitMap()
{
	cout << "WORKING HARD DISK DATA BITMAP ENTRY: " << endl << endl;

	for (int i = 0; i < SECTOR_SZ; i++)
	{
		cout << "\t" << i << " : " << data_bitmap[i] << endl;
	}
}