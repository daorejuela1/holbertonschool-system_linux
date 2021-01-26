# -*- MakeFile -*-

NAME1 = 0-hreadelf 
CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic -g

SRCDIR = src
OBJDIR = obj

TASK0 = print_header
COMMON = common_tools

OBJ += $(patsubst %.c, %.o, $(wildcard $(SRCDIR)/$(TASK0)/*.c))
OBJ += $(patsubst %.c, %.o, $(wildcard $(SRCDIR)/$(COMMON)/*.c))

.PHONY : all clean oclean fclean re

$(NAME1): $(OBJ)
	$(CC) $(OBJ) -o $(NAME1)

clean:
	$(RM) *~ $(NAME1)

oclean:
	$(RM) $(OBJ)

fclean: clean oclean

re: oclean $(NAME)

print-%:
	@echo '$*=$($*)'
