#include "common_tools.h"
/**
 * endian_check - checks the endianess of the headers to understand the data
 * @header: address of the 64 bits structure
 * @header_32: address of the 32 bits structure
 */
void endian_check(Elf64_Ehdr *header, Elf32_Ehdr *header_32)
{
	if (header->e_ident[5] == 2)
	/*64 bits system*/
	{
		header->e_machine = be16toh(header->e_machine);
		header->e_version = be32toh(header->e_version);
		if (header->e_ident[4] == 2)
		/* big endian*/
		{
			header->e_entry = be64toh(header->e_entry);
			header->e_phoff = be64toh(header->e_phoff);
			header->e_shoff = be64toh(header->e_shoff);
			header->e_ehsize = be16toh(header->e_ehsize);
			header->e_phentsize = be16toh(header->e_phentsize);
			header->e_phnum = be16toh(header->e_phnum);
			header->e_shentsize = be16toh(header->e_shentsize);
			header->e_shnum = be16toh(header->e_shnum);
			header->e_shstrndx = be16toh(header->e_shstrndx);
		}
		else
		{
			header_32->e_entry = be32toh(header_32->e_entry);
			header_32->e_phoff = be32toh(header_32->e_phoff);
			header_32->e_shoff = be32toh(header_32->e_shoff);
			header_32->e_flags = be32toh(header_32->e_flags);
			header_32->e_ehsize = be16toh(header_32->e_ehsize);
			header_32->e_phentsize = be16toh(header_32->e_phentsize);
			header_32->e_phnum = be16toh(header_32->e_phnum);
			header_32->e_shentsize = be16toh(header_32->e_shentsize);
			header_32->e_shnum = be16toh(header_32->e_shnum);
			header_32->e_shstrndx = be16toh(header_32->e_shstrndx);
		}
	}
}
