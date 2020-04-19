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
		data_bitmap[i] = 0;
	}
}
int ExtHardDisk::Disk_Init()
{
	magicnum = 4;
	sector_sz = SECTOR_SZ;
	sector_unit = SECTOR_UNIT;
	if (init == false) {
		init = true;
	cout << "\nEXTERNAL HARD DISK IS INITIALIZED! " << endl;
	//Initialize the root directory 
	rootDir.file_sz = 0;
	rootDir.inode_num = 0;
	rootDir.file_type = "dir";
	rootDir.direct_name = "/root";

	inode_bitmap[0].inode = rootDir;
	inode_bitmap[0].address = 0;
	totalInode++;

	diskSectors[0].state = 1;
	diskSectors[0].inode = rootDir;
	diskSectors[1].state = 1;
	diskSectors[2].state = 1;

	data_bitmap[0] = 1;
	data_bitmap[1] = 1;
	data_bitmap[2] = 1;

	return 0;
	}
	else {
	cout << "\nERROR!! EXRTERNAL HARD DISK HAS BEED INITIALIZED ALREADY!!" << endl;
	return -1;
	}
}

int ExtHardDisk::Dir_Create(string path, string directory)
{
	int cnt = 1;
	bool found = false;
	int temp = 0;
	if (init == true)
	{
		if (path.length() < 16)
		{
			while (cnt < totalInode && found == false)
			{
				if (inode_bitmap[cnt].inode.direct_name == directory)
				{
					//updates the directory entries for choosen directory
					inode_bitmap[totalInode].inode.direct_name = inode_bitmap[cnt].inode.direct_name + "/" + path;
					inode_bitmap[cnt].inode.directory_entries[inode_bitmap[cnt].inode.entrySize].filename = inode_bitmap[totalInode].inode.direct_name;
					inode_bitmap[cnt].inode.directory_entries[inode_bitmap[cnt].inode.entrySize].inode_num = inode_num_a;
					inode_bitmap[cnt].inode.entrySize++;

					inode_bitmap[cnt].inode.file_sz = inode_bitmap[cnt].inode.file_sz + 20;
				
					inode_bitmap[totalInode].inode.file_type = "dir";
					inode_bitmap[totalInode].inode.file_sz = 0;
					inode_bitmap[totalInode].inode.inode_num = inode_num_a;

					inode_num_a++;
		
					diskAlloc();
					diskSectors[inode_bitmap[cnt].address].inode = inode_bitmap[cnt].inode;
					diskSectors[inode_bitmap[cnt].address].size = inode_bitmap[cnt].inode.file_sz;
					found = true;
					cout << "DIRECTORY CREATED SUCCESSFULLY " << endl << endl;
					return 0;
				}
				cnt++;
			}

			if (found == false)
			{
				inode_bitmap[totalInode].inode.file_type = "dir";
				inode_bitmap[totalInode].inode.direct_name = rootDir.direct_name + "/" + path;
				inode_bitmap[totalInode].inode.file_sz = 0;
				inode_bitmap[totalInode].inode.inode_num = inode_num_a;
				inode_num_a++;

				//UPDATES THE DIRECTORY ENTRIES WITHIN THE ROOT DIRECTORY FILE
				rootDir.directory_entries[rootDir.entrySize].filename = inode_bitmap[totalInode].inode.direct_name;
				rootDir.directory_entries[rootDir.entrySize].inode_num = inode_bitmap[totalInode].inode.inode_num; // assign random inode number
				rootDir.entrySize++;
				rootDir.file_sz = rootDir.file_sz + 20; // add 20 byte onto the size of the directory
				
				inode_bitmap[0].inode = rootDir;
				
				// LOOKS FOR FREE SECTOR SPACE IN HARD DISK AND UPDATES INODE BITMAP
				diskAlloc();

				diskSectors[0].inode = rootDir;
				diskSectors[0].size = rootDir.file_sz;
				cout << "DIRECTORY CREATED SUCCESSFULLY " << endl << endl;
				return 0;
			}

			
		}
		cout << "\nDirectory name must be less than 16 bytes or 16 characters long" << endl << endl;
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
			flag = 1;
			return inode_bitmap[i].inode.file_sz;
		}
		i++;
	}
	return -1;

}

void ExtHardDisk::printInodeBitmap()
{
	cout << "\nEXTERNAL HARD DISK INODE BITMAP ENTRY: " << endl << endl;

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

void ExtHardDisk::diskAlloc()
{
	int flag = 0;
	int i = 0;
	// LOOKS FOR FREE SECTOR SPACE IN HARD DISK AND UPDATES INODE BITMAP

	while (flag == 0 && i < SECTOR_SZ)
	{
		if (diskSectors[i].state == 0)
		{
			diskSectors[i].state = 1;

			inode_bitmap[totalInode].address = diskSectors[i].address;
			diskSectors[i].inode = inode_bitmap[totalInode].inode; // stores into sector
			data_bitmap[diskSectors[i].address] = 1;
			totalInode++;
			flag = 1;
		}
		i++;
	}
}
void ExtHardDisk::printHardDiskContent()
{
	cout << "EXTERNAL HARD DISK CONTENT:" << endl << endl;
	cout << "Address " << "state" << "    File name  " << endl << endl;
	for (int i = 0; i < SECTOR_SZ; i++)
	{
		if (i == 1)
		{
			cout << diskSectors[i].address << "         " << diskSectors[i].state << "         " << "INODE BITMAP TABLE" << "                                          File size: " <<diskSectors[i].inode.file_sz <<endl;
		}
		else if (i == 2)
		{
			cout << diskSectors[i].address << "         " << diskSectors[i].state << "         " << "DATA BITMAP TABLE" << "                                             File size: " << diskSectors[i].inode.file_sz << endl;
		}

		cout << diskSectors[i].address << "         " << diskSectors[i].state << "         "<< diskSectors[i].inode.direct_name << "                                     File Size: " << diskSectors[i].inode.file_sz << endl;
	}

}
void ExtHardDisk::printDataBitMap()
{
	cout << "EXTERNAL HARD DISK DATA BITMAP ENTRY: " << endl << endl;

	for (int i = 0; i < SECTOR_SZ; i++)
	{
		cout << "\t" << i << " : " << data_bitmap[i] << endl; 
	}  
}

void ExtHardDisk::printAllInode()
{
	cout << "EXTERNAL HARD DISK ALL DIRECTORY LIST: " << endl << endl;
	for (int i = 0; i < totalInode; i++)
	{
		inode_bitmap[i].inode.printInodeInfo();
	}
}