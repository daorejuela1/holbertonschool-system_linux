#include "customls.h"
/**
 * normal_print - prints a list of filenames same lineand free the memory
 * @filenames: array of file names to print
 * Return: Nothing.
 */
void normal_print(char **filenames)
{
	int i = 0, dir_len = 0;

	while (filenames[dir_len])
		dir_len++;
	for (i = 0; i < dir_len; i++)
	{
		if (i != dir_len - 1)
			printf("%s  ", filenames[i]);
		else
			printf("%s\n", filenames[i]);
	}
	free_grid(filenames, dir_len);
}

/**
 * below_print - prints a list of filenames in new lineand free the memory
 * @filenames: array of file names to print
 * Return: Nothing.
 */
void below_print(char **filenames)
{
	int i = 0, dir_len = 0;

	while (filenames[dir_len])
		dir_len++;
	for (i = 0; i < dir_len; i++)
	{
		printf("%s\n", filenames[i]);
	}
	free_grid(filenames, dir_len);
}
