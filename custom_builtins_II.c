#include "shell.h"

/**
 * my_alias - stand in for builtin alias
 * @info: struct address
 * Return: 0
 */
int my_alias(shell_info *info)
{
	int i = 0;
	char *p = NULL;
	str_ll *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			alias_print(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p =  str_chr(info->argv[i], '=');
		if (p)
			alias_set(info, info->argv[i]);
		else
			alias_print(node_starts_with(info->alias, info->argv[i], '='));
	}
	return (0);
}
/**
 * alias_print - prints alias strings
 * @node: the node alias
 * Return: 0 on success, 1 on error
 */
int alias_print(str_ll *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = str_chr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}


/**
 * alias_set-  sets alias to string
 * @info: struct address
 * @str: contains new alias
 * Return: 0 on success else 1
 */
int alias_set(shell_info *info, char *str)
{
	char *p;

	p = str_chr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (alias_unset(info, str));

	alias_unset(info, str);
	return (add_node_end(&(info->alias), str, 0) ==  NULL);
}

/**
 * alias_unset - changes alias to str
 * @info: struct address
 * @str: contains new alias
 * Return: 0 on success else 1
 */
int alias_unset(shell_info *info, char *str)
{
	char *p, c;
	int result;

	p = str_chr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	result = delete_node_at_index(&(info->alias),
			get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (result);

}
/**
 * command_history - displays all previously typed commands
 * @info: struct address
 * Return: 0
 */
int command_history(shell_info *info)
{
	print_llist(info->history);
	return (0);
}
