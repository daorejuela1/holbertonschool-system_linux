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
		if (read->d_type != DT_UNKNOWN)
		{
			i++;
		}
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

/**
 * get_dir_names - gets directory names and store them in matrix
 * @name: name of the dir
 * @dir_len: quantity of files in directory
 *
 * Return: matrix with all the normal directory names.
 */
char **get_dir_names(char *name, int dir_len)
{
	int i = 0;
	DIR *directory;
	char **files;
	struct dirent *read;

	directory = _opendir_safe(name);
	files = _calloc(dir_len + 1, sizeof(char *));
	while ((read = readdir(directory)) != NULL)
	{
		if (read->d_type != DT_UNKNOWN)
		{
			files[i] = _calloc(_strlen(read->d_name) + 1, 1);
			_strncpy(files[i], read->d_name, _strlen(read->d_name));
			i++;
		}
	}
	closedir(directory);
	return (files);
}
