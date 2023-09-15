#include "shell.h"
/**
 * add_head_node - Add a node to the start of the list
 * @head: address of pointer to the head node
 * @str: str field of node
 * @num: node index
 *
 * Return:size of list
 */
str_ll *add_head_node(str_ll **head, const char *str, int num)
{
	str_ll *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(str_ll));
	if (!new_head)
		return (NULL);
	const_mem_set((void *)new_head, 0, sizeof(str_ll));
	new_head->num = num;
	if (str)
	{
		new_head->str = str_dup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * print_list_str - it prints only the str element of a list_t linked list
 * @h: pointer to first node
 * Return: sixe of list
 */
size_t print_list_str(const str_ll *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * add_tail_node - Add a node at the end of the list
 * @head: Pointer adderss to the head node
 * @str: String field of the node
 * @num: Node index used by history
 *
 * Return: Size of the list
 */
str_ll *add_tail_node(str_ll **head, const char *str, int num)
{
	str_ll *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(str_ll));

	if (!new_node)
		return (NULL);

	const_mem_set((void *)new_node, 0, sizeof(str_ll));
	new_node->num = num;

	if (str)
	{
		new_node->str = str_dup(str);

		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}

	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;

	return (new_node);
}

/**
 * delete_node_at_index - Delete a node at an index
 * @head: Address of pointer to first node
 * @index: Index of node to delete
 *
 * Return: 1 on success, else 0
 */
int delete_node_at_index(str_ll **head, unsigned int index)
{
	str_ll *current_node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);
	if (!index)
	{
		current_node = *head;
		*head = (*head)->next;
		free(current_node->str);
		free(current_node);
		return (1);
	}
	current_node = *head;
	while (current_node)
	{
		if (i == index)
		{
			prev_node->next = current_node->next;
			free(current_node->str);
			free(current_node);
			return (1);
		}
		i++;
		prev_node = current_node;
		node = current_node->next;
	}
	return (0);
}

/**
 * free_list - this frees all the nodes of a list
 * @head_ptr: address of pointer to head node
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

if (!head_ptr || !*head_ptr)
return;
head = *head_ptr;
node = head;
while (node)
{
next_node = node->next;
free(node->str);
free(node);
node = next_node;
}
*head_ptr = NULL;
}
