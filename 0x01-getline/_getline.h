#ifndef _GETLINE_H
#define _GETLINE_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define READ_SIZE 512

/**
 * struct STREAM - struct to define each stream source
 *
 * @fd: file descriptor
 * @buffer: store of actual read data
 * @line: store of returned line
 */
typedef struct STREAM
{
	int fd;
	char *buffer;
	char *line;
} streamf;

char *_getline(const int fd);
int getindex(char *array, char chr);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
int _strlen(char *s);
char *split_line(int index);
#endif
