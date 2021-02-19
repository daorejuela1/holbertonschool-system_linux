#include "signals.h"

/**
 * print_gotcha - receives signal
 * @signal: the signal number received
 */
void print_gotcha(int signal)
{
	printf("Gotcha! [%d]\n", signal);
	fflush(stdout);
}

/**
 * handle_sigaction - set a handler for the signal SIGINT
 *
 * Return: Return 0 on success, or -1 on error
 */
int handle_sigaction(void)
{
	struct sigaction act;

	memset(&act, 0, sizeof(act));
	act.sa_handler = print_gotcha;
	return (sigaction(SIGINT, &act, NULL));
}
