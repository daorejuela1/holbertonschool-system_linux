#include "signals.h"

/**
 * print_gotcha - receives signal
 * @signal: the signal number received
 * @info: signal info
 * @name: signal name
 */
void print_gotcha(int signal, siginfo_t *info, void *name)
{
	(void)signal;
	(void)name;
	psiginfo(info, "Caught");
}

/**
 * all_in_one - set a handler for the signal SIGINT
 *
 * Return: Return 0 on success, or -1 on error
 */
void all_in_one(void)
{
	struct sigaction act;
	int signal;

	memset(&act, 0, sizeof(act));
	act.sa_flags |= SA_SIGINFO;
	act.sa_sigaction = print_gotcha;
	for (signal = SIGHUP; signal <= SIGRTMAX; signal++)
		sigaction(signal, &act, NULL);
}
