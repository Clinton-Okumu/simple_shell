#include "shell.h"
/**
 * my_env - prints the current environment variables
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int my_env(info_t *info)
{
	printListStr(info->env);
	return (0);
}

/**
 * _getenv - gets the value of an environment variable
 * @info: Structure containing potential arguments.
 * @name: environment variable name
 * Return: the value of the environment variable or NULL if not found
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;

	while (node)
	{
		if (starts_with(node->str, name))
			return (node->str);
		node = node->next;
	}
	return (NULL);
}

/**
 * my_setenv - Initialize a new environment variable.
 * @info: Structure containing potential arguments.
 * Return: 0 on success, 1 on error
 */
int my_setenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * my_unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int my_unsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * populate_env_list - populates the env linked list.
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		addNodeEnd(&node, environ[i], 0);
	info->env = node;
	return (0);
}
