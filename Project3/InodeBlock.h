#pragma once
#include <string>

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

	int Dir_Create(string path);
	int Dir_Size(string path);
	int Dir_Read(string path, string buffer, int size);
	int Dir_Unlink(string path);

};


class InodeDirectory : public InodeBlock
{
public:

	string direct_name;
	int inode_num;
	DirEntries directory_entries[10];

	InodeDirectory();
};
