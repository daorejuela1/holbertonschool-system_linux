#include "elf.h"
#define REV(x) ((x & 0x0F) << 4 | (x & 0xF0) >> 4)
/**
 *print_spaces - print n spaces
 *@n: number of spaces
 *Return: Nothing
 */
void print_spaces(int n)
{
	int i;

	for (i = 0; i < n; i++)
	{
		printf(" ");
	}
}

/**
 *print_address - print address according to file formart
 *@buf: data buffer
 *Return: Nothing
 */
void print_address(char *buf)
{
	int i;
	unsigned char letter;

	if (*(buf + 5) == 1 && *(buf + 4) == 1)
	{
		printf("%x", REV((unsigned char)*(buf + 27)));
		for (i = 0; i < 3; i++)
		{
			letter = (unsigned char)*(buf + 26 - i);
			if (letter == 0)
				printf("%02x", letter);
			else
				printf("%1x", letter);
		}
	}
	else if (*(buf + 5) == 1 && *(buf + 4) == 2)
	{
		printf("%x", (unsigned char)*(buf + 26));
		printf("%x", (unsigned char)*(buf + 27));
		for (i = 0; i < 2; i++)
		{
			letter = (unsigned char)*(buf + 25 - i);
			if (letter == 0)
				printf("%02x", letter);
			else
				printf("%1x", letter);
		}
	}
	else
	{
		printf("%x", REV((unsigned char)*(buf + 25)));
		for (i = 0; i < 2; i++)
		{
			letter = (unsigned char)*(buf + 26 + i);
			if (letter == 0)
				printf("%02x", letter);
			else
				printf("%1x", letter);
		}
	}
}

/**
 *first_print -prints from magic to version
 *@buf: Quantity of arguments
 *Return: 0 if success
 */
void first_print (char *buf)
{
	int i;

	dict_classes class1 [] = {{2, "ELF64"}, {1, "ELF32"},};
	dict_classes data1 [] = {{1, "2's complement, little endian"},
		{2, "2's complement, big endian"},};
	dict_classes version1 [] = {{0, "0 (invalid)"}, {1, "1 (current)"},
	{2, "1"},};

	printf("  Magic:   ");
	for (i = 0; i < 16; i++)
	{
		printf("%02x", (unsigned char)*(buf + i));
		if (i != 15)
			printf(" ");
	}
	printf("\n");
	printf("  Class:");
	print_spaces(29);
	for (i = 0; i < 2; i++)
	{
		if (class1[i].key == *(buf + 4))
			printf("%s\n", class1[i].value);
	}
	printf("  Data:");
	print_spaces(30);
	for (i = 0; i < 2; i++)
	{
		if (data1[i].key == *(buf + 5))
			printf("%s\n", data1[i].value);
	}
	printf("  Version:");
	print_spaces(27);
	for (i = 0; i < 3; i++)
	{
		if (version1[i].key == EV_CURRENT)
			printf("%s\n", version1[i].value);
	}
}

/**
 *second_print -prints from magic to version
 *@buf: Quantity of arguments
 *Return: 0 if success
 */
void second_print (char *buf)
{
	int i;

	dict_classes abi1[] = {{0, "System V"},
	{1, "HP-UX"}, {2, "NetBSD"}, {3, "Linux"},
	{4, "GNU Hurd"}, {6, "Solaris"}, {7, "AIX"},
	{8, "IRIX"}, {9, "FreeBSD"}, {0xA, "Tru64"},
	{0xB, "Novell Modesto"}, {0xC, "OpenBSD"},
	{0xD, "OpenVMS"}, {0xE, "NonStop Kernel"},
	{0xF, "AROS"}, {0x10, "Fenix OS"},
	{0x11, "CloudABI"}, {0x12, "Stratus Technologies OpenVOS"},};

	dict_classes type1[] = {{0, "EXEC (Executable file)"},
	{1, "REL (Relocatable file)"},
	{2, "EXEC (Executable file)"}, {3, "DYN (Shared object file)"},
	{4, "CORE (Core file)"},};
	printf("  OS/ABI:");
	print_spaces(28);
	for (i = 0; i < 19; i++)
	{
		if (abi1[i].key == *(buf + 7))
			printf("UNIX - %s\n", abi1[i].value);
		if (*(buf + 7) >= 19)
		{
			printf("<unknown: %2x>\n", *(buf + 7));
			break;
		}
	}
	printf("  ABI Version:");
	print_spaces(23);
	printf("%d\n", *(buf + 8));
	printf("  Type:");
	print_spaces(30);
	for (i = 0; i < 4; i++)
	{
		if (type1[i].key == *(buf + 16))
			printf("%s\n", type1[i].value);
	}
}
/**
 *main - cp one file to other
 *@argc: Quantity of arguments
 *@argv: Value of the arguments
 *Return: 0 if success
 */
int main(int argc, char *argv[])
{
	int file_from, rd_error;
	char buf[100];

	if (argc - 1 != 1)
	{
		write(STDERR_FILENO, "Usage: elf_header elf_file\n", 28);
		exit(98);
	}
	file_from = open(argv[1], O_RDONLY);
	if (file_from == -1)
	{
		write(STDERR_FILENO, "Error: Not an RDO file\n", 24);
		exit(98);
	}
	rd_error = read(file_from, buf, 100);
	if (rd_error == -1)
	{
		write(STDERR_FILENO, "Error: Not an RDO file\n", 24);
		exit(98);
	}
	if (*buf == 0x7F)
	{
		if (*(buf + 1) == 'E' && *(buf + 2) == 'L' && *(buf + 3) == 'F')
		{
			printf("ELF Header:\n");
			first_print(buf);
			second_print(buf);
			printf("  Entry point address:");
			print_spaces(15);
			printf("0x");
			print_address(buf);
			printf("\n");
			return (0);
		}
	}
	write(STDERR_FILENO, "Error: Not an ELF file\n", 24);
	exit(98);
}
