#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
/**
 * main - function to showcase how to change the heap memory
 * of a running process
 */
int main(void)
{
	int line = 0;
	char *heap_data = NULL;

	heap_data = strdup("hello world");
	while (1)
	{
		printf("[%d] %s (%p)\n", line++, heap_data, heap_data);
		sleep(2);
	}
	return (1);
}
