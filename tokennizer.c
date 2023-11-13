#include "shell.h"

/**
 * strtow - Split a string into words using a delimiter string
 * @str: The input string to split
 * @d: The delimiter string used for splitting
 *
 * Return: A pointer to an array of strings (words), or NULL on failure
 */
char **strtow(char *str, char *d)
{
	int i, j, k, m, numwords = 0;
	char **words;

	if (str == NULL || str[0] == '\0')
		return (NULL);

	if (!d)
		d = " ";

	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], d) && (is_delim(str[i + 1], d) || !str[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);

	words = malloc((1 + numwords) * sizeof(char *));
	if (!words)
		return (NULL);

	for (i = 0, j = 0; j < numwords; j++)
	{
		while (is_delim(str[i], d))
			i++;

		k = 0;
		while (!is_delim(str[i + k], d) && str[i + k])
			k++;

		words[j] = malloc((k + 1) * sizeof(char));
		if (!words[j])
		{
			for (k = 0; k < j; k++)
				free(words[k]);
			free(words);
			return (NULL);
		}

		for (m = 0; m < k; m++)
			words[j][m] = str[i++];

		words[j][m] = '\0';
	}

	words[j] = NULL;
	return (words);
}

/**
 * strtow2 - Split a string into words using a single character delimiter
 * @str: The input string to split
 * @delim: The delimiter character used for splitting
 *
 * Return: A pointer to an array of strings (words), or NULL on failure
 */
char **strtow2(char *str, char d)
{
	int i, j, k, m, numwords = 0;
	char **words;

	if (str == NULL || str[0] == '\0')
		return (NULL);

	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
			(str[i] != d && !str[i + 1]) || str[i + 1] == d)
			numwords++;

	if (numwords == 0)
		return (NULL);

	words = malloc((1 + numwords) * sizeof(char *));
	if (!words)
		return (NULL);

	for (i = 0, j = 0; j < numwords; j++)
	{
		while (str[i] == d && str[i] != d)
			i++;

		k = 0;
		while (str[i + k] != d && str[i + k] && str[i + k] != d)
			k++;

		words[j] = malloc((k + 1) * sizeof(char));
		if (!words[j])
		{
			for (k = 0; k < j; k++)
				free(words[k]);
			free(words);
			return (NULL);
		}

		for (m = 0; m < k; m++)
			words[j][m] = str[i++];

		words[j][m] = '\0';
	}

	words[j] = NULL;
	return (words);
}
