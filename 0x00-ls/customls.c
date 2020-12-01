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

	if (argc == 1)
		dir_name = DEFAULT;
	else if (argc >= 2 && argv != NULL)
	{
		for (i = 1; i < argc; i++)
		{
			dir_name = argv[i];
			dir_len = get_dirlen(dir_name);
			if (dir_len == -1)
			{
				exit_code = 2;
				continue;
			}
			normal_print(dir_name, dir_len);
		}
	}
	return (exit_code);
}
