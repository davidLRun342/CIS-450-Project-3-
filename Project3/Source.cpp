#include<iostream>
#include<fstream>
#include<sstream>
#include<string.h>

#include "WrkHardDisk.h"
#include "ExtHardDisk.h"
#include "InodeBlock.h"
#include "FileSystem.h"
#include <time.h>
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
	UMDLibFS->wrkHardDisk->extHardDisk = extHardDisk;

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
	
	//UMDLibFS->Disk_Read(2);
	
	UMDLibFS->wrkHardDisk->File_Create("ACanddn.doc", "/root/Mechanic");
	UMDLibFS->wrkHardDisk->File_Create("Amazon1.doc", "/root/Mechanic");
	UMDLibFS->wrkHardDisk->File_Create("Amazon2.doc", "/root/Mechanic");
	UMDLibFS->wrkHardDisk->File_Create("Amazadn.cpp", "/root/Mechanic");
	UMDLibFS->wrkHardDisk->File_Create("Cannder.xmls", "/root/Mechanic");
	UMDLibFS->wrkHardDisk->File_Create("A.png", "/root/Mechanic");
	UMDLibFS->wrkHardDisk->File_Create("Cars.jpg", "/root/Mechanic");
	UMDLibFS->wrkHardDisk->File_Create("engine.jpg", "/root/Mechanic");
	UMDLibFS->wrkHardDisk->File_Create("oil.jpg", "/root/Engineer");
	UMDLibFS->wrkHardDisk->File_Create("Truck.jpg", "/root/Engineer");

	UMDLibFS->Disk_Load();
	
	UMDLibFS->wrkHardDisk->File_Open("/root/Mechanic/A.png");
	UMDLibFS->wrkHardDisk->File_Open("/root/Mechanic/ACanddn.doc");
	UMDLibFS->wrkHardDisk->File_Open("/root/Mechanic/Amazon1.doc");
	UMDLibFS->wrkHardDisk->File_Open("/root/Mechanic/Amazon2.doc");
	UMDLibFS->wrkHardDisk->File_Open("/root/Mechanic/Amazadn.cpp");
	UMDLibFS->wrkHardDisk->File_Open("/root/Mechanic/Cannder.xmls");
	UMDLibFS->wrkHardDisk->File_Open("/root/Engineer/oil.jpg");

	//UMDLibFS->wrkHardDisk->printOpenFileTable();

	UMDLibFS->wrkHardDisk->File_Read(6);
	UMDLibFS->wrkHardDisk->printBufferContent();
	UMDLibFS->wrkHardDisk->File_Write(2, 67);
	UMDLibFS->wrkHardDisk->File_Write(4, 389);
	UMDLibFS->wrkHardDisk->File_Write(6, 433);

	//UMDLibFS->wrkHardDisk->printOpenFileTable();

	UMDLibFS->wrkHardDisk->printHardDiskContent();

	//UMDLibFS->extHardDisk->rootDir.printInodeInfo();

    //UMDLibFS->extHardDisk->printAllInode();

	//UMDLibFS->wrkHardDisk->printInodeBitmap();

	//UMDLibFS->extHardDisk->printAllInode();
	system("PAUSE");
	return 0;
}




