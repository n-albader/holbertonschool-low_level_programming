#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

/**
 * main - copies the content of one file to another file
 * @argc: number of arguments
 * @argv: arguments
 *
 * Return: 0 on success, or an error code on failure
 */
int main(int argc, char **argv)
{
	int fd_from, fd_to;
	ssize_t bytes_read, bytes_written;
	char buffer[1024];

	if (argc != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		return (97);
	}

	fd_from = open(argv[1], O_RDONLY);
	if (fd_from == -1)
	{
		dprintf(STDERR_FILENO,
			"Error: Can't read from file %s\n", argv[1]);
		return (98);
	}

	fd_to = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd_to == -1)
	{
		dprintf(STDERR_FILENO,
			"Error: Can't write to %s\n", argv[2]);
		if (close(fd_from) == -1)
		{
			dprintf(STDERR_FILENO,
				"Error: Can't close fd %d\n", fd_from);
			return (100);
		}
		return (99);
	}

	while ((bytes_read = read(fd_from, buffer, 1024)) > 0)
	{
		bytes_written = write(fd_to, buffer, bytes_read);

		if (bytes_written != bytes_read)
		{
			dprintf(STDERR_FILENO,
				"Error: Can't write to %s\n", argv[2]);

			if (close(fd_from) == -1)
			{
				dprintf(STDERR_FILENO,
					"Error: Can't close fd %d\n", fd_from);
				return (100);
			}

			if (close(fd_to) == -1)
			{
				dprintf(STDERR_FILENO,
					"Error: Can't close fd %d\n", fd_to);
				return (100);
			}

			return (99);
		}
	}

	if (bytes_read == -1)
	{
		dprintf(STDERR_FILENO,
			"Error: Can't read from file %s\n", argv[1]);

		if (close(fd_from) == -1)
		{
			dprintf(STDERR_FILENO,
				"Error: Can't close fd %d\n", fd_from);
			return (100);
		}

		if (close(fd_to) == -1)
		{
			dprintf(STDERR_FILENO,
				"Error: Can't close fd %d\n", fd_to);
			return (100);
		}

		return (98);
	}

	if (close(fd_from) == -1)
	{
		dprintf(STDERR_FILENO,
			"Error: Can't close fd %d\n", fd_from);
		return (100);
	}

	if (close(fd_to) == -1)
	{
		dprintf(STDERR_FILENO,
			"Error: Can't close fd %d\n", fd_to);
		return (100);
	}

	return (0);
}
