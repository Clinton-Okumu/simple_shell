#include "shell.h"

/**
 **_memset - fills memory with a constant byte
 *@ptr: the pointer to the memory area
 *@value: the byte to fill *s with
 *@n: the amount of bytes to be filled
 *Return: (s) a pointer to the memory area s
 */
char *_memset(char *ptr, char value, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		ptr[i] = value;
	return (ptr);
}

/**
 * myffree - frees a string of strings
 * @strarray: string of strings
 */
void myffree(char **strarray)
{
	char **a = strarray;

	if (!strarray)
		return;
	while (*strarray)
		free(*strarray++);
	free(a);
}

/**
 * _realloc - reallocates a block of memory
 * @old_ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *old_ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!old_ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(old_ptr), NULL);
	if (new_size == old_size)
		return (old_ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)old_ptr)[old_size];
	free(old_ptr);
	return (p);
}
