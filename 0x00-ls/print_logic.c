#include "customls.h"
/**
 * normal_print - prints a list of filenames same lineand free the memory
 * @filenames: array of file names to print
 * @mode: printing files or directories
 * @mem: structure with all the memory
 * Return: Nothing.
 */
void normal_print(char **filenames, int mode, free_mem mem)
{
	int i = 0, dir_len = 0, print_len = 0;
	char **printvar = NULL;

	if (mode != -1)
		printvar = filenames;
	else
		printvar = *mem.sep.file_alloc;
	while (filenames[dir_len])
		dir_len++;
	while (printvar[print_len])
		print_len++;
	for (i = 0; i < print_len; i++)
	{
		if (i != print_len - 1)
			printf("%s  ", printvar[i]);
		else
			printf("%s\n", printvar[i]);
	}
	free_grid(filenames, dir_len);
}

/**
 * below_print - prints a list of filenames in new lineand free the memory
 * @filenames: array of file names to print
 * @mode: printing files or directories
 * @mem: structure with all the memory
 * Return: Nothing.
 */
void below_print(char **filenames, int mode, free_mem mem)
{
	int i = 0, dir_len = 0, print_len = 0;
	char **printvar = NULL;

	if (mode != -1)
		printvar = filenames;
	else
		printvar = *mem.sep.file_alloc;
	while (filenames[dir_len])
		dir_len++;
	while (printvar[print_len])
		print_len++;
	for (i = 0; i < print_len; i++)
	{
		printf("%s\n", printvar[i]);
	}
	free_grid(filenames, dir_len);
}
