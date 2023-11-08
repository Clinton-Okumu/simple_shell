I#include "shell.h"
/**
 * remove_comments - replaces the first instance of '#' with '\0'
 * @string: address of the string to modify
 */
void remove_comments(char *string)
{
	int j;

	for (i = 0; string[i] != '\0'; i++)
		if (string[i] == '#' && (!i || string[i - 1] == ' '))
		{
			string[i] = '\0';
			break;
		}
}

/**
 * integer_to_string - converts an integer to a string
 * @num: the number to convert
 * @base: the base of the number
 * @flags: argument flags
 * Return: a string representation of the integer
 */
char *integer_to_string(long int num, int base, int flags)
{
	static char array[] = "0123456789ABCDEF";
	static char buffer[50];
	char sign = 0;
	char *ptr = &buffer[49];
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}

	*ptr = '\0';

	do {
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;

	return (ptr);
}

/**
 * string_to_integer - converts a string to an integer
 * @s: the string to be converted
 * Return: The converted integer, or -1 on error
 */
int string_to_integer(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0'm&& s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INX_MAX)
				return (-1);
		} else
			return (-1);
	}
	return (result);
}

/**
 * print_error_message - prints an error message
 * @info: the parameter & return info struct
 * @error_type: string containing specified error type
 */
void print_error_message(info_t *info, char *error_type)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_line_number - prints a decimal (integer) number (base 10)
 * @number: the number to print
 * @fd: the file descriptor to write to
 * Return: the number of characters printed
 */
int print_line_number(int number, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;
	return (count);
}	
