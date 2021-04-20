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
		printf("%s = ", syscalls_64_g[uregs.orig_rax].name);
		if (syscall_withreturn(child_pid))
			break;
		memset(&uregs, 0, sizeof(uregs));
		ptrace(PTRACE_GETREGS, child_pid, 0, &uregs);
		printf("%#lx\n", (long)uregs.rax);
	}
}
