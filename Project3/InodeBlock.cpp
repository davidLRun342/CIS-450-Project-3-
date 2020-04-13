#include "InodeBlock.h"


InodeBlock::InodeBlock()
{
	file_sz = 0;
	file_type = "na";
	
	for (int i = 0; i < 10; i++)
	{
		data_blocks[i] = 0;
	}
}
 

void InodeBlock::printInodeInfo()
{
	cout << "File Type: " << file_type << endl;
	cout << "File Size: " << file_sz << endl;
	cout << "Data Blocks: " << endl;

	for (int i = 0; i < 10; i++)
	{
		cout <<"\t" <<data_blocks << endl;
	}
	
}
void  InodeDirectory :: printInodeDir()
{
	cout << "==========================================================" << endl;
	cout << "Directory name: " << direct_name << endl;
	cout << "Inode number: " << inode_num << endl;
	cout << "File Type: " << file_type << endl;
	cout << "File Size: " << file_sz << endl << endl;
	
	cout << "Directory Entries for " << direct_name <<" :" << endl << endl;

	for (int i = 0; i < entrySize; i++)
	{
		cout << "Entry " << i << " :" << "\n\tFile Name: " << directory_entries[i].filename << endl;
		cout << "\tFile Inode Number: " << directory_entries[i].inode_num << endl;

	}
	
}