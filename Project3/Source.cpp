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

/*THIS IS TO INITIALIZE AND CONNECT THE FILE SYSTEM, 
EXTERNAL HARD DISK AND WORKING HARD DISK TOGETHER*/

	ExtHardDisk* extHardDisk = new ExtHardDisk();
	WrkHardDisk* wrkHardDisk = new WrkHardDisk();
	FileSystem *UMDLibFS = new FileSystem();

	UMDLibFS->extHardDisk = extHardDisk;
	UMDLibFS->wrkHardDisk = wrkHardDisk;

	UMDLibFS->extHardDisk->Disk_Init();

	int s1= UMDLibFS->extHardDisk->Dir_Create("Camera","");
	int s2 =UMDLibFS->extHardDisk->Dir_Create("Mechanic", "");
	int s3 =UMDLibFS->extHardDisk->Dir_Create("Engineer", "");
	int s4 = UMDLibFS->extHardDisk->Dir_Create("Schedule", "/root/Mechanic");
	int s5 = UMDLibFS->extHardDisk->Dir_Create("SeedPlant", "/root/Mechanic/Schedule");
	int s6 = UMDLibFS->extHardDisk->Dir_Create("Flower", "/root/Mechanic/Schedule");
	int s7 = UMDLibFS->extHardDisk->Dir_Create("Ff", "/root/Mechanic/Schedule");
	int s8 = UMDLibFS->extHardDisk->Dir_Create("sand", "/root/Mechanic/Schedule");
	int s9 = UMDLibFS->extHardDisk->Dir_Create("Fr", "/root/Mechanic/Schedule");
	int s10 = UMDLibFS->extHardDisk->Dir_Create("r", "/root/Mechanic/Schedule");

	int rec4 = UMDLibFS->FS_BOOT();
	
	UMDLibFS->Dir_Read("/root/Mechanic/Schedule", UMDLibFS->wrkHardDisk->buffer, 412);
	UMDLibFS->Dir_Read("/root/Mechanic/Schedule", UMDLibFS->wrkHardDisk->buffer, 412);
	UMDLibFS->Dir_Read("/root/Mechanic/Schedule", UMDLibFS->wrkHardDisk->buffer, 412);
	UMDLibFS->Dir_Read("/root/Mechanic/Schedule", UMDLibFS->wrkHardDisk->buffer, 412);

	//UMDLibFS->extHardDisk->printAllInode();
	//UMDLibFS->extHardDisk->printInodeBitmap();

	//UMDLibFS->wrkHardDisk->printAllInode();
	//UMDLibFS->wrkHardDisk->printInodeBitmap();

	system("PAUSE");
	return 0;
}




