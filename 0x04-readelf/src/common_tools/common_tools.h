#ifndef _COMMON_TOOLS_H
#define _COMMON_TOOLS_H

#include <elf.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

Elf64_Ehdr read_elf_header(FILE **f, char *file_name, Elf32_Ehdr *header_32);
void endian_check(Elf64_Ehdr *header, Elf32_Ehdr *header_32);
void print_spaces(int n);

#endif
