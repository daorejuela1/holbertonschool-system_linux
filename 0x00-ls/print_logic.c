#include "customls.h"
/**
 * normal_print - prints a list of filenames same lineand free the memory
 * @filenames: array of file names to print
 * @mode: printing files or directories
 * @mem: structure with all the memory
 * Return: Nothing.
 */
void normal_print(char **filenames, int mode, free_mem mem)
{
	int i = 0, dir_len = 0, print_len = 0;
	char **printvar = NULL;

	if (mode != -1)
		printvar = filenames;
	else
		printvar = *mem.sep.file_alloc;
	while (filenames[dir_len])
		dir_len++;
	while (printvar[print_len])
		print_len++;
	for (i = 0; i < print_len; i++)
	{
		if (i != print_len - 1)
			printf("%s  ", printvar[i]);
		else
			printf("%s\n", printvar[i]);
	}
	free_grid(filenames, dir_len);
}

/**
 * below_print - prints a list of filenames in new lineand free the memory
 * @filenames: array of file names to print
 * @mode: printing files or directories
 * @mem: structure with all the memory
 * Return: Nothing.
 */
void below_print(char **filenames, int mode, free_mem mem)
{
	int i = 0, dir_len = 0, print_len = 0;
	char **printvar = NULL;

	if (mode != -1)
		printvar = filenames;
	else
		printvar = *mem.sep.file_alloc;
	while (filenames[dir_len])
		dir_len++;
	while (printvar[print_len])
		print_len++;
	for (i = 0; i < print_len; i++)
	{
		printf("%s\n", printvar[i]);
	}
	free_grid(filenames, dir_len);
}
/**
 * long_listing - list all the files
 * @dir_name: directory name
 * @filenames: array of file names to print
 * @mode: printing files or directories
 * @mem: structure with all the memory
 * Return: Nothing.
 */
void long_listing(char *dir_name, char **filenames, int mode, free_mem mem)
{
	struct stat sb;
	int i = 0, dir_len = 0, print_len = 0;
	char **printvar = NULL;
	char buffer[1024];

	if (mode != -1)
		printvar = filenames;
	else
		printvar = *mem.sep.file_alloc;
	while (filenames[dir_len])
		dir_len++;
	while (printvar[print_len])
		print_len++;
	for (i = 0; i < print_len; i++)
	{
	if (_strcmp((dir_name + _strlen(dir_name) - 1), "/") != 0 && mode != -1)
		sprintf(buffer, "%s/%s", dir_name, printvar[i]);
	else if (mode != -1)
		sprintf(buffer, "%s%s", dir_name, printvar[i]);
	else
		sprintf(buffer, "%s", printvar[i]);
	if (lstat(buffer, &sb) == -1)
	{
		perror("aqui es el error stat");
		exit(EXIT_FAILURE);
	}
	print_file_type(sb);
	print_permissions(sb);
	print_data_state(buffer, printvar[i], sb, mem);
		}
	free_grid(filenames, dir_len);
}
/**
 * print_permissions - prints the permissions of a file
 * @sb: structure with file information
 * Return: None
 */
void print_permissions(struct stat sb)
{
	int i = 0, rotate = 0, state = 0;

	for (i = 0; i < 3; i++)
	{
		rotate = 00700 >> i * 3;
		state = sb.st_mode & rotate;
		if (i == 0)
			state = state / 64;
		if (i == 1)
			state = state / 8;
		switch (state)
		{
		case 0:
			printf("---");
			break;
		case 1:
			printf("--x");
			break;
		case 2:
			printf("-w-");
			break;
		case 3:
			printf("-wx");
			break;
		case 4:
			printf("r--");
			break;
		case 5:
			printf("r-x");
			break;
		case 6:
			printf("rw-");
			break;
		case 7:
			printf("rwx");
			break;
		}
	}
}
/**
 * print_data_state - prints extra information about a file
 * @printvar: file name with path
 * @name: file name alone
 * @sb: structure with file information
 * @mem: structure to free memory in case of error
 * Return: None
 */
void print_data_state(char *printvar, char *name, struct stat sb, free_mem mem)
{
	struct passwd *pwd;
	struct group *grp;
	char *file_time;
	char *linkname;
	int r;

	printf(" %ld ", (long) sb.st_nlink);
	pwd = getpwuid(sb.st_uid);
	if (pwd)
		printf("%s ", pwd->pw_name);
	else
		printf("%d ", sb.st_uid);
	grp = getgrgid(sb.st_gid);
	if (grp)
		printf("%s ", grp->gr_name);
	else
		printf("%d ", sb.st_gid);
	printf("%ld ", (long) sb.st_size);
	file_time = ctime(&sb.st_mtime);
	printf("%.12s ", file_time + 4);
	printf("%s", name);
	if ((sb.st_mode & S_IFMT) != S_IFLNK)
		printf("\n");
	else
	{
		linkname = _calloc(sb.st_size + 1, 1, mem);
		r = readlink(printvar, linkname, sb.st_size + 1);
		if (r < 0 || r > sb.st_size)
		{
			fprintf(stderr, "symlink err(%s)\n", printvar);
			exit(EXIT_FAILURE);
		}
		linkname[sb.st_size] = '\0';
		printf(" -> %s\n", linkname);
		free(linkname);
	}
}
