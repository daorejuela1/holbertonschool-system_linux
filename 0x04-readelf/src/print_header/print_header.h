#ifndef _PRINT_HEADER_H
#define _PRINT_HEADER_H
/* Structure definition*/
/**
 * struct classes - dictionary to store tables
 * @key: key to enter value
 * @value: string value
 * Description: singly linked list node structure
 * for Holberton project
 */
typedef struct classes
{
	char key;
	char *value;
} dict_classes;
void print_magic(unsigned char e_ident[EI_NIDENT]);
void print_class(unsigned char class_flag);
void print_data(unsigned char data_flag);
void print_version(unsigned char data_version);
void print_os(unsigned char os_flag);
void print_abi(unsigned char abi_value);
void print_type(Elf64_Half type_flag, Elf32_Half type_flag_32, int selector);
void print_machine(Elf64_Half machine_flag);
void print_entryp(Elf64_Addr entryp, Elf32_Addr entryp_32, int selector);
void print_proghead(Elf64_Addr proghead, Elf32_Addr proghead_32, int selector);
void print_sechead(Elf64_Addr sechead, Elf32_Addr sechead_32, int selector);
void print_version2(Elf64_Word offset);
void print_flags(Elf64_Word flags, Elf32_Word flags_32, int selector);
void print_hsize(Elf32_Half hsize, Elf32_Half hsize_32, int selector);
void print_phsize(Elf32_Half phsize, Elf32_Half phsize_32, int selector);
void print_nsize(Elf32_Half nsize, Elf32_Half nsize_32, int selector);
void print_shsize(Elf32_Half shsize, Elf32_Half shsize_32, int selector);
void print_shnum(Elf32_Half shnum, Elf32_Half shnum_32, int selector);
void print_tindex(Elf32_Half tindex, Elf32_Half tindex_32, int selector);
char *get_osabi_name(unsigned int osabi);
char *get_file_type(unsigned int e_type);
#endif
