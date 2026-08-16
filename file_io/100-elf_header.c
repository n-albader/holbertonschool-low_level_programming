#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

/**
 * get16 - gets a 16-bit value
 * @p: pointer to bytes
 * @big: endianness
 *
 * Return: value
 */
unsigned short get16(unsigned char *p, int big)
{
	if (big)
		return ((unsigned short)p[0] << 8 | p[1]);

	return ((unsigned short)p[1] << 8 | p[0]);
}

/**
 * get32 - gets a 32-bit value
 * @p: pointer to bytes
 * @big: endianness
 *
 * Return: value
 */
unsigned long get32(unsigned char *p, int big)
{
	unsigned long value;

	if (big)
	{
		value = (unsigned long)p[0] << 24;
		value |= (unsigned long)p[1] << 16;
		value |= (unsigned long)p[2] << 8;
		value |= p[3];
	}
	else
	{
		value = (unsigned long)p[3] << 24;
		value |= (unsigned long)p[2] << 16;
		value |= (unsigned long)p[1] << 8;
		value |= p[0];
	}

	return (value);
}

/**
 * get64 - gets a 64-bit value
 * @p: pointer to bytes
 * @big: endianness
 *
 * Return: value
 */
unsigned long get64(unsigned char *p, int big)
{
	unsigned long value;
	int i;

	value = 0;

	if (big)
	{
		for (i = 0; i < 8; i++)
			value = (value << 8) | p[i];
	}
	else
	{
		for (i = 7; i >= 0; i--)
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

	for (i = 0; i < 16; i++)
		printf("%02x%s", header[i], i == 15 ? "\n" : " ");
}

/**
 * print_osabi - prints OS/ABI
 * @abi: OS/ABI value
 */
void print_osabi(unsigned char abi)
{
	printf("  OS/ABI:                            ");

	switch (abi)
	{
		case 0:
			printf("UNIX - System V\n");
			break;
		case 1:
			printf("HP-UX\n");
			break;
		case 2:
			printf("UNIX - NetBSD\n");
			break;
		case 3:
			printf("GNU/Linux\n");
			break;
		case 6:
			printf("UNIX - Solaris\n");
			break;
		case 7:
			printf("AIX\n");
			break;
		case 8:
			printf("IRIX\n");
			break;
		case 9:
			printf("FreeBSD\n");
			break;
		case 10:
			printf("TRU64 UNIX\n");
			break;
		case 11:
			printf("Novell Modesto\n");
			break;
		case 12:
			printf("OpenBSD\n");
			break;
		case 13:
			printf("OpenVMS\n");
			break;
		case 14:
			printf("NonStop Kernel\n");
			break;
		case 15:
			printf("AROS\n");
			break;
		case 16:
			printf("FenixOS\n");
			break;
		case 17:
			printf("CloudABI\n");
			break;
		default:
			printf("<unknown: %02x>\n", abi);
			break;
	}
}

/**
 * print_type - prints ELF type
 * @header: ELF header
 * @big: endianness
 */
void print_type(unsigned char *header, int big)
{
	unsigned short type;

	type = get16(header + 16, big);

	printf("  Type:                             ");

	switch (type)
	{
		case 0:
			printf("NONE (No file type)\n");
			break;
		case 1:
			printf("REL (Relocatable file)\n");
			break;
		case 2:
			printf("EXEC (Executable file)\n");
			break;
		case 3:
			printf("DYN (Shared object file)\n");
			break;
		case 4:
			printf("CORE (Core file)\n");
			break;
		default:
			printf("<unknown>: %u\n", type);
			break;
	}
}

/**
 * print_entry - prints entry point
 * @header: ELF header
 * @class: ELF class
 * @big: endianness
 */
void print_entry(unsigned char *header, unsigned char class, int big)
{
	unsigned long entry;

	entry = 0;

	if (class == 1)
		entry = get32(header + 24, big);
	else
		entry = get64(header + 24, big);

	printf("  Entry point address:               0x%lx\n", entry);
}

/**
 * main - displays ELF header information
 * @argc: number of arguments
 * @argv: arguments
 *
 * Return: 0 on success, 98 on error
 */
int main(int argc, char **argv)
{
	int fd;
	int big;
	ssize_t bytes;
	unsigned char header[64];
	unsigned char class;

	if (argc != 2)
	{
		dprintf(STDERR_FILENO,
			"Usage: elf_header elf_filename\n");
		return (98);
	}

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		dprintf(STDERR_FILENO,
			"Error: Can't open file %s\n", argv[1]);
		return (98);
	}

	bytes = read(fd, header, 64);
	if (bytes < 52)
	{
		dprintf(STDERR_FILENO,
			"Error: Can't read ELF header from %s\n", argv[1]);
		close(fd);
		return (98);
	}

	if (header[0] != 0x7f || header[1] != 'E' ||
	    header[2] != 'L' || header[3] != 'F')
	{
		dprintf(STDERR_FILENO,
			"Error: %s is not an ELF file\n", argv[1]);
		close(fd);
		return (98);
	}

	class = header[4];

	if (class != 1 && class != 2)
	{
		dprintf(STDERR_FILENO,
			"Error: Invalid ELF class in %s\n", argv[1]);
		close(fd);
		return (98);
	}

	if (header[5] != 1 && header[5] != 2)
	{
		dprintf(STDERR_FILENO,
			"Error: Invalid ELF data encoding in %s\n", argv[1]);
		close(fd);
		return (98);
	}

	big = (header[5] == 2);

	printf("ELF Header:\n");

	print_magic(header);

	printf("  Class:                             %s\n",
	       class == 1 ? "ELF32" : "ELF64");

	printf("  Data:                              %s\n",
	       big ? "2's complement, big endian" :
	       "2's complement, little endian");

	printf("  Version:                           %u %s\n",
	       header[6],
	       header[6] == 1 ? "(current)" : "(invalid)");

	print_osabi(header[7]);

	printf("  ABI Version:                       %u\n", header[8]);

	print_type(header, big);

	print_entry(header, class, big);

	if (close(fd) == -1)
	{
		dprintf(STDERR_FILENO,
			"Error: Can't close file %s\n", argv[1]);
		return (98);
	}

	return (0);
}
