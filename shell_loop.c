#include "shell.h"

/**
 * my_shell_loop - main shell loop
 * @info: the parameter & return info struct
 * @argv: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int my_shell_loop(info_t *info, char **argv)
{
	ssize_t read_result = 0;
	int builtin_return = 0;

	while (read_result != -1 && builtin_return != -2)
	{
		clear_info(info);
		if (interact(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		read_result = get_input(info);
		if (read_result != -1)
		{
			set_info(info, argv);
			builtin_return = find_builtin_command(info);
			if (builtin_return == -1)
				find_executable_command(info);
		} else if (interact(info))
		{
			_putchar('\n');
		}
		free_info(info, 0);
	}
	writeHistory(info);
	free_info(info, 1);
	if (!interact(info) && info->status)
		exit(info->status);
	if (builtin_return == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_return);
}

/**
 * find_builtin_command - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *         0 if builtin executed successfully,
 *         1 if builtin found but not successful,
 *         -2 if builtin signals exit()
 */
int find_builtin_command(info_t *info)
{
	int i, builtin_return = -1;
	builtin_table builtintbl[] = {
		{"myexit", my_exit},
		{"myenv", my_env},
		{"myhelp", my_help},
		{"myhistory", my_history},
		{"mysetenv", my_setenv},
		{"myunsetenv", my_unsetenv},
		{"mycd", my_cd},
		{"myalias", my_alias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
	{
		if (my_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			builtin_return = builtintbl[i].func(info);
			break;
		}
	}
	return (builtin_return);
}

/**
 * find_executable_command - finds an executable command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void find_executable_command(info_t *info)
{
	char *path = NULL;
	int i, arg_length = 0;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}

	for (i = 0; info->arg[i]; i++)
	{
		if (!is_delim(info->arg[i], " \t\n"))
		{
			arg_length++;
		}
	}

	if (!arg_length)
	{
		return;
	}
	path = find_command_in_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_executable_command(info);
	} else
	{
		if ((interact(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/')
		&& isCmd(info, info->argv[0]))
		{
			fork_executable_command(info);
		} else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_executable_command - forks an exec thread to run a command
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void fork_executable_command(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	} else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
			{
				print_error(info, "Permission denied\n");
			}
		}
	}
}
