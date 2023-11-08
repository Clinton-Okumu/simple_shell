#include "shell.h"
/**
 * directory_changes - Change the current working directory.
 * @info: Structure containing potential arguments.
 * Return: 0 on success, -1 on error.
 */
int directory_changes(info_t *info)
{
	char *dir, buffer[1024];
	int chdir_ret;
	char *arg = info->argv[1];

	char *home = _getenv(info, "HOME=");
	char *oldpwd = _getenv(info, "OLDPWD=");

	if (arg == NULL || _STRCMP(ARG, "~") == 0)
	{
		dir = home ? home : "/";
	} else if
		(_strcmp(arg, "~") == 0)
		{
			if (oldpwd == NULL)
			{
				_puts("cd: OLDPWD not set\n");
				return (-1);
			}
			dir = oldpwd;
			_puts(oldpwd), _putchar('\n');
		} else
		{
			dir = arg;
		}

		chdir_ret = chdir(dir);
		if (chdir_ret == -1)
		{
			print_error(info, "cd: cannot change to ");
			_eputs(dir), _putchar('\n');
			return (-1);
		}

		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));

		return (0);
}

/**
 * get_help - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int get_help(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("hepls in getting help \n");
	if (0)
		_puts(arg_array);
	return (0);
}

/**
 * for_exit - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int for_exit(info_t *info)
{
	int exitcheck;

	if (info->argv[1])  /* If there is an exit arguement */
	{
		exitcheck = _erratoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}
