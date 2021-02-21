#ifndef _SIGNALS_H
#define _SIGNALS_H

/*  space to include libraries */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>

/* prototypes definition */
int handle_signal(void);
void (*current_handler_signal(void))(int);
void (*current_handler_sigaction(void))(int);
int handle_sigaction(void);
int trace_signal_sender(void);
int pid_exist(pid_t pid);
void all_in_one(void);
int sigset_init(sigset_t *set, int *signals)
#endif
