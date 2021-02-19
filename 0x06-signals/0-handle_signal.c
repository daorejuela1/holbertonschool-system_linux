#include "signals.h"

/**
 * print_gotcha - prints gotcha and the SIGINT number
 * @signal: Signal received with the handler
 */
void print_gotcha(int signal)
{
	printf("Gotcha! [%d]\n", signal);
}

/**
 * handle_signal - function that set a handler for the signal SIGINT
 *
 * Return:  return 0 on success, or -1 on error
 */
int handle_signal(void)
{
	if (signal(SIGINT, print_gotcha) == SIG_ERR)
		return (-1);
	return (0);
}
