#include "syscalls.h"
#include "strace.h"

/**
 * trace_child - traces child process
 * @av: argument vector for execve
 * @envp: environ for execve
 */
void trace_child(char **av, char **envp)
{
	ptrace(PTRACE_TRACEME, 0, 0, 0);
	kill(getpid(), SIGSTOP);
	if (execve(av[1], av + 1, envp) == -1)
	{
		dprintf(STDERR_FILENO, "Exec failed: %d\n", errno);
		exit(-1);
	}
}

/**
 * trace_parent - calls made by tracing parent
 * @child_pid: pid of child to trace
 */
void trace_parent(pid_t child_pid)
{
	int status;
	struct user_regs_struct uregs;

	waitpid(child_pid, &status, 0);
	ptrace(PTRACE_SETOPTIONS, child_pid, 0, PTRACE_O_TRACESYSGOOD);
	while (1)
	{
		if (await_syscall(child_pid))
			break;
		memset(&uregs, 0, sizeof(uregs));
		ptrace(PTRACE_GETREGS, child_pid, 0, &uregs);
		printf("%lu\n", (long)uregs.orig_rax);
		if (await_syscall(child_pid))
			break;
	}
}

/**
 * trace_name - prints name of given command
 * @child_pid: pid of child to trace
 */
void trace_name(pid_t child_pid)
{
	int status;
	struct user_regs_struct uregs;

	waitpid(child_pid, &status, 0);
	ptrace(PTRACE_SETOPTIONS, child_pid, 0, PTRACE_O_TRACESYSGOOD);
	while (1)
	{
		if (await_syscall(child_pid))
			break;
		memset(&uregs, 0, sizeof(uregs));
		ptrace(PTRACE_GETREGS, child_pid, 0, &uregs);
		printf("%s", syscalls_64_g[uregs.orig_rax].name);
		if (await_syscall(child_pid))
			break;
		printf("\n");
	}
}


/**
 * await_syscall - waits for a syscall
 * @child_pid: pid of process to await
 * Return: 0 if child stopped, 1 if exited
 */
int await_syscall(pid_t child_pid)
{
	int status;

	while (1)
	{
		ptrace(PTRACE_SYSCALL, child_pid, 0, 0);
		waitpid(child_pid, &status, 0);
		if (WIFSTOPPED(status) && WSTOPSIG(status) & 0x80)
			return (0);
		if (WIFEXITED(status))
			return (1);
	}
}

/**
 * syscall_withreturn - waits for a syscall printing ? in case of exit 
 * @child_pid: pid of process to await
 * Return: 0 if child stopped, 1 if exited
 */
int syscall_withreturn(pid_t child_pid)
{
	int status;

	while (1)
	{
		ptrace(PTRACE_SYSCALL, child_pid, 0, 0);
		waitpid(child_pid, &status, 0);
		if (WIFSTOPPED(status) && WSTOPSIG(status) & 0x80)
			return (0);
		if (WIFEXITED(status))
		{
			printf(" = ?\n");
			return (1);
		}
	}
}

