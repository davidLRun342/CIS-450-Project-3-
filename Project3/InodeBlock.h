#pragma once
#include <string>
#include <iostream>

using namespace std;

/* Essentially a FILE and DIRECTORY is composed of Inode blocks and data blocks 
   so it's not neccessary to create FILE and DIRECTORY Class*/

using namespace std;
/*============DIRECTORY ENTRIES DATA STRUCTURE  - can be stored into a directory file*/
struct DirEntries
{
	string filename;
	int inode_num;

}; typedef struct DirEntries DirEntries;



/*=============FILE/DIRECT DATA STRUCTURE - Composed of Inode blocks and Data blocks*/
class InodeBlock
{
public:

	int file_sz;
	string file_type;
	int data_blocks[10];


	InodeBlock();


	void printInodeInfo();


};

class InodeDirectory : public InodeBlock
{
public:

	string direct_name;
	int inode_num;
	int entrySize = 0;
	DirEntries directory_entries[10];

	void printInodeDir();
};
