#include <iostream>
#include<string>
#include"FileSystem.h"


int FileSystem::FS_BOOT()
{

	if (extHardDisk->init == false)
	{
		osErrMsg = "ERR_FILE_BOOT";
		cout << "\n\n" << osErrMsg << " - MUST INITIALIZE THE EXTERNAL HARD DISK! " << endl << endl;
		cout << "External Hard Disk will now be initialized for you....." << endl << endl;

		extHardDisk->Disk_Init();

		return -1;
	}
	if (hasBooted == false && hasReseted == false) {
		hasBooted = true;
		cout << "\nTHE UMD LIBRARY FILE SYSTEM HAS SUCESSEFULLy BOOTED!!" << endl;

		Disk_Load();
		return 0;
	}
	if (hasBooted == true && hasReseted == false) {
		osErrMsg = "ERR_FILE_BOOT";
		cout << "\nTHE UMD LIBRARY FILE SYSTEM HAS ALREADY BEEN BOOTED!!" << endl;
		return -1;
	}
	if (hasBooted == true && hasReseted == true) {
		hasReseted = false;
		cout << "\nTHE UMD LIBRARY FILE SYSTEM HAS BEEN REBOOTED!!" << endl;
		return 0;
	}

}

int FileSystem::FS_Sync()
{
	if (hasBooted == true && hasReseted == false)
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
	else {
		cout << "\n\nSYSTEM MUST BE BOOTED IN ORDER TO SYNC !!! PLEASE BOOT FS!" << endl << endl;
		osErrMsg = "ERR_FILE_SYNC";
		return -1;
	}

}

int FileSystem::FS_Reset()
{
	if (hasBooted == true && hasReseted == false)
	{
		FS_Sync();
		hasReseted = true;
		return 0;
	}
	if (hasBooted == true && hasReseted == true) {

		osErrMsg = "ERR_FILE_RESET";
		cout << "file system is already locked" << endl;
		return -1;
	}
	if (hasBooted == false || extHardDisk->init == false)
	{
		osErrMsg = "ERR_FILE_RESET";
		cout << osErrMsg << endl << endl;
		cout << "SYSTEM SHUTDOWN...." << endl;
		cout << "\nFILE SYSTEM CURRENTLY UNAVAILABLE......" << endl;

		return -1;
	}
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
	else {
		osErrMsg = "ERR_DSK_LOAD";
		cout << "DISK LOAD WAS NOT PERFORMED CORRECTLY.. PLEASE INITIALIZE DISK AND BOOT THE FILE SYSTEM!" << endl << endl;
		return -1;
	}
}

int FileSystem::Disk_Save()
{
	FS_Sync();
	if (FS_Sync() == 0) {
		return 0;
	}
	else {
	cout << "ERROR, MEMORY WAS NOT ABLE TO SYNC TO EXTERNAL HARD DISK" << endl;

	return -1;
	}
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
		else {
			osErrMsg = "ERR_READ_INVALID_PARAM";
			cout << osErrMsg << endl << endl;
			cout << "SECTOR IS LESS THAN 0 OR GREATER THAN SECTOR MAX! " << endl << endl;
			return -1;
		}
	}
	else {
		osErrMsg = "ERR_READ_INVALID_PARAM";
		cout << "EXTERNAL HARD DISK NEED TO INITIALIZE BEFORE DISK WRITE! " << endl;
		return -1;
	}

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
	else {
		extHardDisk->dskErrMsg = "E_READ_INVALID_PARAM";
		cout << "\n" << extHardDisk->dskErrMsg << endl << endl;
		cout << "EXTERNAL HARD DISK FAILED TO READ " << endl << endl;

		return -1;
	}

}

int FileSystem::Dir_Read(string path, int size)
{
	bool found = false;
	int i = 0;
	int temp = 0;
	if (extHardDisk->init == true)
	{
	
		while (found == false)
		{
			if (size < extHardDisk->inode_bitmap[i].inode.file_sz)
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
					cout << "BUFFER CANNOT STORE THAT LOAD OF DATA!!" << endl;

					return -1;
				}
			}

			i++;
		}
		osErrMsg = "ERR_DIR_READ";
		cout << "PATH DOES NOT EXIST!!" << endl;
		return -1;
	}
	cout << "DISK MUST BE INITIALIZED TO READ DIRECTORY" << endl << endl;
	return -1;
}

int FileSystem::Dir_Unlink(string path)
{
	int i = 0;
	int j = 0;
	int cntSect = 0;
	bool found = false;
	InodeDirectory temp[100];
	int temp_cnt = 0;
	
	bool suc1 = false;
	bool suc2 = false;
	bool suc3 = false;
	bool suc4 = false;

	InodeDirectory empty;

	string tempSr = "";


	if (extHardDisk->init == true)
	{
		
		if (path == "/root")
		{
			osErrMsg = "ERR_DEL_ROOT_DIR";
			cout << "\n" << osErrMsg << endl << endl;
			cout << "ROOT DIRECTORY CAN NEVER BE DELETED!" << endl << endl;
			return -1;
		}
		else if (path != "/root")
		{
			//"ERASE CONNECTION WITH PARENT DIRECTORY"
			for (int i = 0; i < extHardDisk->totalInode; i++)
			{
				for (int j = 0; j < extHardDisk->inode_bitmap[i].inode.entrySize; j++)
				{
					
					if (extHardDisk->inode_bitmap[i].inode.directory_entries[j].filename == path)
					{

						for (int cnt =j + 1; cnt < extHardDisk->inode_bitmap[i].inode.entrySize; cnt++)
						{
							extHardDisk->inode_bitmap[i].inode.directory_entries[cnt - 1] = extHardDisk->inode_bitmap[i].inode.directory_entries[cnt];

						}
						extHardDisk->inode_bitmap[i].inode.directory_entries[j + 1].filename = "";
						extHardDisk->inode_bitmap[i].inode.directory_entries[j + 1].inode_num = -1;
						extHardDisk->inode_bitmap[i].inode.entrySize--;
						suc1 = true;
					}
				}
			} 
			while ( cntSect < extHardDisk->sector_sz && found == false)
			{
				if (extHardDisk->diskSectors[cntSect].inode.direct_name == path)
				{
					extHardDisk->diskSectors[cntSect].inode = empty;
					extHardDisk->diskSectors[cntSect].state = 0;
					extHardDisk->diskSectors[cntSect].size = 0;
					found = true; 
				}
				cntSect++;
			}
			while (i <= extHardDisk->totalInode)
			{
				for (int cnt1 = 0; cnt1 < extHardDisk->inode_bitmap[i].inode.direct_name.length(); cnt1++)
				{
					tempSr += extHardDisk->inode_bitmap[i].inode.direct_name[cnt1];

					if (tempSr == path)
					{
						extHardDisk->inode_bitmap[i].inode = empty;
						extHardDisk->diskSectors[extHardDisk->inode_bitmap[i].address].inode = empty;
						extHardDisk->diskSectors[extHardDisk->inode_bitmap[i].address].state = 0;
						extHardDisk->diskSectors[extHardDisk->inode_bitmap[i].address].size = 0;
						extHardDisk->data_bitmap[extHardDisk->inode_bitmap[i].address] = 0;

						suc2 = true;
						tempSr = "";
					}
				}
				tempSr = "";
				i++;
			}
			 // copies the remaining directories into temp array 
			while (j < extHardDisk->totalInode)
			{
				if (extHardDisk->inode_bitmap[j].inode.file_type != "na")
				{
					suc3 = true;
					temp[temp_cnt] = extHardDisk->inode_bitmap[j].inode;
					temp_cnt++;		
				}
				j++;
			}
			//UPDATE INODE TABLE IN THE EXTERNAL HARD DISK 

			for (int i = 0; i < extHardDisk->totalInode; i++)
			{
				suc4 = true;
				extHardDisk->inode_bitmap[i].inode = temp[i];
			}
			extHardDisk->totalInode= temp_cnt;
			
			if (suc1 == true && suc2 == true && suc3 == true && suc4 == true)
			{
				cout << "DIRECTORY SUCCESSFULLY UNLINKED " << endl << endl; 
				return 0;
			}

		}
		cout << "DIRECTORY IS NOT FOUND, PLEASE TYPE IN FULL PATHWAY NAME!!" << endl << endl;
		return -1;
	}

	osErrMsg = " DISK MUST BE INITIALIZED TO UNLINK DIRECTORY";

	cout << "\nDISK MUST BE INITIALIZED TO UNLINK DIRECTORY" << endl << endl;
	return -1;
}
