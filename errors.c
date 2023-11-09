#include "shell.h"
/**
 * writeCharToStdErr - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success, 1. On error, -1 is returned, and errno is set appropriately.
 */
int writeCharToStdErr(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || I >= WRITE_BUF_SIZE)
	{
		IF (WRITE(2, BUF, I) == -1)
		{
			PERROR("Error writing to stderr");
			return (-1);
		}
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * writeStringToFD - writes an input string to the given file descriptor
 * @str: the string to be printed
 * @fd: the file descriptor to write to
 *
 * Return: the number of characters written
 */
int writeStringToFD(char *str, int fd)
{
	int charCount = 0;

	if (!str)
		return (0);
	while (*str)
	{
		if (_putfd(*str++, fd) == -1)
		{
			perror("Error writing to file descriptor");
			return (-1);
		}
		charCount++;
	}
	return (charCount);
}

/**
 *_eputs - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_eputchar(str[i]);
		i++;
	}
}

/**
 * _eputchar - writes a character to the standard error (stderr)
 * @c: The character to be printed
 *
 * Return: On success, it returns 1. On error, it returns -1.
 */
int _eputchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
	{
		buf[i++] = c;
	}
	return (1);
}
