#include "customls.h"
/**
 * parse_data - initialized dir_len
 *
 * @var: structure with malloc variables
 *
 * Return: 0 if success
 **/
void parse_data(char *argv[], c_per var)
{
	int i = 0, arg_len = 0, file_len = 0, j = 0, counter = 0;
	int filestr_len = 0, arg_count = 0;

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
	*var.arguments = _calloc(arg_len + 1, 1);
	*var.arg_len = arg_len;
	*var.filenames = _calloc(file_len + 1, sizeof(char *));
	*var.file_len = file_len;
	for (i = 1; argv[i] != NULL; i++)
	{
		if (*argv[i] == '-' && (argv[i] + 1) != NULL)
		{
			for (j = 1; j < _strlen(argv[i]); j++)
			{
				*(*var.arguments+arg_count) = argv[i][j];
				arg_count++;
			}
		}
		else
		{
			filestr_len = _strlen(argv[i]) + 1;
			*var.filenames[counter] = malloc(filestr_len);
			_strncpy(*var.filenames[counter], argv[i], filestr_len);
			counter++;
		}
	}
}
