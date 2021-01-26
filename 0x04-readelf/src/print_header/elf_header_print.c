#include "../common_tools/common_tools.h"
#include "print_header.h"


/**
 *main - logic to open the file
 *@argc: Quantity of arguments
 *@argv: Value of the arguments
 *Return: 0 if success otherwise Error
 */
int main(int argc, char *argv[])
{
	Elf64_Ehdr header;
	Elf32_Ehdr header_32;
	FILE *file = NULL;

	if (argc - 1 != 1)
	{
		exit(0);
	}
	header = read_elf_header(&file, argv[1], &header_32);
	endian_check(&header, &header_32);
	printf("ELF Header:\n");
	print_magic(header.e_ident);
	print_class(header.e_ident[4]);
	print_data(header.e_ident[5]);
	print_version(header.e_ident[6]);
	print_os(header.e_ident[7]);
	print_abi(header.e_ident[8]);
	print_type(header.e_type, header_32.e_type, header.e_ident[4]);
	print_machine(header.e_machine);
	print_version2(header.e_version);
	print_entryp(header.e_entry, header_32.e_entry, header.e_ident[4]);
	print_proghead(header.e_phoff, header_32.e_phoff, header.e_ident[4]);
	print_sechead(header.e_shoff, header_32.e_shoff, header.e_ident[4]);
	print_flags(header.e_flags, header_32.e_flags, header_32.e_ident[4]);
	print_hsize(header.e_ehsize, header_32.e_ehsize, header.e_ident[4]);
	print_phsize(header.e_phentsize, header_32.e_phentsize, header.e_ident[4]);
	print_nsize(header.e_phnum, header_32.e_phnum, header.e_ident[4]);
	print_shsize(header.e_shentsize, header_32.e_shentsize, header.e_ident[4]);
	print_shnum(header.e_shnum, header_32.e_shnum, header.e_ident[4]);
	print_tindex(header.e_shstrndx, header_32.e_shstrndx, header.e_ident[4]);
	fclose(file);
	return (0);
}
