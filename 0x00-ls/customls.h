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
#endif
