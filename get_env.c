#include "shell.h"

/**
 * set_env - sets env variable
 * @info: struct address
 * @var: env var property
 * @val: env var value
 * Return: 0
 */
int set_env(shell_info *info, char *var, char *val)
{
	char *buffer = NULL;
	str_ll *node;
	char *ptr;

	if (!var || !val)
		return (0);

	buffer = malloc(str_len(var) + str_len(val) + 2);
	if (!buffer)
		return (1);
	str_cpy(buffer, var);
	str_cat(buffer, "=");
	str_cat(buffer, val);
	node = info->env;

	while (node)
	{
		ptr = if_starts_with_str(node->str, var);
		if (ptr && *ptr == '=')
		{
			free(node->str);
			node->str = buffer;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_tail_node(&(info->env), buffer, 0);
	free(buffer);
	info->env_changed = 1;
	return (0);
}
/**
 * unset_env - remove environment variable
 * @info: struct address
 * @var: env var string
 * Return: 1 on sucess else 0
 */
int unset_env(shell_info *info, char *var)
{
	str_ll *node = info->env;
	size_t i = 0;
	char *ptr;

	if (!node || !var)
		return (0);
	while (node)
	{
		ptr = if_starts_with_str(node->str, var);
		if (ptr && *ptr == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}
/**
 * get_shell_environ - returns array copy of our environ
 * @info: struct address
 * Return: Always 0
 */
char **get_shell_environ(shell_info *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = llist_to_strarr(info->env);
		info->env_changed = 0;
	}
	return (info->environ);
}
