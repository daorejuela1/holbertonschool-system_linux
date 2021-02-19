#include <sys/types.h>
#include <signal.h>
/**
 * pid_exist - Checks that a PID
 * * @pid: pid to check if exist
 * * Return: return 1 if the process with the PID pid exists, or 0
 */
int pid_exist(pid_t pid)
{
	return (kill(pid, 0) ? 0 : 1);
}
