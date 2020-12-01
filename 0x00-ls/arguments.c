#include "customls.h"
/**
 * flag_setter - function to set flags by counting the arguments
 * @name: name of the dir
 *
 * Return: Number of files.
 */
arg_flags flag_setter(c_per var)
{
	int i = 0;
	arg_flags flags;

	flags.print_below = 0, flags.search_hidden = 0, flags.search_myhidden = 0;
	flags.long_listing = 0, flags.sort_by_size = 0, flags.sort_by_time = 0;
	flags.sort_reverse = 0, flags.recursive = 0;
	for (i = 0; *(*var.arguments + i); i++)
	{
		if (*(*var.arguments + i) == '1')
			flags.print_below = 1;
		else if (*(*var.arguments + i) == 'a')
			flags.search_hidden = 1;
		else if (*(*var.arguments + i) == 'A')
			flags.search_myhidden = 1;
		else if (*(*var.arguments + i) == 'l')
			flags.long_listing = 1;
		else if (*(*var.arguments + i) == 'r')
			flags.sort_reverse = 1;
		else if (*(*var.arguments + i) == 'S')
			flags.sort_by_size = 1;
		else if (*(*var.arguments + i) == 't')
			flags.sort_by_time = 1;
		else if (*(*var.arguments + i) == 'R')
			flags.recursive = 1;
		else
		{
			fprintf(stderr, "hls: invalid option -- '%c'\n", *(*var.arguments + i));
			fprintf(stderr, "Try 'hls --help' for more information.\n");
			free(*var.arguments);
			free_grid(*var.filenames, *var.file_len);
			exit(2);
		}
	}
	return (flags);
}
