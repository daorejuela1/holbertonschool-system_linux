#ifndef CUSTOMLS_H
#define CUSTOMLS_H

#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
extern int errno;
void normal_print(char *name, int dir_len);
int get_dirlen(char *name);
DIR *_opendir_safe(char *name);
int _strcmp(char *p1, char *p2);
char *_strncpy(char *dest, char *src, int n);
int _strlen(char *s);
char *_strcat(char *dest, char *src);
void free_grid(char **grid, int height);
void *_calloc(unsigned int nmemb, unsigned int size);
char *_memset(char *s, char b, unsigned int n);
char **parse_data(char *argv[], char **arguments);
#endif
