#include "strace.h"
#include "syscalls.h"

/**
 * trace_namehex - gets the syscall name and hex value
 * @child_pid: pid of child to trace
 */
void trace_namehex(pid_t child_pid)
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
		if (syscall_withreturn(child_pid))
			break;
		memset(&uregs, 0, sizeof(uregs));
		ptrace(PTRACE_GETREGS, child_pid, 0, &uregs);
		printf(" = %#lx\n", (long)uregs.rax);
	}
}

/**
 * params - gets given parameter for syscall
 * @uregs: userspace register struct
 * @i: syscall parameter index
 * Return: value of param
 */
unsigned long params(struct user_regs_struct uregs, size_t i)
{
	switch (i)
	{
		case 0: return (uregs.rdi);
		case 1: return (uregs.rsi);
		case 2: return (uregs.rdx);
		case 3: return (uregs.r10);
		case 4: return (uregs.r8);
		case 5: return (uregs.r9);
		default: return (-1);
	}
}

/**
 * syscall_withreturn2 - waits for a syscall printing ? in case of exit
 * @child_pid: pid of process to await
 * Return: 0 if child stopped, 1 if exited
 */
int syscall_withreturn2(pid_t child_pid)
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

/**
 * trace_namewithargs - calls made by tracing parent
 * @child_pid: pid of child to trace
 */
void trace_namewithargs(pid_t child_pid)
{
	int status, i, first = 1;
	struct user_regs_struct uregs;

	waitpid(child_pid, &status, 0);
	ptrace(PTRACE_SETOPTIONS, child_pid, 0, PTRACE_O_TRACESYSGOOD);
	while (1)
	{
		if (await_syscall(child_pid))
			break;
		memset(&uregs, 0, sizeof(uregs));
		ptrace(PTRACE_GETREGS, child_pid, 0, &uregs);
		if (first && uregs.orig_rax == 59)
			first = 1;
		else
		{
			printf("%s(", syscalls_64_g[uregs.orig_rax].name);
			for (i = 0; i < (int)syscalls_64_g[uregs.orig_rax].nb_params; i++)
			{
				i ? printf(", ") : 0;
				syscalls_64_g[uregs.orig_rax].params[i] == VARARGS ?
					printf("...") : printf("%#lx", params(uregs, i));
			}
		}
		if (syscall_withreturn2(child_pid))
			break;
		memset(&uregs, 0, sizeof(uregs));
		ptrace(PTRACE_GETREGS, child_pid, 0, &uregs);
		if (first && uregs.orig_rax == 59)
			first = 0;
		else
			printf(") = %#lx\n", (unsigned long)uregs.rax);
	}
}
