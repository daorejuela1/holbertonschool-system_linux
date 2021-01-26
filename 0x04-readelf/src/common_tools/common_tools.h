#ifndef _COMMON_TOOLS_H
#define _COMMON_TOOLS_H
#include <elf.h>
#include <endian.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
Elf64_Ehdr read_elf_header(const char *file_name, Elf32_Ehdr *header_32);
void print_spaces(int n);
#define REV(x) (((x) & 0x0F) << 4 | ((x) & 0xF0) >> 4)
#endif
