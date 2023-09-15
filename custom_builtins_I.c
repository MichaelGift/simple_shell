#include "shell.h"


/**
 * custom_help - get help
 * @info: struct address
 * Return: 0
 */
int custom_help(shell_info *info)
{
	char **args;

	args = info->argv;
	custom_puts("Help call works,>>NOT IMPLEMENTED<<\n");
	if (0)
		custom_puts(*args);
	return (0);
}
/**
 * custom_exit - exits shell
 * @info: struct address
 * Return: 0 on success
 */
int custom_exit(shell_info *info)
{
	int check_exit;

	if (info->argv[1])
	{
		check_exit = error_sti(info->argv[1]);
		if (check_exit == -1)
		{
			info->status == 2;
			output_error(info, "Illegal number: ");
			puts_error(info->argv[1]);
			put_char_to_stderr('\n');
			return (1);
		}
		info->error_number = error_sti(info->argv[1]);
		return (-2);
	}
	info->error_number = -1;
	return (-2);
}

/**
 * custom_cd - changes directory
 * @info: struct address
 * Return: 0
 */
int custom_cd(shell_info *info)
{
	char *cwd, *dir, buffer[1024];
	int chdir_ret;

	cwd = getcwd(buffer, 1024);
	if (!cwd)
		custom_puts("Cannot get CWD check >>custom_builts/customk_cd<<\n");
	if (!info->argv[1])
	{
		dir = get_env(info, "HOME=");
		if (!dir)
			chdir_ret =
				chdir((dir = get_env(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (str_cmp(info->argv[1], "-") == 0)
	{
		if (!get_env(info, "OLDPWD="))
		{
			custom_puts(s);
			custom_putchar('\n');
			return (1);
		}
		custom_puts(get_env(info, "OLDPWD=")), custom_putchar('\n');
		chdir_ret =
			chdir((dir = get_env(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		output_error(info, "Cannot CD to ");
		puts_error(info->argv[1]), put_char_to_stderr('\n');
	}
	else
	{
		set_env(info, "OLDPWD", get_env(info, "PWD="));
		set_env(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

