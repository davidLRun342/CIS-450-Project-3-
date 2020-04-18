#include "InodeBlock.h"


InodeBlock::InodeBlock()
{
	file_sz = 0;
	file_type = "na";
	
	for (int i = 0; i < 10; i++)
	{
		data_blocks[i].sizeHold = 0;
	}
}
 

void  InodeDirectory :: printInodeInfo()
{
	if (file_type == "dir")
	{
		cout << "==========================================================" << endl;
		cout << "Directory name: " << direct_name << endl;
		cout << "Inode number: " << inode_num << endl;
		cout << "File Type: " << file_type << endl;
		cout << "File Size: " << file_sz << endl;

		cout << "Directory Entries for " << direct_name << " :" << endl << endl;
		
		if (entrySize == 0)
		{
			cout << "NONE CURRENTLY" << endl << endl;
		}

		for (int i = 0; i < entrySize; i++)
		{
			cout << "Entry " << i << " :" << "\n\tFile Name: " << directory_entries[i].filename << endl;
			cout << "\tFile Inode Number: " << directory_entries[i].inode_num << endl;

		}
	}
	else if (file_type == "file")
	{
		cout << "==========================================================" << endl;
		cout << "File name: " << direct_name << endl;
		cout << "File Type: " << file_type << endl;
		cout << "File Size: " << file_sz << endl;

		cout << "Data Blocks for " << direct_name << " :" << endl << endl;
		
		if (da_block_cnt == 0)
		{
			cout << "NONE CURRENTLY" << endl << endl;
		}
		
		for (int i = 0; i < da_block_cnt; i++)
		{
			cout << "\tsize: " << data_blocks[i].sizeHold << endl;
		}
	}
	
	
}