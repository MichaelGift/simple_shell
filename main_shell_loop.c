#include "shell.h"

/**
 * hsh - the main loop.
 * @info: struct address
 * @agv: argument vector
 * Return: 0 on success or else 1
 */
int hsh(shell_info *info, char **agv)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_shell_info(info);
		if (is_interactive(info))
			_puts("$ ");
		putchar_error(BUF_FLUSH);
		r = get_input(info);
		if (r != -1)
		{
			set_shell_info(info, agv);
			builtin_ret = find_builtin(info);
			if (builtin_ret == -1)
				find_cmd(info);
		}
		else if (is_interactive(info))
			_putchar('\n');
		free_shell_info(info, 0);
	}
	write_shell_history(info);
	free_shell_info(info, 1);
	if (!is_interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - find builtin command
 * @info: struct address
 * Return: -2 builtin signal,-1 not found, 0 success, 1 unsuccessful
 */
int find_builtin(shell_info *info)
{
	int i, built_in_ret = -1;
	builtin_comms builtin_commands[] = {
		{"exit", custom_exit},
		{"env", custom_env},
		{"help", custom_help},
		{"history", custom_history},
		{"setenv", set_my_env},
		{"unsetenv", unset_my_env},
		{"cd", custom_cd},
		{"alias", custom_alias},
		{NULL, NULL}
	};

	for (i = 0; builtin_commands[i].type, i++)
	{
		if (str_cmp(info->argv[0], builtin_commands[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtin_commands[i].func(info);
			break;
		}
	}
	return (built_in_ret);
}

/**
 * find_command - find a command in PATH
 * @info: struct address
 */
void find_command(shell_info *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!is_delimiter(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(info, get_env(info, "PATH="), infor->argv[0]);
	if (path)
	{
		info->path = path;
		fork_command(info);
	}
	else
	{
		if ((is_interactive(info) || get_env(info, "PATH=")
					|| info->argv[0][0] == '/') && is_command(info, info->argv[0]))
			fork_command(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_command - fork an exec thread
 * @info: struct address
 */
void fork_command(shell_info *info)
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
			free_shell_info(info, 1);
			if (errno ==  EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
