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
	int dir_len;

	if (argc == 1)
		dir_name = DEFAULT;
	else if (argc >= 2)
	{
		dir_name = argv[1];
	}
	dir_len = get_dirlen(dir_name);
	normal_print(dir_name, dir_len);
	return (0);
}
