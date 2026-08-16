#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <elf.h>

/**
 * get_value - gets a value from ELF header
 * @p: pointer to the value
 * @size: size of the value
 * @big: endianness
 *
 * Return: value
 */
unsigned long get_value(unsigned char *p, int size, int big)
{
	unsigned long value;
	int i;

	value = 0;

	if (big)
	{
		for (i = 0; i < size; i++)
			value = (value << 8) | p[i];
	}
	else
	{
		for (i = size - 1; i >= 0; i--)
			value = (value << 8) | p[i];
	}

	return (value);
}

/**
 * print_magic - prints ELF magic
 * @header: ELF header
 */
void print_magic(unsigned char *header)
{
	int i;

	printf("  Magic:   ");
	for (i = 0; i < EI_NIDENT; i++)
	{
		printf("%02x", header[i]);
		if (i < EI_NIDENT - 1)
			printf(" ");
	}
	printf("\n");
}

/**
 * print_osabi - prints ELF OS/ABI
 * @abi: OS/ABI value
 */
void print_osabi(unsigned char abi)
{
	char *name;

	name = NULL;

	switch (abi)
	{
		case ELFOSABI_SYSV:
			name = "UNIX - System V";
			break;
		case ELFOSABI_HPUX:
			name = "HP-UX";
			break;
		case ELFOSABI_NETBSD:
			name = "UNIX - NetBSD";
			break;
		case ELFOSABI_LINUX:
			name = "GNU/Linux";
			break;
		case ELFOSABI_SOLARIS:
			name = "UNIX - Solaris";
			break;
		case ELFOSABI_AIX:
			name = "AIX";
			break;
		case ELFOSABI_IRIX:
			name = "IRIX";
			break;
		case ELFOSABI_FREEBSD:
			name = "FreeBSD";
			break;
		case ELFOSABI_TRU64:
			name = "TRU64 UNIX";
			break;
		case ELFOSABI_OPENBSD:
			name = "OpenBSD";
			break;
		default:
			printf("  OS/ABI:                            <unknown: %02x>\n",
			       abi);
			return;
	}

	printf("  OS/ABI:                            %s\n", name);
}

/**
 * print_type - prints ELF type
 * @type: ELF type
 */
void print_type(unsigned short type)
{
	switch (type)
	{
		case ET_NONE:
			printf("  Type:                              NONE (No file type)\n");
			break;
		case ET_REL:
			printf("  Type:                              REL (Relocatable file)\n");
			break;
		case ET_EXEC:
			printf("  Type:                              EXEC (Executable file)\n");
			break;
		case ET_DYN:
			printf("  Type:                              DYN (Shared object file)\n");
			break;
		case ET_CORE:
			printf("  Type:                              CORE (Core file)\n");
			break;
		default:
			printf("  Type:                              <unknown>: %u\n", type);
	}
}

/**
 * main - displays ELF header information
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success, 98 on error
 */
int main(int argc, char **argv)
{
	int fd, big;
	ssize_t bytes;
	unsigned char header[64];
	unsigned long entry, type;

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

	bytes = read(fd, header, sizeof(header));
	if (bytes < 52)
	{
		dprintf(STDERR_FILENO, "Error: Can't read ELF header from %s\n",
			argv[1]);
		close(fd);
		return (98);
	}

	if (header[EI_MAG0] != ELFMAG0 || header[EI_MAG1] != ELFMAG1 ||
	    header[EI_MAG2] != ELFMAG2 || header[EI_MAG3] != ELFMAG3)
	{
		dprintf(STDERR_FILENO, "Error: %s is not an ELF file\n", argv[1]);
		close(fd);
		return (98);
	}

	if (header[EI_CLASS] != ELFCLASS32 &&
	    header[EI_CLASS] != ELFCLASS64)
	{
		dprintf(STDERR_FILENO, "Error: Invalid ELF class in %s\n",
			argv[1]);
		close(fd);
		return (98);
	}

	if (header[EI_DATA] != ELFDATA2LSB &&
	    header[EI_DATA] != ELFDATA2MSB)
	{
		dprintf(STDERR_FILENO, "Error: Invalid ELF data encoding in %s\n",
			argv[1]);
		close(fd);
		return (98);
	}

	big = (header[EI_DATA] == ELFDATA2MSB);

	printf("ELF Header:\n");
	print_magic(header);
	printf("  Class:                             %s\n",
	       header[EI_CLASS] == ELFCLASS32 ? "ELF32" : "ELF64");
	printf("  Data:                              %s\n",
	       big ? "2's complement, big endian" :
	       "2's complement, little endian");
	printf("  Version:                           %u", header[EI_VERSION]);

	if (header[EI_VERSION] == EV_CURRENT)
		printf(" (current)");

	printf("\n");

	print_osabi(header[EI_OSABI]);
	printf("  ABI Version:                       %u\n", header[EI_ABIVERSION]);

	type = get_value(header + 16, 2, big);
	print_type((unsigned short)type);

	if (header[EI_CLASS] == ELFCLASS32)
		entry = get_value(header + 24, 4, big);
	else
		entry = get_value(header + 24, 8, big);

	printf("  Entry point address:               0x%lx\n", entry);

	if (close(fd) == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close file %s\n", argv[1]);
		return (98);
	}

	return (0);
}
