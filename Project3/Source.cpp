#include<iostream>
#include<fstream>
#include<sstream>
#include<string.h>
#include "WrkHardDisk.h"
#include "ExtHardDisk.h"
#include "InodeBlock.h"
#include "FileSystem.h"


using namespace std;

int main()
{
	ExtHardDisk* extHardDisk = new ExtHardDisk();
	WrkHardDisk* wrkHardDisk = new WrkHardDisk();
	FileSystem *UMDLibFS = new FileSystem();



	UMDLibFS->extHardDisk = extHardDisk;
	UMDLibFS->wrkHardDisk = wrkHardDisk;


	UMDLibFS->FS_BOOT();

	extHardDisk->printInodeBitmap();
	extHardDisk->rootDir.printInodeDir();

	system("PAUSE");
	return 0;
}




