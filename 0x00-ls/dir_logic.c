#include "customls.h"
#define PER_DEN "hls: cannot open directory %s: Permission denied\n"
#define NO_EXIST "hls: cannot access %s: No such file or directory\n"
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

	if (!directory)
		return (-1);
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
		switch (errnum)
		{
			case 13:
				fprintf(stderr, PER_DEN, name);
				return (NULL);
			case 2:
				fprintf(stderr, NO_EXIST, name);
				return (NULL);
		}
	}
	return (directory);
}
