#include "shell.h"


/**
 * initialize_shell_info - initilizes the shell_info struct
 * @info: Pointer to shell_info struct
 */
void initialize_shell_info(shell_info *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
  * set_shell_info - inits shell_info struct
  * @info: struct address
  * @agv: argument number
  */
void set_shell_info(shell_info *info, char **agv)
{
	int i = 0;

	info->fname = agv[0];
	if (info->arg)
	{
		info->argv = str_tow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = str_dup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;
		alias_replace(info);
		substitute_vars(info);
	}
}
/**
 * free_shell_info - frees shell_info struct
 * @info: struct address
 * @all_fields: free all fields?
 */
void free_shell_info(shell_info *info, int all_fields)
{
	free_field(info->argv);
	info->argv = NULL;
	info->path = NULL;

	if (all_fields)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		free_field(info->environ);
		info->environ = NULL;
		free_buffer((void **)info->cmd_buf);
		if (info->read_file_d > 2)
			close(info->read_file_d);
		custom_putchar(FLUSH_BUFFER);
	}
}
