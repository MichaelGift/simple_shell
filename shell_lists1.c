#include "shell.h"
/**
 * llist_to_strarr - will return an array of strings of the list
 * @head: pointer to the first node
 * Return: array of strings
 */
char **llist_to_strarr(str_ll *head)
{
	str_ll *node = head;
	size_t i = list_str_ll_len(head), j;
	char **strs;
	char *str;
	
	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(str_len(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
			free(strs[j]);
			free(strs);
			return (NULL);
		}
		str = str_cpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}

/**
 * list_str_ll_len - this determines the lenght of linked list
 * @head: Pointer to head node
 * Return: size of list
 */
size_t list_str_ll_len(const str_ll *head)
{
	size_t i = 0;

	while (head)

	{
		head = head->next;
		i++;
	}
	return (i);
}

/**
 * node_starts_with - will return node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character afetr prefix to match
 * Return: match node or null
 */
str_ll *node_starts_with(str_ll *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = if_starts_with_str(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - will get the index of a node
 * @head: pointer list head
 * @node: pointer to the node
 * Return: index of node or -1
 */
ssize_t get_node_index(str_ll *head, str_ll *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}

/**
 * print_llist - prints all elements of a str_ll linked list
 * @head: pointer to head node
 * Return: size of list
 */
size_t print_llist(const str_ll *head)
{
	size_t i = 0;

	while (head)
	{
		custom_puts(number_converter(head->num, 10, 0));
		custom_putchar(' : ');
		custom_putchar(' ');
		custom_puts(head->str ? head->str : "(nil)");
		custom_puts("\n");
		head = head->next;
		i++;
	}
	return (i);
}
