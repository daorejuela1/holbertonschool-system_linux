#include "signals.h"

/**
 * handle_sigaction - set a handler for the signal SIGINT
 *
 * Return: retrieves the current handler of the signal SIGINT
 */
int handle_sigaction(void)
{
	struct sigaction act;

	memset(&act, 0, sizeof(act));
	if (!sigaction(SIGINT, &act, NULL))
		return (NULL);
	return (act.sa_handler);
}
