#include "shell.h"

/**
 * get_env - gets environ variable
 * @info: struct address
 * @name: environ name
 * Return: environ
 */
char *get_env(shell_info *info, const char *name)
{
	str_ll *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * unset_my_env - remove my env
 * @info: struct address
 * Return: 0
 */
int unset_my_env(shell_info *info)
{
	int i;

	if (info->argc == 1)
	{
		puts_error("Too few arguments.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		unset_env(info, info->argv[i]);
	return (0);
}
/**
 * set_my_env - set a new environ variables
 * @info: struct address
  * Return: 0
 */
int set_my_env(shell_info *info)
{
	if (info->argc != 3)
	{
		puts_error("Wrong number of arguments\n");
		return (1);
	}
	if (set_env(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * my_env - prints current env
 * @info: struct address
 * Return: 0
 */
int my_env(shell_info *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * add_envs_to_llist- add env's to linked list
 * @info: struct address
 * Return: 0
 */
int add_envs_to_llist(shell_info *info)
{
	str_ll *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
