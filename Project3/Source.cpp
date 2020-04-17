#include<iostream>
#include<fstream>
#include<sstream>
#include<string.h>
#include<ostream>
#include "WrkHardDisk.h"
#include "ExtHardDisk.h"
#include "InodeBlock.h"
#include "FileSystem.h"
#include <time.h>
using namespace std;

int UserPage() {
	int input = 0;
	cout << "Please slect an option" << endl;
	cout << "1. Disk_Init()" << endl;
	cout << "2. FS_Boot()" << endl;
	cout << "3. FS_Sync()" << endl;
	cout << "4. FS_Reset()" << endl;
	cout << "0. Exit" << endl;
	try {

		cin >> input;

		if (cin.fail()) {
			throw - 1;
		}
	}
	catch (...) {

		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		input = -1;
	}
	return input;

}

int main()
{
	ofstream DirectiveLog;
	DirectiveLog.open("DirectiveLog");

/*THIS IS TO INITIALIZE AND CONNECT THE FILE SYSTEM, 
EXTERNAL HARD DISK AND WORKING HARD DISK TOGETHER*/

	ExtHardDisk* extHardDisk = new ExtHardDisk();
	WrkHardDisk* wrkHardDisk = new WrkHardDisk();
	FileSystem *UMDLibFS = new FileSystem();

	UMDLibFS->extHardDisk = extHardDisk;
	UMDLibFS->wrkHardDisk = wrkHardDisk;
	UMDLibFS->wrkHardDisk->extHardDisk = extHardDisk;
	/*
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

	UMDLibFS->wrkHardDisk->printOpenFileTable();

	UMDLibFS->wrkHardDisk->File_Read(6);
	UMDLibFS->wrkHardDisk->printBufferContent();
	UMDLibFS->wrkHardDisk->File_Write(2, 67);
	UMDLibFS->wrkHardDisk->File_Write(4, 389);
	UMDLibFS->wrkHardDisk->File_Write(6, 433);
	*/
	//UMDLibFS->wrkHardDisk->printOpenFileTable();

	//UMDLibFS->wrkHardDisk->printHardDiskContent();
	//UMDLibFS->extHardDisk->rootDir.printInodeInfo();

  // UMDLibFS->extHardDisk->printAllInode();

	//UMDLibFS->wrkHardDisk->printInodeBitmap();

	//UMDLibFS->extHardDisk->printAllInode();

	while (true) {
		int userInput = 0;
		int response = 0;
		string nullInfo = "";
		userInput = UserPage();

		if (userInput == 4) {
			UMDLibFS->extHardDisk->Disk_Init();
		}
		else if (userInput == 2) {

			DirectiveLog << "System: FS_Boot" << endl;
			response = UMDLibFS->FS_BOOT();

			if (response == 0) {
				DirectiveLog << "System: FS_Boot_Success" << endl;
			}
			if (response == -1) {
				DirectiveLog << "System: " << UMDLibFS->osErrMsg << endl;
			}
		}
		else if (userInput == 3) {
			DirectiveLog << "System: FS_Sync" << endl;
			response = UMDLibFS->FS_Sync();
			if (response == 0) {
				DirectiveLog << "Return: FS_Sync_Success" << endl;
			}
			if (response == -1) {
				DirectiveLog << "Return: " << UMDLibFS->osErrMsg << endl;
			}
		}
		else if (userInput == 4) {
			DirectiveLog << "System: FS_Reset_Success" << endl;
			response = UMDLibFS->FS_Reset();
			if (response == 0) {
				DirectiveLog << "Return: FS_Reset_Success" << endl;
			}
			if (response == -1) {
				DirectiveLog << "Return: " << UMDLibFS->osErrMsg << endl;
			}
		}
		else if (userInput == 5) {
			UMDLibFS->wrkHardDisk->File_Open(nullInfo);
		}
		else
			/*
			File open
			file create
			file close
			file inlink
			dir create
			dir size
			dir read
			dir unlink*/
			if (userInput == 0) {
				DirectiveLog << "Return: EXIT_SYSTEM" << endl;
				break;
			}
		if (userInput == -1) {
			DirectiveLog << "System: ERR_USER_INPUT" << endl;
		}
	}
	system("PAUSE");
	return 0;
}




