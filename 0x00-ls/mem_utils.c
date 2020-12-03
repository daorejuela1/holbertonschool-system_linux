#include "customls.h"
/**
 *free_grid - allocate matrix in the form of memory
 *@grid: 2d matrix
 *@height: matrix row
 *Return: None
 */
void free_grid(char **grid, int height)
{
	int i;

	for (i = 0; i < height; i++)
		free(grid[i]);
	free(grid);
	grid = NULL;
}
/**
 *_calloc - using calloc with malloc
 *@nmemb: number of entries
 *@size: bytes of the entry
 *@mem: structure with allocs to free in case of error
 *Return: 0
 */
void *_calloc(unsigned int nmemb, unsigned int size, free_mem mem)
{
	char *pointer;

	if (size <= 0 || nmemb <= 0)
		return (NULL);
	pointer = malloc(nmemb * size);
	if (pointer == NULL)
	{
		if (*mem.c_var.arguments)
			free(mem.c_var.arguments);
		if (*mem.c_var.filenames)
			free_grid(*mem.c_var.filenames, *mem.c_var.file_len);
		if (*mem.c_var.directories)
			free_grid(*mem.c_var.directories, *mem.c_var.dir_len);
		if (*mem.sep.error_alloc)
			free_grid(*mem.sep.error_alloc, *mem.sep.error_len);
		if (*mem.sep.file_alloc)
			free_grid(*mem.sep.file_alloc, *mem.sep.file_len);
		if (*mem.sep.folder_alloc)
			free_grid(*mem.sep.folder_alloc, *mem.sep.folder_len);
		exit(2);
	}
	pointer = _memset(pointer, 0, nmemb * size);
	return ((void *)pointer);
}

/**
 *_memset -  sets memory values from *s to n quantity
 *@s: initial address
 *@b: value
 *@n: quantity of bytes
 *Return: pointer to the memory area of s
 */
char *_memset(char *s, char b, unsigned int n)
{
	char **pointer_to_s;
	unsigned int i;

	pointer_to_s = &s;
	for (i = 0; i < n; i++)
	{
	*(*pointer_to_s + i) = b;
	}
	return (*pointer_to_s);
}
