#include "../common_tools/syscalls.h"
#include "../common_tools/strace.h"


/**
 * main - program that executes and traces a given command
 * @ac: argument count
 * @av: argument vector
 * @envp: environ variable
 * Return: Success or Failure
 */
int main(int ac, char **av, char **envp)
{
	pid_t child_pid;

	if (ac < 2)
	{
		printf("Usage: %s command [args...]\n", av[0]);
		return (EXIT_FAILURE);
	}
	setbuf(stdout, NULL);
	child_pid = fork();
	if (child_pid == -1)
	{
		dprintf(STDERR_FILENO, "Fork failed: %d\n", errno);
		exit(-1);
	}
	else if (!child_pid)
		{
			setbuf(stdout, NULL);
			printf("execve(0, 0, 0) = 0\n");
			trace_child(av, envp);
		}
	else
		trace_namewithargs(child_pid);
	return (EXIT_SUCCESS);
}
