#include <iostream>
#include<string>
#include"FileSystem.h"


int FileSystem:: FS_BOOT()
{
	if (extHardDisk->sector_sz == 0 && extHardDisk->sector_unit == 0 && extHardDisk->magicnum == 0)
	{
		osErrMsg = "E_FILE_BOOT";
		cout << osErrMsg <<" - MUST INITIALIZE THE EXTERNAL HARD DISK! " << endl <<endl;
		cout << "External Hard Disk will now be initialized for you." << endl<<endl;
		extHardDisk->Disk_Init();

		return -1;
	}

	wrkHardDisk->sector_sz = extHardDisk->sector_sz;
	wrkHardDisk->sector_unit = extHardDisk->sector_unit;
	wrkHardDisk->rootDir = extHardDisk->rootDir;

	for (int i = 0; i < wrkHardDisk->sector_sz; i++)
	{
		wrkHardDisk->diskSectors[i] = extHardDisk->diskSectors[i];
		wrkHardDisk->inode_bitmap[i] = extHardDisk->inode_bitmap[i];
	}

	return 0;
}

int FileSystem :: FS_Sync()
{
	cout << "TRANSFERING DATA FROM EXTERNAL HARD DISK TO WORKING HARD DISK....." << endl;

	for (int i = 0; i < wrkHardDisk->sector_sz; i++)
	{
		extHardDisk->diskSectors[i] = wrkHardDisk->diskSectors[i];
		extHardDisk->inode_bitmap[i] = wrkHardDisk->inode_bitmap[i];
	}

	return 0;
}

int FileSystem:: FS_Reset()
{
	return 0; 
}
