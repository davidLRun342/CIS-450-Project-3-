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

string GetParent() {
	string parent;

	cout << "what directory do you want it to store in (Make sure to type in FULL PATHWAY including /root/...)?" << endl;
	cin >> parent;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	return parent;
}
string GetPath() {
	string path;
	cout << "What path would you like?" << endl;
	cin >> path;
	return path;
}

string FileName(string operation) {
	string fileName;

	cout << "what file would you like to "<< operation << endl;
	cin >> fileName;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	return fileName;
}

string DirectoryName() {
	string dir_name;

	cout << "what is the file Directory would you like it to be on (Make sure to type in FULL PATHWAY including /root/...)?" << endl;
	cin >> dir_name;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	return dir_name;
}

int FileD() {
	int fd;
	while (true) {
		cout << "What is the fd?" << endl;
		try {

			cin >> fd;

			if (cin.fail()) {
				throw - 1;
			}
			else {
				return fd;
			}
		}
		catch (...) {

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			fd = -1;
		}
	}
}

int GetSize() {
	int size = 0;
	while (true) {
		cout << "What is the size?" << endl;
		try {

			cin >> size;

			if (cin.fail()) {
				throw - 1;
			}
			else {
				return size;
			}
		}
		catch (...) {

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			size = -1;
		}

	}
}

int GetOffset() {
	int offset = 0;
	while (true) {
		cout << "What would be the  offset?" << endl;
		try {

			cin >> offset;

			if (cin.fail()) {
				throw - 1;
			}
			else {
				return offset;
			}
		}
		catch (...) {

			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			offset = -1;
		}
	}

}

int UserPage() {
	int input = 0;
	cout << "Please slect an option" << endl;
	cout << "1. Disk_Init()" << endl;
	cout << "2. FS_Boot()" << endl;
	cout << "3. FS_Sync()" << endl;
	cout << "4. FS_Reset()" << endl;
	cout << "5. WHD_File_Open()" << endl;
	cout << "6. WHD_File_Create()" << endl;
	cout << "7. WHD_File_Write()" << endl;
	cout << "8. WHD_File_Read()" << endl;
	cout << "9. WHD_File_Close()" << endl;
	cout << "10. WHD_File_Seek()" << endl;
	cout << "11. WHD_File_Unlink()" << endl;
	cout << "12. Dir_Create()" << endl;
	cout << "13. Dir_Read()" << endl;
	cout << "14. Dir_Unlink()" << endl;
	cout << "15. View File System Directory" << endl;
	cout << "16. View External Hard Disk Content" << endl;
	cout << "17. View RAM (Working Hard Disk) BUFFER Content" << endl;
	cout << "18. View Open File Table" << endl;
	cout << "0. Exit" << endl;
	try {

		cin >> input;

		if (cin.fail()) {
			throw - 1;
		}
		if (input < 0 || input > 18) {
			input = -1;
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

	while (true) {
		int userInput = 0;
		int response = 0;
		int fd = 0;
		int offset = 0;
		int size = 0;
		string parent= "";
		string file = "";
		string directory = "";
		string path="";
		userInput = UserPage();

		if (userInput == 1) {
			DirectiveLog << "System: Disk_Init()" << endl;
			response = UMDLibFS->extHardDisk->Disk_Init();
			if (response == 0) {
				DirectiveLog << "Return:  Disk_Init_Success" << endl;
			}
			if (response == -1) {
				DirectiveLog << "Return: " << UMDLibFS->osErrMsg << endl;
			}

		}

		else if (userInput == 2) {
			DirectiveLog << "System: FS_Boot()" << endl;
			response = UMDLibFS->FS_BOOT();

			if (response == 0) {
				DirectiveLog << "Return: FS_Boot_Success" << endl;
			}
			if (response == -1) {
				DirectiveLog << "Return: " << UMDLibFS->osErrMsg << endl;
			}
		}

		else if (userInput == 3) {
			DirectiveLog << "System: FS_Sync()" << endl;
			response = UMDLibFS->FS_Sync();
			if (response == 0) {
				DirectiveLog << "Return: FS_Sync_Success" << endl;
			}
			if (response == -1) {
				DirectiveLog << "Return: " << UMDLibFS->osErrMsg << endl;
			}
		}

		else if (userInput == 4) {
			DirectiveLog << "System: FS_Reset()" << endl;
			response = UMDLibFS->FS_Reset();
			if (response == 0) {
				DirectiveLog << "Return: FS_Reset_Success" << endl;
			}
			if (response == -1) {
				DirectiveLog << "Return: " << UMDLibFS->osErrMsg << endl;
			}
		}

		else if (userInput == 5) {
			DirectiveLog << "System: WHD_File_Open()" << endl;

			file = FileName("open");
			DirectiveLog << "User Input: " << file << endl;


			response = UMDLibFS->wrkHardDisk->File_Open(file);
			if (response == 0) {
				DirectiveLog << "Return: WHD_File_Open_Success" << endl;
			}
			if (response == -1) {
				DirectiveLog << "Return: " << UMDLibFS->wrkHardDisk->osErrMsg << endl;
			}
		}

		else if (userInput == 6) {
			DirectiveLog << "System: WHD_File_Create()" << endl;
			
			file = FileName("create");
			DirectiveLog << "User Input: " << file << endl;
			directory = DirectoryName();
			DirectiveLog << "User Input: " << directory<< endl;


			response = UMDLibFS->wrkHardDisk->File_Create(file, directory);
			if (response == 0) {
				DirectiveLog << "Return: WHD_File_Create_Success" << endl;
			}
			if (response == -1) {
				DirectiveLog << "Return: " << UMDLibFS->wrkHardDisk->osErrMsg << endl;
			}
		}

		else if (userInput == 7) {
			DirectiveLog << "System: WHD_File_Write()" << endl;
			
			UMDLibFS->wrkHardDisk->printOpenFileTable();
			cout << endl;

			fd = FileD();
			DirectiveLog << "User Input: " << fd << endl;

			size = GetSize();
			DirectiveLog << "User Input: " << size << endl;

			response = UMDLibFS->wrkHardDisk->File_Write(fd, size);
			if (response == 0) {
				DirectiveLog << "Return: WHD_File_Open_Success" << endl;
			}
			if (response == -1) {
				DirectiveLog << "Return: " << UMDLibFS->wrkHardDisk->osErrMsg << endl;
			}
		}

		else if (userInput == 8) {
			DirectiveLog << "System: WHD_File_Read()" << endl;

			UMDLibFS->wrkHardDisk->printOpenFileTable();
			cout << endl;

			fd = FileD();
			
			
			DirectiveLog << "User Input: " << fd << endl;

			response = UMDLibFS->wrkHardDisk->File_Read(fd);
			
			if (response == 0) {
				DirectiveLog << "Return: WHD_File_Return_Success" << endl;
			}
			if (response == -1) {
				DirectiveLog << "Return: " << UMDLibFS->wrkHardDisk->osErrMsg << endl;
			}
		}

		else if (userInput == 9) {
			DirectiveLog << "System: WHD_File_Close()" << endl;

			UMDLibFS->wrkHardDisk->printOpenFileTable();
			
			fd = FileD();
			DirectiveLog << "User Input: " << fd << endl;


			response = UMDLibFS->wrkHardDisk->File_Close(fd);
			
			if (response == 0) {
				DirectiveLog << "Return: WHD_File_Close_Success" << endl;
			}
			if (response == -1) {
				DirectiveLog << "Return: " << UMDLibFS->wrkHardDisk->osErrMsg << endl;
			}
		}

		else if (userInput == 10) {

			DirectiveLog << "System: WHD_File_Seek()" << endl;
			
			UMDLibFS->wrkHardDisk->printOpenFileTable();
			cout << endl;

			fd = FileD();
			DirectiveLog << "User Input: " << fd << endl;
			size = GetSize();
			DirectiveLog << "User Input: " << size << endl;
			offset = GetOffset();
			DirectiveLog << "User Input: " << offset << endl;

			UMDLibFS->wrkHardDisk->printOpenFileTable();

			response = UMDLibFS->wrkHardDisk->File_Seek(fd,size ,offset);
			if (response == 0) {
				DirectiveLog << "Return: WHD_File_Seek_Success" << endl;
			}
			if (response == -1) {
				DirectiveLog << "Return: " << UMDLibFS->wrkHardDisk->osErrMsg << endl;
			}
		}
		
		else if (userInput == 11) {
		DirectiveLog << "System: WHD_File_Unlink()" << endl;

		cout << endl;
		cout << "Make sure to type in the FULL PATHWAY name of the file to unlink....ie /root/a/b/c.txt" << endl << endl;

		file = FileName("unlink");
		
		DirectiveLog << "User Input: " << file << endl;

		response = UMDLibFS->wrkHardDisk->File_Unlink(file);

		if (response == 0) {
			DirectiveLog << "Return: WHD_File_Unlink_Return_Success" << endl;
		}
		if (response == -1) {
			DirectiveLog << "Return: " << UMDLibFS->wrkHardDisk->osErrMsg << endl;
		}
		}
		else if (userInput == 12) {
		DirectiveLog << "System: Dir_Create()" << endl;
		path = GetPath();
		DirectiveLog << "User Input: " << path << endl;
		parent = GetParent();
		DirectiveLog << "User Input: " << parent << endl;

		response = UMDLibFS->extHardDisk->Dir_Create(path, parent);

		if (response == 0) {
			DirectiveLog << "Return: Dir_Read_Success" << endl;
		}
		if (response == -1) {
			DirectiveLog << "Return: " << UMDLibFS->osErrMsg << endl;
		}
		}

		else if (userInput == 13) {
		DirectiveLog << "System: Dir_Read()" << endl;

		path = GetPath();
		DirectiveLog << "User Input: " << path << endl;
		size = GetSize();
		DirectiveLog << "User Input: " << size << endl;

		response = UMDLibFS->Dir_Read(path, size);
			if (response == 0) {
				DirectiveLog << "Return: Dir_Read_Success" << endl;
			}
			if (response == -1) {
				DirectiveLog << "Return: " << UMDLibFS->osErrMsg << endl;
			}
		}

		else if (userInput == 14) {
		DirectiveLog << "System: Dir_Unlink()" << endl;

		path = GetPath();
		DirectiveLog << "User Input: " << path << endl;

		response = UMDLibFS->Dir_Unlink(path);
			if (response == 0) {
				DirectiveLog << "Return: Dir_Unlink_Success" << endl;
			}
			if (response == -1) {
				DirectiveLog << "Return: " << UMDLibFS->osErrMsg << endl;
			}
		}
		
		else if (userInput == 15) {
		DirectiveLog << "System: View File System Directory" << endl;

		UMDLibFS->extHardDisk->printAllInode();

		}
		else if (userInput == 16) {
		DirectiveLog << "System: View External Hard Disk Content" << endl;

		UMDLibFS->extHardDisk->printHardDiskContent();

		}
		else if (userInput == 17) {
		DirectiveLog << "System: View RAM Buffer Content" << endl;

		UMDLibFS->wrkHardDisk->printBufferContent();

		}
		else if (userInput == 18) {
		DirectiveLog << "System: View Open File Table" << endl;

		UMDLibFS->wrkHardDisk->printOpenFileTable();

		}
		if (userInput == 0) {
			DirectiveLog << "Return: EXIT_SYSTEM" << endl;
			break;
		}

		if (userInput == -1) {
			DirectiveLog << "System: ERR_USER_INPUT" << endl;
		}
	}
	UMDLibFS->extHardDisk->printAllInode();

	

	system("pause");
	return 0;
}