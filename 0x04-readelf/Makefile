# -*- MakeFile -*-

NAME0 = 0-hreadelf 
NAME1 = 1-hreadelf 
NAME2 = 2-hreadelf 
NAME100 = 100-hreadelf 

CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic
SRCDIR = src
COMMON_DIR = hreadelf

TASK0 = print_header
COMMON = common_tools
OBJ0 += $(patsubst %.c, %.o, $(wildcard $(SRCDIR)/$(TASK0)/*.c))
OBJ0 += $(patsubst %.c, %.o, $(wildcard $(SRCDIR)/$(COMMON)/*.c))
OBJ1 += $(patsubst %.c, %.o, $(SRCDIR)/$(COMMON_DIR)/1-main.c)
OBJ2 += $(patsubst %.c, %.o, $(SRCDIR)/$(COMMON_DIR)/2-main.c)
OBJ100 += $(patsubst %.c, %.o, $(SRCDIR)/$(COMMON_DIR)/100-main.c)

$(NAME0): $(OBJ0)
	$(CC) $(OBJ0) -o $(NAME0)

$(NAME1): $(OBJ1)
	$(CC) $(OBJ1) -o $(NAME1)

$(NAME2): $(OBJ2)
	$(CC) $(OBJ2) -o $(NAME2)

$(NAME100): $(OBJ100)
	$(CC) $(OBJ100) -o $(NAME100)
