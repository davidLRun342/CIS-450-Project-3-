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
		cout << "External Hard Disk will now be initialized for you." << endl<<endl;
		
		extHardDisk->Disk_Init();

		return -1;
	}

	cout << "\nTHE UMD LIBRARY FILE SYSTEM HAS SUCESSEFULLy BOOTED!!" << endl;

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

int FileSystem :: FS_Sync()
{
	if (hasBooted == true)
	{
		cout << "\n\nSYNCING MEMORY TO EXTERNAL HARD DISK.....PLEASE WAIT A MOMENT!" << endl << endl;;

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
		return 0;
	}
	if (hasBooted == false && extHardDisk->init == false)
	{
		cout << "\n\nFILE SYSTEM CURRENTLY UNAVAILABLE......" << endl;
		osErrMsg = "ERR_FILE_RESET";
		cout << osErrMsg << endl << endl;;
	}
	return -1; 
}
