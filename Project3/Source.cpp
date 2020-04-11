#include<iostream>
#include<fstream>
#include<sstream>
#include<string.h>
#include "WrkHardDisk.h"
#include "ExtHardDisk.h"
#include "InodeBlock.h"

using namespace std;

int main()
{
	
	InodeBlock file;

	InodeDirectory directory;

	string a =directory.file_type = "direct";
	string b =directory.directory_entries[0].filename = "David.txt";
	int c = directory.directory_entries[0].inode_num = 1244;
	
	cout << "Directory name:" << a << endl;
	cout << "Directory entry 0 name:" << b << endl;
	cout << "Directory inode number:" << c << endl;
	
	
	system("PAUSE");
	return 0;
}