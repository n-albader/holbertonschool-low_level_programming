#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <elf.h>

/**
 * print_magic - prints the ELF magic
 * @h: ELF header
 *
 * Return: Nothing
 */
void print_magic(unsigned char *h)
{
	int i;

	printf("  Magic:   ");
	for (i = 0; i < EI_NIDENT; i++)
	{
		printf("%02x", h[i]);
		if (i < EI_NIDENT - 1)
			printf(" ");
	}
	printf("\n");
}

/**
 * print_osabi - prints the ELF OS/ABI
 * @h: ELF header
 *
 * Return: Nothing
 */
void print_osabi(unsigned char *h)
{
	unsigned char a;

	a = h[EI_OSABI];
	printf("  OS/ABI:                            ");

	if (a == ELFOSABI_SYSV)
		printf("UNIX - System V");
	else if (a == ELFOSABI_HPUX)
		printf("HP-UX");
	else if (a == ELFOSABI_NETBSD)
		printf("UNIX - NetBSD");
	else if (a == ELFOSABI_LINUX)
		printf("UNIX - GNU/Linux");
	else if (a == ELFOSABI_SOLARIS)
		printf("UNIX - Solaris");
	else if (a == ELFOSABI_AIX)
		printf("AIX");
	else if (a == ELFOSABI_IRIX)
		printf("IRIX");
	else if (a == ELFOSABI_FREEBSD)
		printf("FreeBSD");
	else if (a == ELFOSABI_TRU64)
		printf("TRU64 UNIX");
	else if (a == ELFOSABI_OPENBSD)
		printf("OpenBSD");
	else
		printf("<unknown: %02x>", a);

	printf("\n");
}

/**
 * print_type - prints the ELF type
 * @h: ELF header
 * @big: endianness flag
 *
 * Return: Nothing
 */
void print_type(unsigned char *h, int big)
{
	unsigned int type;

	if (big)
		type = ((unsigned int)h[16] << 8) | h[17];
	else
		type = ((unsigned int)h[17] << 8) | h[16];

	printf("  Type:                              ");

	if (type == ET_NONE)
		printf("NONE (No file type)\n");
	else if (type == ET_REL)
		printf("REL (Relocatable file)\n");
	else if (type == ET_EXEC)
		printf("EXEC (Executable file)\n");
	else if (type == ET_DYN)
		printf("DYN (Shared object file)\n");
	else if (type == ET_CORE)
		printf("CORE (Core file)\n");
	else
		printf("<unknown>: %u\n", type);
}

/**
 * print_header - prints ELF header information
 * @h: ELF header
 *
 * Return: Nothing
 */
void print_header(unsigned char *h)
{
	unsigned long entry;
	int big, i, size;

	big = h[EI_DATA] == ELFDATA2MSB;
	printf("ELF Header:\n");
	print_magic(h);

	printf("  Class:                             ");
	printf("%s\n", h[EI_CLASS] == ELFCLASS32 ? "ELF32" : "ELF64");

	printf("  Data:                              ");
	printf("%s\n", big ? "2's complement, big endian" :
	       "2's complement, little endian");

	printf("  Version:                           %u", h[EI_VERSION]);
	if (h[EI_VERSION] == EV_CURRENT)
		printf(" (current)");
	printf("\n");

	print_osabi(h);
	printf("  ABI Version:                       %u\n", h[EI_ABIVERSION]);

	print_type(h, big);

	size = h[EI_CLASS] == ELFCLASS32 ? 4 : 8;
	entry = 0;

	if (big)
	{
		for (i = 0; i < size; i++)
			entry = (entry << 8) | h[24 + i];
	}
	else
	{
		for (i = size - 1; i >= 0; i--)
			entry = (entry << 8) | h[24 + i];
	}

	printf("  Entry point address:               0x%lx\n", entry);
}

/**
 * main - displays information contained in an ELF header
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success, 98 on error
 */
int main(int argc, char **argv)
{
	int fd;
	ssize_t n;
	unsigned char h[64];

	if (argc != 2)
	{
		dprintf(STDERR_FILENO, "Usage: elf_header elf_filename\n");
		return (98);
	}

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't open file %s\n", argv[1]);
		return (98);
	}

	n = read(fd, h, sizeof(h));
	if (n < 52 || h[EI_MAG0] != ELFMAG0 ||
	    h[EI_MAG1] != ELFMAG1 || h[EI_MAG2] != ELFMAG2 ||
	    h[EI_MAG3] != ELFMAG3)
	{
		dprintf(STDERR_FILENO, "Error: %s is not an ELF file\n", argv[1]);
		close(fd);
		return (98);
	}

	if ((h[EI_CLASS] != ELFCLASS32 && h[EI_CLASS] != ELFCLASS64) ||
	    (h[EI_DATA] != ELFDATA2LSB && h[EI_DATA] != ELFDATA2MSB))
	{
		dprintf(STDERR_FILENO, "Error: Invalid ELF header in %s\n", argv[1]);
		close(fd);
		return (98);
	}

	print_header(h);

	if (close(fd) == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close file %s\n", argv[1]);
		return (98);
	}

	return (0);
}
