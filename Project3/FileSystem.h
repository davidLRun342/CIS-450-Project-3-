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

	string FileSys = "UMDLibFS";

	ExtHardDisk *extHardDisk; 
	WrkHardDisk *wrkHardDisk;

	int FS_BOOT();
	int FS_Sync();
	int FS_Reset();
	
};