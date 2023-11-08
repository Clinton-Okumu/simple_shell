#include "shell.h"
/**
 * print_environment - prints the current environment variables
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
 */
int print_environment(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * get_environment_variable - gets the value of an environment variable
 * @info: Structure containing potential arguments.
 * @name: environment variable name
 * Return: the value of the environment variable or NULL if not found
 */
char *get_environment_variable(info_t *info, const char *name)
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
 * set_environment_variable - Initialize a new environment variable.
 * @info: Structure containing potential arguments.
 * Return: 0 on success, 1 on error
 */
int set_environment_variable(info_t *info)
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
 * unset_environment_variable - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int unset_environment_variable(info_t *info)
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
 * initialize_environment - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int initialize_environment(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
