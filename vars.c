#include "shell.h"

/**
 * is_chain - Check if the current character in the buffer is a chain delimiter
 * @info: The parameter struct
 * @buf: The character buffer
 * @p: Address of the current position in buf
 *
 * Return: 1 if it's a chain delimiter, 0 otherwise
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[j] == ';')
	{
		buf[j] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
	{
		return (0);
	}
	*p = j;
	return (1);
}

/**
 * check_chain - Check if we should continue chaining based on the last status
 * @info: The parameter struct
 * @buf: The character buffer
 * @p: Address of the current position in buf
 * @i: Starting position in buf
 * @len: Length of buf
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * replace_alias - Replace aliases in the tokenized string
 * @info: The parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = nodeStarts_with(info->alias, info->argv[0], '=');
		if (!node)
		{
			return (0);
		}
		
		p = _strchr(node->str, '=');
		if (!p)
		{
			return (0);
		}
		p = my_duplicate_string(p + 1);
		if (!p)
		{
			return (0);
		}
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - Replace variables in the tokenized string
 * @info: The parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
		{
			continue;
		}

		if (!my_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
					my_duplicate_string(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!my_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
					my_duplicate_string(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = nodeStarts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_string(&(info->argv[i]),
					my_duplicate_string(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[i], my_duplicate_string(""));
	}
	return (0);
}

/**
 * replace_string - Replace a string
 * @old: Address of the old string
 * @new: New string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
