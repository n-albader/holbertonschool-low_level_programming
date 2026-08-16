#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

/**
 * close_file - closes a file descriptor
 * @fd: file descriptor to close
 *
 * Return: 0 on success, 100 on failure
 */
int close_file(int fd)
{
	if (close(fd) == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd);
		return (100);
	}

	return (0);
}

/**
 * copy_file - copies the content of one file to another
 * @fd_from: source file descriptor
 * @fd_to: destination file descriptor
 * @filename: name of the source file
 *
 * Return: 0 on success, 98 on read failure, 99 on write failure
 */
int copy_file(int fd_from, int fd_to, char *filename)
{
	char buffer[1024];
	ssize_t bytes_read;
	ssize_t bytes_written;

	while ((bytes_read = read(fd_from, buffer, 1024)) > 0)
	{
		bytes_written = write(fd_to, buffer, bytes_read);
		if (bytes_written != bytes_read)
		{
			dprintf(STDERR_FILENO,
				"Error: Can't write to %s\n", filename);
			return (99);
		}
	}

	if (bytes_read == -1)
	{
		dprintf(STDERR_FILENO,
			"Error: Can't read from file %s\n", filename);
		return (98);
	}

	return (0);
}

/**
 * open_source - opens the source file
 * @filename: name of the source file
 *
 * Return: file descriptor on success, 98 on failure
 */
int open_source(char *filename)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		dprintf(STDERR_FILENO,
			"Error: Can't read from file %s\n", filename);
		return (-1);
	}

	return (fd);
}

/**
 * open_destination - opens the destination file
 * @filename: name of the destination file
 *
 * Return: file descriptor on success, -1 on failure
 */
int open_destination(char *filename)
{
	int fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (fd == -1)
	{
		dprintf(STDERR_FILENO,
			"Error: Can't write to %s\n", filename);
		return (-1);
	}

	return (fd);
}

/**
 * main - copies the content of one file to another
 * @argc: number of arguments
 * @argv: arguments
 *
 * Return: 0 on success, or an error code on failure
 */
int main(int argc, char **argv)
{
	int fd_from, fd_to, result;

	if (argc != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		return (97);
	}

	fd_from = open_source(argv[1]);
	if (fd_from == -1)
		return (98);

	fd_to = open_destination(argv[2]);
	if (fd_to == -1)
	{
		close_file(fd_from);
		return (99);
	}

	result = copy_file(fd_from, fd_to, argv[1]);
	if (result != 0)
	{
		if (close_file(fd_from) == 100)
			return (100);
		if (close_file(fd_to) == 100)
			return (100);
		return (result);
	}

	if (close_file(fd_from) == 100)
		return (100);

	if (close_file(fd_to) == 100)
		return (100);

	return (0);
}
