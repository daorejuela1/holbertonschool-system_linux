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
	char *arguments = NULL;
	char **filenames = NULL;

	if (argc == 1)
		dir_name = DEFAULT;
	filenames = parse_data(argv, &arguments);
	for (i = 0; filenames[i] != NULL; i++)
	{
		dir_name = filenames[i];
		dir_len = get_dirlen(dir_name);
		if (dir_len == -1)
		{
			exit_code = 2;
			continue;
		}
		normal_print(dir_name, dir_len);
	}
	free(arguments);
	free_grid(filenames, i);
	return (exit_code);
}
