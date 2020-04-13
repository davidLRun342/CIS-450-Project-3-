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

	UMDLibFS->extHardDisk->Disk_Init();

	

	int s1= UMDLibFS->extHardDisk->Dir_Create("Camera");
	int s2 =UMDLibFS->extHardDisk->Dir_Create("Mechanic");
	int s3 =UMDLibFS->extHardDisk->Dir_Create("Engineer");
	int s4 =UMDLibFS->extHardDisk->Dir_Create("CIS");
	int s5 =UMDLibFS->extHardDisk->Dir_Create("Resume");
	int s6 =UMDLibFS->extHardDisk->Dir_Create("GoogleDocument");


	//int rec4 = UMDLibFS->FS_BOOT();
	//int rec2 = UMDLibFS->FS_Sync();
	int rec3 = UMDLibFS->FS_Reset();

	UMDLibFS->extHardDisk->rootDir.printInodeInfo();
	UMDLibFS->extHardDisk->printInodeBitmap();

	UMDLibFS->wrkHardDisk->rootDir.printInodeInfo();
	UMDLibFS->wrkHardDisk->printInodeBitmap();

	system("PAUSE");
	return 0;
}




