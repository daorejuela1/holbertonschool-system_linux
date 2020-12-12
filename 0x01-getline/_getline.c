#include "_getline.h"
#define OLD_SIZE (((READ_SIZE + 1) * current_file->repetitions) + 1)
#define NEW_SIZE (((READ_SIZE + 1) * ((current_file->repetitions) + 1)) + 1)
static streamf *file, *current_file;
/**
 * _getline - Gets a line from an input
 * @fd: file descriptor number
 *
 * Return: pointer to the memory
 */
char *_getline(const int fd)
{
	int readed = 0, index = 0;
	char buffer[READ_SIZE + 1], *line = NULL, *temp = NULL;

	if (fd == -1)
	{
		clean_files();
		return (NULL);
	}
	handlefd(fd);
	do {
		readed = read(current_file->fd, &buffer, READ_SIZE);
		if (readed == -1)
			return (NULL);
		if (readed)
		{
			temp = _realloc(current_file->output, OLD_SIZE, NEW_SIZE);
			if (temp == NULL)
				return (NULL);
			current_file->output = temp;
			buffer[readed] = 0;
			strcat(current_file->output, buffer);
			current_file->repetitions = current_file->repetitions + 1;
		}
		index = getindex(current_file->output, 10);
	} while (readed == READ_SIZE && index == -1);
	if (index != -1 && current_file->output)
		return (split_line(index));
	if (current_file->output)
	{
		line = malloc(NEW_SIZE);
		if (line == NULL)
			return (NULL);
		strcpy(line, current_file->output);
		free(current_file->output);
		current_file->output = NULL;
		return (line);
	}
	clean_files();
	return (NULL);
}
/**
 * getindex - search for a character inside an array
 * @array: array to search the character from
 * @chr: character to search for
 *
 * Return: index of the chr in array or -1 if not found
 */
int getindex(char *array, char chr)
{
	int index = 0;

	if (!array)
		return (-1);
	for (index = 0; *(array + index); index++)
	{
		if (array[index] == chr)
			return (index);
	}
	return (-1);
}

/**
 *_realloc - array with the range of integer
 *@ptr: array
 *@old_size: old array sizee
 *@new_size: new array size
 *Return: int array with min to max
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *array = NULL;
	unsigned int minimum, i;

	if (new_size == old_size)
		return (ptr);
	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	array = malloc(new_size);
	if (array == NULL)
	{
		free(ptr);
		return (NULL);
	}
	memset(array, 0, new_size);
	if (ptr == NULL)
	{
		return (array);
	}
	if (new_size > old_size)
		minimum = old_size;
	else
		minimum = new_size;
	for (i = 0; i < minimum; i++)
		array[i] = *((char *)ptr + i);
	free(ptr);
	return ((void *)array);
}

/**
 *handlefd - returns saved stream or created stream if not found
 *@fd: file descriptor number
 *
 *Return: NULL if something failed
 *
 */
char *handlefd(int fd)
{
	streamf *initial = NULL;

	current_file = file;
	initial = file;
	while (current_file)
	{
		if (fd == current_file->fd)
			break;
		current_file = current_file->next;
	}
	if (!current_file)
	{
		file = malloc(sizeof(streamf));
		if (!file)
			return (NULL);
		file->next = initial;
		file->fd = fd;
		file->output = NULL;
		file->repetitions = 0;
		current_file = file;
	}
	return (file->output);
}


/**
 *split_line - split line until new line character is found
 *@index: index of current solution
 *
 *Return: String used by split line
 *
 */
char *split_line(int index)
{
	char *line = NULL, *temp = NULL;

	line = malloc(index + 1);
	if (line == NULL)
		return (NULL);
	strncpy(line, current_file->output, index);
	line[index] = 0;
	if (*(current_file->output + index + 1) == 0)
	{
		free(current_file->output);
		current_file->output = NULL;
		current_file->repetitions = 0;
	}
	else
	{
		temp = malloc(NEW_SIZE);
		strcpy(temp, current_file->output + index + 1);
		free(current_file->output);
		current_file->output = temp;
	}
	return (line);
}

/**
 *clean_files - cleans all files allocs
 */
void clean_files(void)
{
	streamf *temp;

	while (file)
	{
		temp = file->next;
		if (file->output)
			free(file->output);
		free(file);
		file = temp;
	}
}
