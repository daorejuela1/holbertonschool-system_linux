#ifndef CUSTOMLS_H
#define CUSTOMLS_H

#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
/**
 * struct modifier_params - singly linked list
 * @print_below: flag to store if a below printing is in order
 * @search_hidden: flag to indicate if hidden files should be listed
 * @search_myhidden: flag to indicate if hidden files except . ..
 * @long_listing: flag to indicate if long listed is needed
 * @sort_reverse: flag to indicate reverse sorting
 * @sort_by_size: flag to indicate sort by size
 * @sort_by_time: flag to indicate sort by time
 * @recursive: flag to indicate recursion
 *
 * Description: This structure defines the flags that ls has to take in account
 */
typedef struct modifier_params
{
	char print_below;
	char search_hidden;
	char search_myhidden;
	char long_listing;
	char sort_reverse;
	char sort_by_size;
	char sort_by_time;
	char recursive;
} arg_flags;

/**
 * struct c_alloc - all malloc variables
 * @arguments: list of arguments
 * @filenames: list of filenames get by argument
 * @directories: list of directories inside a folder
 * @file_len: len of filenames
 * @arg_len: len of arguments
 * @dir_len: len of directories
 *
 * Description: This structure defines the mem allocs
 */
typedef struct c_alloc
{
	char **arguments;
	int *arg_len;
	char ***filenames;
	int *file_len;
	char ***directories;
	int *dir_len;
} c_per;


extern int errno;
void normal_print(char **filenames);
int get_dirlen(char *name, int selector);
DIR *_opendir_safe(char *name, int mode);
int _strcmp(char *p1, char *p2);
char *_strncpy(char *dest, char *src, int n);
int _strlen(char *s);
char *_strcat(char *dest, char *src);
void free_grid(char **grid, int height);
void *_calloc(unsigned int nmemb, unsigned int size);
char *_memset(char *s, char b, unsigned int n);
void parse_data(char *argv[], c_per variables);
char **get_dir_names(char *name, int dir_len, int selector);
arg_flags flag_setter(c_per variables);
int ls_answer(char *dir_name, arg_flags ls_flag, c_per c_var, int multiple);
void below_print(char **filenames);
int _strfcmp(char *p1, char *p2);
int gets_valid(char **fold_names);
#endif
