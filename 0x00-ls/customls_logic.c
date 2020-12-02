#include "customls.h"
/**
 * parse_data - initialized dir_len
 * @argv: program arguments
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
				*(*var.arguments + arg_count) = argv[i][j];
				arg_count++;
			}
		}
		else
		{
			filestr_len = _strlen(argv[i]) + 1;
			*(*var.filenames + counter) = malloc(filestr_len);
			_strncpy(*(*var.filenames + counter), argv[i], filestr_len);
			counter++;
		}
	}
}

/**
 * ls_answer - reads the args to give an according answer
 * @dir_name: directory name
 * @ls_flag: ls_flags from argument
 * @c_var: malloc data
 * @multiple: indicates if multiple values are valid to print
 *
 * Return: last exit code in case of a mistake
 **/
int ls_answer(char *dir_name, arg_flags ls_flag, c_per c_var, int multiple)
{
	int dir_len = 0;
	/*data search*/
	if (ls_flag.search_hidden)
	{
		dir_len = get_dirlen(dir_name, 1);
		if (dir_len == -1)
			return (-1);
		*c_var.directories = get_dir_names(dir_name, dir_len, 1);
	}
	else if (ls_flag.search_myhidden)
	{
		dir_len = get_dirlen(dir_name, 2);
		if (dir_len == -1)
			return (-1);
		*c_var.directories = get_dir_names(dir_name, dir_len, 2);
	}
	else
	{
	dir_len = get_dirlen(dir_name, 3);
		if (dir_len == -1)
			return (-1);
		*c_var.directories = get_dir_names(dir_name, dir_len, 3);
	}
	/*data sort*/
	/*data print*/
	if (multiple >= 2)
	{
		*c_var.dir_len = *c_var.dir_len + 1;
		printf("%s:\n", dir_name);
	}
	if (ls_flag.long_listing)
		printf("Coming soon\n");
	else if (ls_flag.print_below)
		below_print(*c_var.directories);
	else
		normal_print(*c_var.directories);
	if (*c_var.dir_len != multiple && multiple >= 2)
		printf("\n");
	return (dir_len == -1 ? 2 : 0);
}
