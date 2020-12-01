#include "customls.h"
/**
 * parse_data - initialized dir_len
 *
 * @argv: array with arguments
 * @arguments: array with args for the ls command
 *
 * Return: 0 if success
 **/
char **parse_data(char *argv[], char **arguments)
{
	int i = 0, arg_len = 0, file_len = 0, j = 0, counter = 0;
	int filestr_len;
	char **filenames = NULL;

	for (i = 1; argv[i] != NULL; i++)
	{
		if (*argv[i] == '-' && (argv[i] + 1) != NULL)
		{
			for (j = 1; j < _strlen(argv[i]); j++)
			{
				arg_len++;
			}
		}
		else
		{
			file_len++;
		}
	}
	*arguments = malloc(arg_len + 1);
	filenames = _calloc(file_len + 1, sizeof(char *));
	for (i = 1; argv[i] != NULL; i++)
	{
		if (*argv[i] == '-' && (argv[i] + 1) != NULL)
		{
			_strcat(*arguments, argv[i]);
		}
		else
		{
			filestr_len = _strlen(argv[i]) + 1;
			filenames[counter] = malloc(filestr_len);
			_strncpy(filenames[counter], argv[i], filestr_len);
			counter++;
		}
	}
	return (filenames);
}
