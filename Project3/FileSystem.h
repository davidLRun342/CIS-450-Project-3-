#pragma once
#include <string>
#include<iostream>
#include "ExtHardDisk.h"
#include "WrkHardDisk.h"

using namespace std;

class FileSystem
{
public: 

	string osErrMsg; 
	bool hasBooted = false;
	bool hasReseted = false;
	string FileSys = "UMDLibFS";

	ExtHardDisk *extHardDisk; 
	WrkHardDisk *wrkHardDisk;

	int FS_BOOT();
	int FS_Sync();
	int FS_Reset();
	
	int Disk_Load();
	int Disk_Save();
	int Disk_Write(int sector);
	int Disk_Read(int sector);
	int Dir_Read(string path, int size);
	int Dir_Unlink(string path);

};