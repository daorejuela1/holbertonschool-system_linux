#include "_getline.h"
#define OLD_SIZE (((READ_SIZE + 1) * repetitions) + 1)
#define NEW_SIZE (((READ_SIZE + 1) * (repetitions + 1)) + 1)
static int repetitions;
static char *output;
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

	do {
		readed = read(fd, &buffer, READ_SIZE);
		if (readed == -1)
			return (NULL);
		if (readed)
		{
			temp = _realloc(output, OLD_SIZE, NEW_SIZE);
			if (temp == NULL)
				return (NULL);
			output = temp;
			buffer[readed] = 0;
			strcat(output, buffer);
			repetitions++;
		}
		index = getindex(output, 10);
	} while (readed == READ_SIZE && index == -1);
	if (index != -1 && output)
	{
		return (split_line(index));
	}
	if (output)
	{
		line = malloc(NEW_SIZE);
		if (line == NULL)
			return (NULL);
		strcpy(line, output);
		free(output);
		output = NULL;
		return (line);
		repetitions = 0;
	}
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
	char *array;
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
 *_strlen - returns data len
 *@s: input string
 *
 *Return:an int number
 *
 */
int _strlen(char *s)
{
	int counter = 0;

	while (*(s + counter) != 0)
	{
		counter++;
	}
	return (counter);
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
	strncpy(line, output, index);
	line[index] = 0;
	if (*(output + index + 1) == 0)
	{
		free(output);
		output = NULL;
		repetitions = 0;
	}
	else
	{
		temp = malloc(NEW_SIZE);
		strcpy(temp, output + index + 1);
		free(output);
		output = temp;
	}
	return (line);
}
