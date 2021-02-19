#include "signals.h"

/**
 * print_gotcha - receives signal
 *
 * @signal: the signal number received
 * @info:data structure with information about the signal
 * @name: Signal name
 */
void print_gotcha(int signal, siginfo_t *info, void *name)
{
	(void) name;
	(void) signal;

	printf("SIGQUIT sent by %d\n", info->si_pid);
}

/**
 * trace_signal_sender - set a handler for the signal SIGQUIT
 *
 * Return:  return 0 on success, or -1 on error
 */
int trace_signal_sender(void)
{
	struct sigaction act;

	memset(&act, 0, sizeof(act));
	act.sa_sigaction = print_gotcha;
	return (sigaction(SIGQUIT, &act, NULL));
}
