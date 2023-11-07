#include "shell.h"

/**
 * my_copy_string - copies a string
 * @destination: the destination
 * @source: the source
 *
 * Return: pointer to the destination
 */
char *my_copy_string(char *destination, const char *source)
{
    int i = 0;

    if (destination == source || source == 0)
        return (destination);
    while (source[i])
    {
        destination[i] = source[i];
        i++;
    }
    destination[i] = '\0';
    return (destination);
}

/**
 * my_duplicate_string - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *my_duplicate_string(const char *str)
{
    int length = 0;
    char *result;

    if (str == NULL)
        return (NULL);
    while (*str++)
        length++;
    result = malloc(sizeof(char) * (length + 1));
    if (!result)
        return (NULL);
    for (length++; length--;)
        result[length] = *--str;
    return (result);
}

/**
 * my_print_string - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void my_print_string(const char *str)
{
    int i = 0;

    if (!str)
        return;
    while (str[i] != '\0')
    {
        my_putchar(str[i]);
        i++;
    }
}

/**
 * my_putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int my_putchar(char c)
{
    static int i;
    static char buffer[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(1, buffer, i);
        i = 0;
    }
    if (c != BUF_FLUSH)
        buffer[i++] = c;
    return (1);
}
