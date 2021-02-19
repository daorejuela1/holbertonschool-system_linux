#include "signals.h"

/**
 * main - prints a description of a given signal
 * @argc: quantity of arguments
 * @argv: value of the arguments
 *
 * Return: 0 on success, -1 on failure
 */
int main(int argc, char *argv[])
{
	int signal_num = 0;

	if (argc != 2)
	{
		printf("Usage: %s <signum>\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	signal_num = atoi(argv[1]);
	printf("%d: %s\n", signal_num, strsignal(signal_num));
	return (0);
}
