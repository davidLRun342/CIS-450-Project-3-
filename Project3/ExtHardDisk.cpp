#include "ExtHardDisk.h"


ExtHardDisk::ExtHardDisk()
{
	magicnum = 0;
	sector_sz = 0;
	sector_unit = 0;

	//Assign the address to each sector
	for (int i = 0; i < SECTOR_SZ; i++)
	{
		diskSectors[i].address = i;
	}
}
int ExtHardDisk:: Disk_Init()
{
	magicnum = 4;
	sector_sz = SECTOR_SZ;
	sector_unit = SECTOR_UNIT;
	init = true;

	rootDir.file_sz = 0;
	rootDir.inode_num = 0;
	rootDir.file_type = "dir";
	rootDir.direct_name = "/root";

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
int ExtHardDisk::Dir_Create(string path)
{
	int flag = 0;
	int i = 0;
	if (init == true)
	{
		inode_bitmap[totalInode].inode.file_type = "dir";
		inode_bitmap[totalInode].inode.direct_name = rootDir.direct_name + "/" + path;
		inode_bitmap[totalInode].inode.file_sz = 0;
		inode_bitmap[totalInode].inode.inode_num = inode_num_a;

		rootDir.directory_entries[rootDir.entrySize].filename = inode_bitmap[totalInode].inode.direct_name;
		rootDir.directory_entries[rootDir.entrySize].inode_num = inode_bitmap[totalInode].inode.inode_num; // assign random inode number
		rootDir.entrySize++;
		inode_num_a++;

		// LOOKS FOR FREE SECTOR SPACE IN HARD DISK 
		while (flag == 0 && i < SECTOR_SZ)
		{
			if (diskSectors[i].state == 0)
			{
				diskSectors[i].state = 1;

				inode_bitmap[totalInode].address = diskSectors[i].address;
				diskSectors[i].directory = inode_bitmap[totalInode].inode; // stores into sector
				totalInode++;

				flag = 1;
				return 0;

			}
			i++;
		}
	}
	return -1;
}
int ExtHardDisk::Dir_Size(string path)
{
	int i = 0;
	int flag = 0;
	while( i < totalInode && flag ==0 )
	{
		if (inode_bitmap[i].inode.direct_name == path)
		{
			return inode_bitmap[i].inode.file_sz;
		}
	}
	return -1;

}
int ExtHardDisk::Dir_Read(string path, string buffer, int size)
{
	return 0;
}
int ExtHardDisk::Dir_Unlink(string path)
{
	return 0;
}

void ExtHardDisk::printInodeBitmap()
{
	cout << "INODE BITMAP ENTRY: " << endl << endl;

	for (int i = 0; i < totalInode; i++)
	{
		cout << "Inode number: " << inode_bitmap[i].inode.inode_num << endl;
		cout << "file name: " << inode_bitmap[i].inode.direct_name << endl;
		cout << "address: " << inode_bitmap[i].address << endl << endl;
	}
}

void ExtHardDisk::printHardDiskContent()
{
	cout << "DISK CONTENT:" << endl << endl;
	cout << "Address " << "state" << "    File name  " << endl;
	for (int i = 0; i < SECTOR_SZ; i++)
	{
		cout << diskSectors[i].address << "         " << diskSectors[i].state << "         "<< diskSectors[i].directory.direct_name << endl;
	}

}