#include "customls.h"
/**
 * get_dirlen - returns the number of files in a directory
 * @name: name of the dir
 *
 * Return: Number of files.
 */
int get_dirlen(char *name)
{
	int i = 0;
	DIR *directory = _opendir_safe(name);
	struct dirent *read;

	while ((read = readdir(directory)) != NULL)
	{
		if (read->d_type == DT_REG)
			i++;
	}
	closedir(directory);
	return (i);
}

/**
 * _opendir_safe - open dir and handle errors at the moment
 * @name: name of the dir
 *
 * Return: void.
 */
DIR *_opendir_safe(char *name)
{
	DIR *directory = opendir(name);
	int errnum;
	if (directory == NULL)
	{
		errnum = errno;
		switch(errnum)
		{
			case 13:
				fprintf(stderr, "hls: cannot open directory %s: "
						"Permission denied\n", name);
				exit(2);
			case 2:
				fprintf(stderr, "hls: cannot access %s: "
						"No such file or directory\n", name);
				exit(2);
		}
	}
	return directory;
}
