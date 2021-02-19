#include "signals.h"

/**
 * current_handler_signal - retrieve the current handler of SIGINT
 *
 * Return: NULL on error, pointer to the current handler of SIGINT otherwise
 */
void (*current_handler_signal(void))(int)
{
	__sighandler_t sigint_handler = signal(SIGINT, SIG_IGN);
	return (sigint_handler);
}
