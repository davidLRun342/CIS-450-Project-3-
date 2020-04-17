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
	cout << "DISK LOAD WAS NOT PERFORMED CORRECTLY.. PLEASE INITIALIZE DISK AND BOOT THE FILE SYSTEM!" << endl << endl; 
	return -1;
}
int FileSystem::Disk_Save()
{
	if (FS_Sync() == 0) return 0;
	
	cout << "ERROR, MEMORY WAS NOT ABLE TO SYNC TO EXTERNAL HARD DISK" << endl; 

	return -1;
}
int FileSystem::Disk_Write(int sector)
{
	int i = 0;
	bool sectFound = false;

	if (extHardDisk->init == true)
	{
		if (sector >= 0 && sector < SECTOR_SZ)
		{
			if (extHardDisk->diskSectors[sector].state == 0)
			{
				extHardDisk->diskSectors[sector].inode = wrkHardDisk->buffer.inodeblock;
				extHardDisk->diskSectors[sector].size = wrkHardDisk->buffer.size;
				cout << "DISK WRITE SUCCESSFUL " << endl;
				sectFound = true;
				return 0;
			}
			else if (extHardDisk->diskSectors[i].state == 1)
			{
				while (sectFound == false)
				{
					if (extHardDisk->diskSectors[i].state == 0)
					{
						extHardDisk->diskSectors[i].inode = wrkHardDisk->buffer.inodeblock;
						extHardDisk->diskSectors[sector].size = wrkHardDisk->buffer.size;
						cout << "\nDISK WRITE SUCCESSFUL " << endl <<endl;
						sectFound = true;
						return 0;
					}

					i++;
				}
			}
		}

		osErrMsg = "ERR_READ_INVALID_PARAM";
		cout << osErrMsg << endl << endl;
		cout << "SECTOR IS LESS THAN 0 OR GREATER THAN SECTOR MAX! " << endl << endl;
		return -1;
		
	}

	cout << "EXTERNAL HARD DISK NEED TO INITIALIZE BEFORE DISK WRITE! " << endl;

	return -1;
}
int FileSystem::Disk_Read(int sector )
{
	int i = 0;
	int temp = 0;
	bool sectFound = false;

	if (extHardDisk->init == true)
	{
		if (sector >=0 && sector < SECTOR_SZ)
		{
			while (sectFound == false)
			{
				if (extHardDisk->diskSectors[i].address == sector)
				{
					temp = wrkHardDisk->buffer.size + extHardDisk->diskSectors[i].inode.file_sz;

					if (temp < 512)
					{
						if (sector == 1)
						{
							wrkHardDisk->printInodeBitmap();
							wrkHardDisk->buffer.size = wrkHardDisk->buffer.size + wrkHardDisk->totalInode;
							cout << "\nDISK READ SUCCESSFUL " << endl << endl;
							sectFound = true;
							return 0;
						}
						else if (sector == 2)
						{
							cout << "\nCONTENTS IN BUFFER OF WORKING HARD DISK: " << endl << endl;
							extHardDisk->printDataBitMap();
							sectFound = true;
							return 0;
						}
						else if (sector > 2 || sector ==0)
						{
							wrkHardDisk->buffer.inodeblock = extHardDisk->diskSectors[i].inode; // store the disk sector info into buffer
							wrkHardDisk->buffer.size = wrkHardDisk->buffer.size + extHardDisk->diskSectors[i].inode.file_sz;
							cout << "\nDISK READ SUCCESSFUL " << endl << endl;
							sectFound = true;
							return 0;
						}					
					}

					cout << "BUFFER CANNOT CONTAIN ANY MORE DATA! " << endl << endl;
	
				}

				i++;
			}
		}	
	}
	extHardDisk->dskErrMsg = "E_READ_INVALID_PARAM";
	cout << "\n" << extHardDisk->dskErrMsg << endl << endl;
	cout << "EXTERNAL HARD DISK FAILED TO READ " << endl << endl;

	return -1;
}
int FileSystem::Dir_Read(string path, int size)
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
int FileSystem::Dir_Unlink(string path)
{
	int i = 0;
	
	bool found = false;

	if (extHardDisk->init == true)
	{
		if (path == "/root")
		{
			osErrMsg = "ERR_DEL_ROOT_DIR";
			cout << "\n" << osErrMsg << endl << endl;
			cout << "ROOT DIRECTORY CAN NEVER BE DELETED!" << endl << endl;
		}
		else if (path != "/root")
		{
			while (found == false && i < extHardDisk->totalInode)
			{
				if (extHardDisk->rootDir.directory_entries[i].filename == path)
				{
					/*Check to is it has child directories and will delete those*/
				
					for (int j = i + 1; j < extHardDisk->rootDir.entrySize; j++)
					{
						extHardDisk->rootDir.directory_entries[j -1 ] = extHardDisk->rootDir.directory_entries[j ];
						
					}
					extHardDisk->rootDir.directory_entries[extHardDisk->rootDir.entrySize - 1].filename = "";
					extHardDisk->rootDir.directory_entries[extHardDisk->rootDir.entrySize -1 ].inode_num = -1;
					extHardDisk->rootDir.entrySize--;

					extHardDisk->inode_bitmap[0].inode = extHardDisk->rootDir;

					found = true;
					cout << "\nUNLINK DIRECTORY SUCCESSFUL" << endl << endl;
					return 0;
				}

				i++;
			}
		}
	}
	cout << "\nFAIL TO UNLINK DIRECTORY" << endl << endl;
	return -1;
}
