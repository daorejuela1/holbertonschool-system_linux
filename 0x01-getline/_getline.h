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
 * @output: store of actual read data
 * @repetitions: stores if the buffer needs to be increased in the next read
 * @next: pointer to the next stream
 */
typedef struct STREAM
{
	int fd;
	char *output;
	int repetitions;
	struct STREAM *next;
} streamf;

char *_getline(const int fd);
int getindex(char *array, char chr);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
int _strlen(char *s);
char *split_line(int index);
void clean_files(void);
char *handlefd(int fd);
#endif
