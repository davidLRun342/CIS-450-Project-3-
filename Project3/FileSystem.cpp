#include <iostream>
#include<string>
#include"FileSystem.h"


int FileSystem:: FS_BOOT()
{
	hasBooted = true;

	if (extHardDisk->init == false)
	{
		osErrMsg = "ERR_FILE_BOOT";
		cout <<"\n\n" << osErrMsg <<" - MUST INITIALIZE THE EXTERNAL HARD DISK! " << endl <<endl;
		cout << "External Hard Disk will now be initialized for you....." << endl<<endl;
		
		extHardDisk->Disk_Init();

		return -1;
	}

	cout << "\nTHE UMD LIBRARY FILE SYSTEM HAS SUCESSEFULLy BOOTED!!" << endl;
	
	Disk_Load();
	return 0;
}

int FileSystem :: FS_Sync()
{
	if (hasBooted == true)
	{
		cout << "\nSYNCING MEMORY TO EXTERNAL HARD DISK.....PLEASE WAIT A MOMENT!" << endl << endl;

		wrkHardDisk->rootDir = extHardDisk->rootDir;

		for (int i = 0; i < wrkHardDisk->sector_sz; i++)
		{
			extHardDisk->diskSectors[i] = wrkHardDisk->diskSectors[i];
			extHardDisk->inode_bitmap[i] = wrkHardDisk->inode_bitmap[i];
		}

		cout << "SUCCESS!!" << endl << endl;

		return 0;
	}
	
	cout << "\n\nSYSTEM MUST BE BOOTED IN ORDER TO SYNC !!! PLEASE BOOT FS!" << endl <<endl; 
	return -1;
}

int FileSystem:: FS_Reset()
{
	if (hasBooted == true)
	{
		FS_Sync();
		hasBooted = false;
		
	}
	if (hasBooted == false || extHardDisk->init == false)
	{
		osErrMsg = "ERR_FILE_RESET";
		cout << osErrMsg << endl << endl;
		cout << "SYSTEM SHUTDOWN...." << endl;
		cout << "\nFILE SYSTEM CURRENTLY UNAVAILABLE......" << endl;
		
		return -1;
	}
	return 0; 
}

int FileSystem::Disk_Load()
{
	if (extHardDisk->init == true)
	{
		wrkHardDisk->sector_sz = extHardDisk->sector_sz;
		wrkHardDisk->sector_unit = extHardDisk->sector_unit;
		wrkHardDisk->rootDir = extHardDisk->rootDir;
		wrkHardDisk->totalInode = extHardDisk->totalInode;

		for (int i = 0; i < SECTOR_SZ; i++)
		{
			wrkHardDisk->diskSectors[i] = extHardDisk->diskSectors[i];
			wrkHardDisk->data_bitmap[i] = extHardDisk->data_bitmap[i];
			wrkHardDisk->inode_bitmap[i] = extHardDisk->inode_bitmap[i];
		}
		return 0;
	}
	return -1;
}
int FileSystem::Disk_Save()
{
	if (FS_Sync() == 0) return 0;
	
	cout << "ERROR, MEMORY WAS NOT ABLE TO SYNC TO EXTERNAL HARD DISK" << endl; 

	return -1;
}
int FileSystem::Disk_Write(int sector, string buffer)
{
	return 0;
}
int FileSystem::Disk_Read(int sector, string buffer)
{
	return 0;
}
int FileSystem::Dir_Read(string path, Buffer buffer, int size)
{
	bool found = false;
	int i = 0;
	int temp = 0;
	while (found == false)
	{
		if (extHardDisk->inode_bitmap[i].inode.direct_name == path)
		{
			temp = wrkHardDisk->buffer.size + extHardDisk->inode_bitmap[i].inode.file_sz;

			if (temp < size)
			{
				wrkHardDisk->buffer.inodeblock = extHardDisk->inode_bitmap[i].inode; // stores into the buffer
				wrkHardDisk->buffer.size = wrkHardDisk->buffer.size + extHardDisk->inode_bitmap[i].inode.file_sz;
				wrkHardDisk->printBufferContent();
				found = true;
				return 0; 
			}
			osErrMsg = "ERR_BUFF_TO_SMALL";
			cout << "\n" << osErrMsg << endl << endl;
			cout << "BUFFER CANNOT STOR THAT LOAD OF DATA!!" << endl;

			return -1;
			
		}
		i++;
	}
	cout << "PATH DOES NOT EXIST!!" << endl;
	return -1;
}