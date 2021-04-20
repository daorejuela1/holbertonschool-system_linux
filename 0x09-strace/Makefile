# -*- MakeFile -*-

NAME0 = strace_0
NAME1 = strace_1
NAME2 = strace_2
NAME3 = strace_3

CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -g
SRCDIR = src

TASK0 = strace_0
TASK1 = strace_1
TASK2 = strace_2
TASK3 = strace_3

COMMON = common_tools

OBJ0 += $(patsubst %.c, %.o, $(wildcard $(SRCDIR)/$(TASK0)/*.c))
OBJ0 += $(patsubst %.c, %.o, $(wildcard $(SRCDIR)/$(COMMON)/*.c))
OBJ1 += $(patsubst %.c, %.o, $(wildcard $(SRCDIR)/$(TASK1)/*.c))
OBJ1 += $(patsubst %.c, %.o, $(wildcard $(SRCDIR)/$(COMMON)/*.c))
OBJ2 += $(patsubst %.c, %.o, $(wildcard $(SRCDIR)/$(TASK2)/*.c))
OBJ2 += $(patsubst %.c, %.o, $(wildcard $(SRCDIR)/$(COMMON)/*.c))
OBJ3 += $(patsubst %.c, %.o, $(wildcard $(SRCDIR)/$(TASK3)/*.c))
OBJ3 += $(patsubst %.c, %.o, $(wildcard $(SRCDIR)/$(COMMON)/*.c))

$(NAME0): $(OBJ0)
	$(CC) $(OBJ0) -o $(NAME0)

$(NAME1): $(OBJ1)
	$(CC) $(OBJ1) -o $(NAME1)

$(NAME2): $(OBJ2)
	$(CC) $(OBJ2) -o $(NAME2)

$(NAME3): $(OBJ3)
	$(CC) $(OBJ3) -o $(NAME3)
