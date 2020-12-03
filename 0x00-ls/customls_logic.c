#include "customls.h"
#define INVALID "hls: unrecognized option '%s'\n"
/**
 * parse_data - initialized dir_len
 * @argv: program arguments
 * @mem: structure with malloc variables
 *
 * Return: 0 if success
 **/
void parse_data(char *argv[], free_mem mem)
{
	int i = 0, arg_len = 0, file_len = 0, j = 0, counter = 0;
	int	filestr_len = 0, arg_count = 0;

	for (i = 1; argv[i] != NULL; i++)
	{
		if (*argv[i] == '-' && (argv[i][1]) == '-')
		{
			if (argv[i][2] != 0)
			{
				fprintf(stderr, INVALID, argv[i]);
				fprintf(stderr, "Try 'hls --help' for more information.\n");
				exit(2);
			}
		}
		else if (*argv[i] == '-' && (argv[i][1]) != 0)
			for (j = 1; j < _strlen(argv[i]); j++)
				arg_len++;
		else
			file_len++;
	}
	*mem.c_var.arguments = _calloc(arg_len + 1, 1, mem);
	*mem.c_var.arg_len = arg_len;
	*mem.c_var.filenames = _calloc(file_len + 1, sizeof(char *), mem);
	*mem.c_var.file_len = file_len;
	for (i = 1; argv[i] != NULL; i++)
	{
		if (*argv[i] == '-' && (argv[i][1]) == '-' && (argv[i][2]) == 0)
		{
		}
		else if (*argv[i] == '-' && (argv[i][1]) != 0)
			for (j = 1; j < _strlen(argv[i]); j++)
				*(*mem.c_var.arguments + arg_count++) = argv[i][j];
		else
		{
			filestr_len = _strlen(argv[i]) + 1;
			*(*mem.c_var.filenames + counter) = _calloc(filestr_len, 1, mem);
			_strncpy(*(*mem.c_var.filenames + counter++), argv[i], filestr_len);
		}
	}
}

/**
 * ls_answer - reads the args to give an according answer
 * @dir_name: directory name
 * @ls_flag: ls_flags from argument
 * @c_var: malloc data
 * @multiple: indicates if multiple values are valid to print
 * @mem: structure with mallocs to free
 * Return: last exit code in case of a mistake
 **/
int ls_answer(char *dir_name, arg_flags ls_flag, c_per c_var,
		int multiple, free_mem mem)
{
	int dir_len = 0;
	/*data search*/
	if (ls_flag.search_hidden)
	{
		dir_len = get_dirlen(dir_name, 1);
		if (dir_len == -1)
			return (-1);
		*c_var.directories = get_dir_names(dir_name, dir_len, 1, mem);
	}
	else if (ls_flag.search_myhidden)
	{
		dir_len = get_dirlen(dir_name, 2);
		if (dir_len == -1)
			return (-1);
		*c_var.directories = get_dir_names(dir_name, dir_len, 2, mem);
	}
	else
	{
		dir_len = get_dirlen(dir_name, 3);
		if (dir_len == -1)
			return (-1);
		*c_var.directories = get_dir_names(dir_name, dir_len, 3, mem);
	}
	if ((*mem.sep.folder_len >= 2 && dir_len != -2) || multiple == 1)
		printf("%s:\n", dir_name);
	if (ls_flag.long_listing)
		long_listing(dir_name, *c_var.directories, multiple, mem);
	else if (ls_flag.print_below)
		below_print(*c_var.directories, multiple, mem);
	else
		normal_print(*c_var.directories, multiple, mem);
	if (*c_var.dir_len + 1 != *mem.sep.folder_len &&
			*mem.sep.folder_len >= 2 && dir_len != -2)
		printf("\n");
	return (dir_len == -1 ? 2 : 0);
}
