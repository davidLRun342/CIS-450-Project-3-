#include "WrkHardDisk.h"


WrkHardDisk::WrkHardDisk()
{
	sector_sz = 0;
	sector_unit = 0;
}

int WrkHardDisk::File_Create(string file)
{
	return 0;
}
int WrkHardDisk::File_Open(string file)
{
	return 0;
}
int WrkHardDisk::File_Read(int fd, string buffer, int size)
{
	return 0;
}
int WrkHardDisk::File_Write(int fd, string buffer, int size)
{
	return 0;
}
int WrkHardDisk::File_Seek(int fd, int offset)
{
	return 0;
}
int WrkHardDisk::File_Close(int fd)
{
	return 0;
}
int WrkHardDisk::File_Unlink(string file)
{
	return 0;
}
int WrkHardDisk::Dir_Create(string path)
{

	return 0;
}
int WrkHardDisk::Dir_Size(string path)
{

	return 0;

}
int WrkHardDisk::Dir_Read(string path, string buffer, int size)
{
	return 0;
}
int WrkHardDisk::Dir_Unlink(string path)
{
	return 0;
}