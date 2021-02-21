#include "signals.h"

/**
 * current_handler_signal - retrieve the current handler of SIGINT
 *
 * Return: NULL on error, pointer to the current handler of SIGINT otherwise
 */
void (*current_handler_signal(void))(int)
{
	__sighandler_t sigint_handler = signal(SIGINT, SIG_IGN);

	if (sigint_handler == SIG_ERR)
		return (NULL);
	if (signal(SIGINT, sigint_handler) == SIG_ERR)
		return (NULL);
	return (sigint_handler);
}
