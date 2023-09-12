#include "shell.h"

/**
 * is_chain_delimiter - checks if char is a chain delim
 * @info: struct address
 * @buffer: char buffer
 * @ptr: address of current pos
 * Return: i if true else 0
 */
int is_chain_delimiter(shell_info *info, char *buffer, size_t *ptr)
{
	size_t j = *ptr;

	if (buffer[j] == '|' && buffer[j + 1] == '|')
	{
		buffer[j] = 0;
		j++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buffer[j] == '&' && buffer[j + 1] == '&')
	{
		buffer[j] = 0;
		j++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buffer[j] == ';')
	{
		buffer[j] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*ptr = j;
	return (1);
}


/**
 * check_cmd_chain - should we continue chaining
 * @info: struct address
 * @buffer: the char buffer
 * @ptr: address of current pos
 * @i: starting pos in buffer
 * @length: size of buffer
 */
void check_cmd_chain(
		shell_info *info, char *buffer, size_t *ptr, size_t i, size_t length)
{
	size_t j = *ptr;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buffer[i] = 0;
			j = length;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buffer[i] = 0;
			j = len;
		}
	}
	*ptr = j;
}

/**
 * alias_replace - relaces an alias in the tokenized str
 * @info: struct address
 * Return: 1 on success else 0
 */
int alias_replace(shell_info *info)
{
	int i;
	str_ll *node;
	char *ptr;

	for (i = 0; i < 10; i++)
	{
		node = node_start_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);

		ptr = str_chr(node->str, '=');
		if (!ptr)
			return (0);
		ptr = str_dup(p + 1);
		if (!ptr)
			return (0);
		info->argv[0] = ptr;
	}
	return (1);
}

/**
 * substitute_vars - replaces vars in a tokenized string
 * @info: struct address
 * Return: 1 on success, else 0
 */
int substitute_vars(info_t *info)
{
	int i = 0;
	str_ll *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;
		if (!str_cmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
					str_dup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!str_cmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
					str_dup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_string(&(info->argv[i]),
					str_dup(str_chr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[i], str_dup(""));
	}
	return (0);
}

/**
 * sub_str - replaces string
 * @old_str: adkdress of old string
 * @new_str: new string
 *
 * Return: 1 on success, 0 otherwise
 */

int sub_str(char **old_str, char *new_str)
{
	free(*old_str);
	*old_str = new_str;
	return (1);
}

