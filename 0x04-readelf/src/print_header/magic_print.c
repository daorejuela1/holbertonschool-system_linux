#include "../common_tools/common_tools.h"
#include "print_header.h"
/**
 * print_magic - prints the magic number of an ELF file
 * @e_ident: array of bytes in the ELF file
 *
 * Return: Nothing
 */
void print_magic(unsigned char e_ident[EI_NIDENT])
{
	int i;

	printf("  Magic:   ");
	for (i = 0; i < EI_NIDENT; i++)
	{
		printf("%02x", e_ident[i]);
		printf(" ");
	}
	printf("\n");
}
/**
 * print_class - prints the class of an ELF file
 * @class_flag: array of bytes in the ELF file
 *
 * Return: Nothing
 */
void print_class(unsigned char class_flag)
{
	int i;
	dict_classes classes[] = {{2, "ELF64"}, {1, "ELF32"},};

	printf("  Class:");
	print_spaces(29);
	for (i = 0; i < 2; i++)
	{
		if (classes[i].key == class_flag)
			printf("%s\n", classes[i].value);
	}
}

/**
 * print_data - prints the data of an ELF file
 * @data_flag: flag to tell how data is structured in the file
 *
 * Return: Nothing
 */
void print_data(unsigned char data_flag)
{
	int i;
	dict_classes data[] = {{1, "2's complement, little endian"},
				{2, "2's complement, big endian"},};
	char *info = "  Data:";

	printf("%s", info);
	print_spaces(37 - strlen(info));
	for (i = 0; i < 2; i++)
	{
		if (data[i].key == data_flag)
			printf("%s\n", data[i].value);
	}
}

/**
 * print_version - prints the version of an ELF file
 * @version_flag: flag to tell how data is structured in the file
 *
 * Return: Nothing
 */
void print_version(unsigned char version_flag)
{
	int i;
	char *info = "  Version:";
	dict_classes version[] = {{0, "0 (invalid)"}, {1, "1 (current)"},
		{2, "1"},};

	printf("%s", info);
	print_spaces(37 - strlen(info));
	for (i = 0; i < 2; i++)
	{
		if (version[i].key == version_flag)
			printf("%s\n", version[i].value);
	}
}

/**
 * print_os - prints the os of an ELF file
 * @os_flag: the kind of os the file was created fot
 *
 * Return: Nothing
 */
void print_os(unsigned char os_flag)
{
	int i;
	char *info = "  OS/ABI:";
	dict_classes os[] = {{0, "UNIX - System V"},
	{1, "UNIX - HP-UX"}, {2, "UNIX - NetBSD"}, {3, "UNIX - Linux"},
	{4, "UNIX - GNU Hurd"}, {6, "UNIX - Solaris"}, {7, "UNIX - AIX"},
	{8, "UNIX - IRIX"}, {9, "UNIX - FreeBSD"}, {0xA, "UNIX - Tru64"},
	{0xB, "Novell Modesto"}, {0xC, "OpenBSD"},
	{0xD, "OpenVMS"}, {0xE, "NonStop Kernel"},
	{0xF, "AROS"}, {0x10, "Fenix OS"},
	{0x11, "CloudABI"}, {0x12, "Stratus Technologies OpenVOS"},};

	printf("%s", info);
	print_spaces(37 - strlen(info));
	for (i = 0; i < 19; i++)
	{
		if (os[i].key == os_flag)
			printf("%s\n", os[i].value);
	}
}
