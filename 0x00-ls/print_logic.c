#include "customls.h"
/**
 * normal_print - prints a directory list by using readdir
 * @name: pointer to an open dir
 * @dir_len: number of directories to scan
 * Return: Nothing.
 */
void normal_print(char *name, int dir_len)
{
	int i = 0;
	DIR *directory;
	struct dirent *read;

	directory = _opendir_safe(name);
	read = readdir(directory);
	for (i = 0; i < dir_len; i++)
	{
		if (i != dir_len - 1)
			printf("%s\t", read->d_name);
		else
			printf("%s\n", read->d_name);
		read = readdir(directory);
	}
	closedir(directory);
}
