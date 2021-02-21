#include "signals.h"

/**
 * sigset_init - function that initializes a sigset
 * @set: pointer to the signal set to initialize
 * @signals: 0-terminated array of int, each one being a signal number
 * Return: 0 on success else -1 on error
 */
int sigset_init(sigset_t *set, int *signals)
{
	for (sigemptyset(set); *signals != 0; signals++)
		if (sigaddset(set, *signals))
			return (-1);
	return (0);
}
