#include "shell.h"
/**
 * free_buffer - it frees a pointer and NULLS the address
 * @ptr: it is the address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */

int free_buffer(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
