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
	int dir_len, exit_code = 0;
	c_per c_vars;
	arg_flags ls_flags;
	s_str s_sep;
	int direc_len = 0, file_len = 0, arg_len = 0;
	int error_count = 0, file_count = 0, folder_count = 0;
	char *arguments = NULL;
	char **filenames = NULL, **error_alloc = NULL, **file_alloc = NULL;
	char **directories = NULL, **folder_alloc = NULL;

	c_vars.arguments = &arguments, c_vars.filenames = &filenames;
	c_vars.directories = &directories, c_vars.dir_len = &direc_len;
	c_vars.file_len = &file_len, c_vars.arg_len = &arg_len;
	s_sep.error_alloc = &error_alloc, s_sep.file_alloc = &file_alloc;
	s_sep.folder_alloc = &folder_alloc, s_sep.file_len = &file_count;
	s_sep.folder_len = &folder_count, s_sep.error_len = &error_count;
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
	separate_files(c_vars, s_sep);
	scan_in_order(ls_flags, c_vars, s_sep);
	free_grid(folder_alloc, folder_count);
	free_grid(*c_vars.filenames, *c_vars.file_len);
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

/**
 * separate_files - get the number of valid filenames
 *
 * @c_vars: structure containing the filenames and arguments
 * @s_sep: structure containing the separators
 *
 * Return: number of valid names
 **/
int separate_files(c_per c_vars, s_str s_sep)
{
	int err_c = 0, file_c = 0, folder_c = 0, i = 0, dir_len = 0;
	char *dir_name;

	for (i = 0; *(*c_vars.filenames + i) != NULL; i++)
	{
		dir_len = get_dirlen(*(*c_vars.filenames + i), 5);
		if (dir_len == -1)
			*s_sep.error_len = *s_sep.error_len + 1;
		else if (dir_len == -2)
			*s_sep.file_len = *s_sep.file_len + 1;
		else
			*s_sep.folder_len = *s_sep.folder_len + 1;
	}
	*s_sep.error_alloc = _calloc(*s_sep.error_len + 1, sizeof(char *));
	*s_sep.file_alloc = _calloc(*s_sep.file_len + 1, sizeof(char *));
	*s_sep.folder_alloc = _calloc(*s_sep.folder_len + 1, sizeof(char *));
	for (i = 0; *(*c_vars.filenames + i) != NULL; i++)
	{
		dir_name = *(*c_vars.filenames + i);
		dir_len = get_dirlen(dir_name, 5); /* know if file is good */
		if (dir_len == -1)
		{
			*(*s_sep.error_alloc + err_c) = _calloc(_strlen(dir_name) + 1, 1);
			_strncpy(*(*s_sep.error_alloc + err_c++), dir_name, _strlen(dir_name));
		}
		else if (dir_len == -2)
		{
			*(*s_sep.file_alloc + file_c) = _calloc(_strlen(dir_name) + 1, 1);
			_strncpy(*(*s_sep.file_alloc + file_c++), dir_name, _strlen(dir_name));
		}
		else
		{
			*(*s_sep.folder_alloc + folder_c) = _calloc(_strlen(dir_name) + 1, 1);
			_strncpy(*(*s_sep.folder_alloc + folder_c++), dir_name, _strlen(dir_name));
		}
	}
	return (1);
}

/**
 * scan_in_order - acts in order to print the ls of the files
 *
 * @ls_flags: structure that contains the flags
 * @c_vars: structure containing the filenames and arguments
 * @s_sep: structure containing the separators
 *
 * Return: number of valid names
 **/
int scan_in_order(arg_flags ls_flags, c_per c_vars, s_str s_sep)
{
	char *dir_name;
	int exit_code = 0;
	int i = 0;

	for (i = 0; i < *s_sep.error_len; i++)
	{
		dir_name = *(*s_sep.error_alloc + i);
		ls_answer(dir_name, ls_flags, c_vars, 1);
		exit_code = 2;
	}
	free_grid(*s_sep.error_alloc, *s_sep.error_len);
	for (i = 0; i < *s_sep.file_len; i++)
	{
		dir_name = *(*s_sep.file_alloc + i);
		ls_answer(dir_name, ls_flags, c_vars, 1);
	}
	free_grid(*s_sep.file_alloc, *s_sep.file_len);
	if (*s_sep.folder_len && *s_sep.file_len)
		printf("\n");
	for (i = 0; i < *s_sep.folder_len; i++)
	{
		dir_name = *(*s_sep.folder_alloc + i);
		ls_answer(dir_name, ls_flags, c_vars, *s_sep.folder_len);
		*c_vars.dir_len = *c_vars.dir_len + 1;
	}
	return (exit_code);
}
