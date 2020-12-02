#include "customls.h"
#define PER_DEN "hls: cannot open directory %s: Permission denied\n"
#define NO_EXIST "hls: cannot access %s: No such file or directory\n"
#define SHOW_ALL (read->d_type != DT_UNKNOWN)
#define M (_strcmp(read->d_name, ".") != 0 && _strcmp(read->d_name, "..") != 0)
#define SHOW (read->d_type != DT_UNKNOWN && _strfcmp(read->d_name, ".") != 0)
/**
 * get_dirlen - returns the number of files in a directory
 * @name: name of the dir
 * @selector: range selector
 * Return: Number of files.
 */
int get_dirlen(char *name, int selector)
{
	int i = 0;
	int condition = 0;
	DIR *directory = _opendir_safe(name);
	struct dirent *read;

	if (!directory)
	{
		if (errno == 20)
			return (1);
		return (-1);
	}
	while ((read = readdir(directory)) != NULL)
	{
		if (selector == 1)
			condition = SHOW_ALL;
		else if (selector == 2)
			condition = SHOW_ALL && M;
		else
			condition = SHOW;
		if (condition)
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
			default:
				return (NULL);
		}
	}
	return (directory);
}

/**
 * get_dir_names - gets directory names and store them in matrix
 * @name: name of the dir
 * @dir_len: quantity of files in directory
 * @selector: conditional selector
 * Return: matrix with all the normal directory names.
 */
char **get_dir_names(char *name, int dir_len, int selector)
{
	int i = 0, condition = 0;
	DIR *directory;
	char **files;
	struct dirent *read;

	directory = _opendir_safe(name);
	if (!directory)
	{
		if (errno == 20)
		{
			files = _calloc(2, sizeof(char *));
			files[0] = _calloc(_strlen(name) + 1, 1);
			_strncpy(files[0], name, _strlen(name));
			return (files);
		}
	}
	files = _calloc(dir_len + 1, sizeof(char *));
	while ((read = readdir(directory)) != NULL)
	{
		if (selector == 1)
			condition = SHOW_ALL;
		else if (selector == 2)
			condition = SHOW_ALL && M;
		else
			condition = SHOW;
		if (condition)
		{
			files[i] = _calloc(_strlen(read->d_name) + 1, 1);
			_strncpy(files[i], read->d_name, _strlen(read->d_name));
			i++;
		}
	}
	closedir(directory);
	return (files);
}
