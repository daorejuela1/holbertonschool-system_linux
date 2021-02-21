#include "signals.h"

/**
 * current_handler_sigaction - set a handler for the signal SIGINT
 *
 * Return: retrieves the current handler of the signal SIGINT
 */
void (*current_handler_sigaction(void))(int)
{
	struct sigaction old;

	memset(&old, 0, sizeof(old));
	if (!sigaction(SIGINT, NULL, &old))
		return (NULL);
	return (old.sa_handler);
}
