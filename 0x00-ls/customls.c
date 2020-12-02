#include "customls.h"
#define DEFAULT "."
/**
 * main - initialized dir_len
 *
 * @argc: number of arguments
 * @argv: array with arguments
 *
 * Return: 0 if success
 **/
int main(int argc, char *argv[])
{
	char *dir_name;
	int dir_len, i, exit_code = 0;
	c_per c_vars;
	arg_flags ls_flags;
	int direc_len = 0, file_len = 0, arg_len = 0, multiple = 0;
	char *arguments = NULL;
	char **filenames = NULL;
	char **directories = NULL;

	c_vars.arguments = &arguments, c_vars.filenames = &filenames;
	c_vars.directories = &directories, c_vars.dir_len = &direc_len;
	c_vars.file_len = &file_len, c_vars.arg_len = &arg_len;
	if (argc == 1)
		dir_name = DEFAULT;
	parse_data(argv, c_vars);
	ls_flags = flag_setter(c_vars);
	free(*c_vars.arguments);
	if (*(*c_vars.filenames) == NULL)
	{
		dir_name = DEFAULT;
		dir_len = ls_answer(dir_name, ls_flags, c_vars, 1);
		if (dir_len == -1)
			exit_code = 2;
	}
	multiple = gets_valid(*c_vars.filenames);
	for (i = 0; *(*c_vars.filenames + i) != NULL; i++)
	{
		dir_name = *(*c_vars.filenames + i);
		dir_len = ls_answer(dir_name, ls_flags, c_vars, multiple);
		*c_vars.dir_len = *c_vars.dir_len + 1; 
		if (dir_len == -1)
		{
			exit_code = 2;
			continue;
		}
	}
	free_grid(*c_vars.filenames, i);
	return (exit_code);
}

/**
 * gets_valid - get the number of valid filenames
 *
 * @fold_names: array with folder names
 *
 * Return: number of valid names
 **/
int gets_valid(char **fold_names)
{
	int i = 0, dir_len = 0, multiple = 0;
	char *dir_name;

	for (i = 0; *(fold_names + i) != NULL; i++)
	{
		dir_name = *(fold_names + i);
		dir_len = get_dirlen(dir_name, 4);
		if (dir_len >= 1)
			multiple++;
	}
	return (multiple);
}

