#include "common_tools.h"

#define NO_ELF "readelf: Error: Not an ELF file"
#define WRONG_MAGIC "- it has the wrong magic bytes at the start\n"

Elf64_Ehdr read_elf_header(const char *file_name, Elf32_Ehdr *header_32)
{
	Elf64_Ehdr header;
	FILE *file = NULL;

	file = fopen(file_name, "rb");
	if (file)
	{
		fread(&header, sizeof(header), 1, file);
		if (memcmp(header.e_ident, ELFMAG, SELFMAG) == 0)
		{
			rewind(file);
			if (header.e_ident[4] == 1)
				fread(header_32, sizeof(*header_32), 1, file);
			return (header);
		}
		fprintf(stderr, "%s %s", NO_ELF, WRONG_MAGIC);
		exit(1);
	}
	else
	{
		perror("Error: ");
		exit(1);
	}
}
