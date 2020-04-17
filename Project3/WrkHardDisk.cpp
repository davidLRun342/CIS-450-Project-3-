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


int WrkHardDisk::File_Create(string file, string directory)
{
	int cnt = 1;
	bool found = false;
	int temp = 0;
	if (extHardDisk->init == true)
	{
		if (file.length() < 16)
		{
		
			while (cnt < extHardDisk->totalInode && found == false)
			{
				if (extHardDisk->inode_bitmap[cnt].inode.entrySize < 10)
				{
					if (extHardDisk->inode_bitmap[cnt].inode.direct_name == directory)
					{
						//updates the directory entries for choosen directory
						extHardDisk->inode_bitmap[extHardDisk->totalInode].inode.direct_name = extHardDisk->inode_bitmap[cnt].inode.direct_name + "/" + file;
						extHardDisk->inode_bitmap[cnt].inode.directory_entries[extHardDisk->inode_bitmap[cnt].inode.entrySize].filename = extHardDisk->inode_bitmap[extHardDisk->totalInode].inode.direct_name;
						extHardDisk->inode_bitmap[cnt].inode.directory_entries[extHardDisk->inode_bitmap[cnt].inode.entrySize].inode_num = extHardDisk->inode_num_a;
						extHardDisk->inode_bitmap[cnt].inode.entrySize++;

						extHardDisk->inode_bitmap[cnt].inode.file_sz = extHardDisk->inode_bitmap[cnt].inode.file_sz + 20;

						extHardDisk->inode_bitmap[extHardDisk->totalInode].inode.file_type = "file";
						extHardDisk->inode_bitmap[extHardDisk->totalInode].inode.file_sz = 0;
						extHardDisk->inode_bitmap[extHardDisk->totalInode].inode.inode_num = extHardDisk->inode_num_a;

						extHardDisk->inode_num_a++;

						diskAlloc();
						extHardDisk->diskSectors[extHardDisk->inode_bitmap[cnt].address].inode = extHardDisk->inode_bitmap[cnt].inode;

						found = true;
						cout << "FILE CREATED SUCCESSFULLY!" << endl;
						return 0;
					}
				}
				cnt++;
			}

			if (found == false)
			{
				extHardDisk->inode_bitmap[extHardDisk->totalInode].inode.file_type = "file";
				extHardDisk->inode_bitmap[extHardDisk->totalInode].inode.direct_name = extHardDisk->rootDir.direct_name + "/" + file;
				extHardDisk->inode_bitmap[extHardDisk->totalInode].inode.file_sz = 0;
				extHardDisk->inode_bitmap[extHardDisk->totalInode].inode.inode_num = extHardDisk->inode_num_a;
				extHardDisk->inode_num_a++;

				//UPDATES THE DIRECTORY ENTRIES WITHIN THE ROOT DIRECTORY FILE
				extHardDisk->rootDir.directory_entries[extHardDisk->rootDir.entrySize].filename = extHardDisk->inode_bitmap[extHardDisk->totalInode].inode.direct_name;
				extHardDisk->rootDir.directory_entries[extHardDisk->rootDir.entrySize].inode_num = extHardDisk->inode_bitmap[extHardDisk->totalInode].inode.inode_num; // assign random inode number
				extHardDisk->rootDir.entrySize++;
				extHardDisk->rootDir.file_sz = extHardDisk->rootDir.file_sz + 20; // add 20 byte onto the size of the directory

				extHardDisk->inode_bitmap[0].inode = extHardDisk->rootDir;

				// LOOKS FOR FREE SECTOR SPACE IN HARD DISK AND UPDATES INODE BITMAP
				diskAlloc();

				extHardDisk->diskSectors[0].inode = extHardDisk->rootDir;

				cout << "FILE CREATED SUCCESSFULLY!" << endl;

				return 0;
			}

		}
		cout << "\nFile name must be less than 16 bytes or 16 characters long" << endl << endl;
	}

	cout << "ERR_FILE_CREATE" << endl << endl;
	cout << "ERROR IN CREATING THE FILE....." << endl << endl;

	return -1;
}
int WrkHardDisk::File_Open(string file)
{
	int cnt = 0; 
	bool success = false;
	int temp = 0;
	int j = 0;
	int k = 0;

	bool set = false;

	if (extHardDisk->init == true)
	{
		if (numOpenFile <= 10)
		{
			while (cnt < SECTOR_SZ && success == false )
			{
				if (extHardDisk->inode_bitmap[cnt].inode.file_type == "file")
				{
					if (extHardDisk->inode_bitmap[cnt].inode.direct_name == file)
					{

						while (j < 10)
						{
							if (opFileTable.entries[j].state == 0)
							{
								cout << "\n OPENNING " << file << " PLEASE WAIT....." << endl;
								opFileTable.entries[j].state = 1;
								opFileTable.entries[j].inodeblock = extHardDisk->inode_bitmap[cnt].inode;
								opFileTable.entries[j].address = extHardDisk->inode_bitmap[cnt].address;
								opFileTable.entries[j].fDes = 1 + fileDescr % 10;
								
								numOpenFile++;
								fileDescr++;
								cout << "\nFILE HAS OPENNED SUCESSFULLY" << endl << endl;
								success = true;
								return 0;
							}
							j++;
						}
					}
				}
				
				cnt++;
			}
			cout << "\nFILE COULD NOT BE FOUND !" << endl << endl;
			return -1;
		}

		cout << "\nTOO MANY FILES OPEN AT THE SAME TIME" << endl << endl;
		return -1;
	}
	
	cout << "DISK NOT INITIALIZED OR FS HAS NOT BOOTED" << endl;

	return -1;
}
int WrkHardDisk::File_Read(int fd)
{
	int i = 0;
	bool read = false;
	bool found = false;

	if (extHardDisk->init == true)
	{
			while (i < numOpenFile && found == false)
			{
				if (opFileTable.entries[i].fDes == fd)
				{
					
					buffer.inodeblock = opFileTable.entries[i].inodeblock;
					buffer.size = opFileTable.entries[i].inodeblock.file_sz;
					filePointer = buffer.size;

					found = true;

					cout << "\nFILE READ SUCCESSFULLY!" << endl << endl;
					return filePointer;
				}
				i++;
			}
		cout << "\nNO SUCH FILE IS OPENED" << endl << endl; 
		return -1;
	}
	
	cout << "\nEXTERNAL HARD DISK MUST BE INITIALIZED TO READ FILE" << endl << endl;
	return -1;
}
int WrkHardDisk::File_Write(int fd, int size )
{
	int i = 0;
	int temp = 0;
	int cnt = 0;
	bool write = true;

	filePointer = 0;

	if (extHardDisk->init == true)
	{
		if (buffer.size + size < 512)
		{	
			if (buffer.inodeblock.da_block_cnt < 10)
			{
				filePointer = size;
				buffer.size = size;
				
				buffer.inodeblock.file_sz = size;

				for (int i = 0; i < buffer.inodeblock.da_block_cnt; i++)
				{
					if (buffer.inodeblock.data_blocks[i].sizeHold < 512)
					{
						buffer.inodeblock.data_blocks[i].sizeHold += size;
					}
					
				}
				while (cnt < 10 &&  write == true)
				{
					if (opFileTable.entries[cnt].fDes == fd)
					{
						opFileTable.entries[cnt].inodeblock.file_sz  +=  buffer.inodeblock.file_sz;
						
						cout << "\nFILE HAS SUCCESSFULLY BEEN WRITTEN" << endl;
						for (int i = 0; i < totalInode; i++)
						{
							if (opFileTable.entries[cnt].inodeblock.direct_name == inode_bitmap[i].inode.direct_name)
							{
								inode_bitmap[i].inode.file_sz = opFileTable.entries[cnt].inodeblock.file_sz;
								diskSectors[inode_bitmap[i].address].inode.file_sz = opFileTable.entries[cnt].inodeblock.file_sz;
							}
						}
						write = true;
						buffer.size = 0;
						return opFileTable.entries[cnt].inodeblock.file_sz;
					}
					cnt++;
				}
			}
			cout << "DATA BLOCKS CAPACITY REACHED " << endl;
			return -1;
		}
		cout << "\nUNABLE TO WRITE THIS MUCH INTO BUFFER, PLEASE TRY A DIFFERENT SIZE" << endl << endl;
		return -1;
	}
		
	cout << "HARD DISK MUST BE INITIALIZED TO WRITE TO FILE " << endl << endl;
	return -1; 

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

void WrkHardDisk::diskAlloc()
{
	int flag = 0;
	int i = 0;
	// LOOKS FOR FREE SECTOR SPACE IN HARD DISK AND UPDATES INODE BITMAP

	while (flag == 0 && i < SECTOR_SZ)
	{
		if (extHardDisk->diskSectors[i].state == 0)
		{
			extHardDisk->diskSectors[i].state = 1;

			extHardDisk->inode_bitmap[extHardDisk->totalInode].address = extHardDisk->diskSectors[i].address;
			extHardDisk->diskSectors[i].inode = extHardDisk->inode_bitmap[extHardDisk->totalInode].inode; // stores into sector
			extHardDisk->data_bitmap[extHardDisk->diskSectors[i].address] = 1;
			extHardDisk->totalInode++;
			flag = 1;
		}
		i++;
	}
}
void WrkHardDisk::printInodeBitmap()
{
	cout << "\nWORKING HARD DISK INODE BITMAP ENTRY: " << endl << endl;

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
		cout << diskSectors[i].address << "         " << diskSectors[i].state << "         " << diskSectors[i].inode.direct_name <<"     File Size: " << diskSectors[i].inode.file_sz <<endl;
	}

}void WrkHardDisk::printDataBitMap()
{
	cout << "WORKING HARD DISK DATA BITMAP ENTRY: " << endl << endl;

	for (int i = 0; i < SECTOR_SZ; i++)
	{
		cout << "\t" << i << " : " << data_bitmap[i] << endl;
	}
}
void WrkHardDisk::printAllInode()
{
	cout << "WORKING HARD DISK ALL DIRECTORY LIST: " << endl << endl;
	for (int i = 0; i < totalInode; i++)
	{
		inode_bitmap[i].inode.printInodeInfo();
	}
}
void WrkHardDisk::printBufferContent()
{
	cout << "\nCONTENTS OF BUFFER IN WORKING HARD DISK: " << endl << endl;
	buffer.inodeblock.printInodeInfo();
	cout << "\nSIZE IN BUFFER: " << buffer.size << endl;
}

void WrkHardDisk:: printOpenFileTable()
{
	cout << "\nOPEN FILE TABLE: " << endl << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << "\tFILE NAME: " << opFileTable.entries[i].inodeblock.direct_name << "    ";
		cout << "FILE DESCRIPTOR: " << opFileTable.entries[i].fDes << "    ";
		cout << "ADDRESS(LOCATION): " << opFileTable.entries[i].address << "    " <<endl <<endl;
		
	}
}