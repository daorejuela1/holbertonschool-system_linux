#include "signals.h"

/**
 * print_gotcha - receives signal
 *
 * @signal: the signal number received
 */
void print_gotcha(int signal)
{
	printf("Caught %d\n", signal);
	printf("Signal received\n");
	fflush(stdout);
}

/**
 * main - set a handler for the signal SIGINT
 *
 * Return: 0 on success
 */
int main(void)
{
	struct sigaction act;

	memset(&act, 0, sizeof(act));
	act.sa_handler = print_gotcha;
	sigaction(SIGINT, &act, NULL);
	pause();
	return (EXIT_SUCCESS);
}
