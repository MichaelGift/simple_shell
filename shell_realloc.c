#include "shell.h"
/**
 * ffree - this fress a string of strings
 * @pp: string of strings
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		ffree(*pp++);
	ffree(a);
}

/**
* const_mem_set - Fill memory with a constant byte
* @ptr: Pointer to memory area
* @byte: The constant byte
* @len: The number of bytes to fill
* Return: Pointer to memory area 'ptr'
*/
char *const_mem_set(char *ptr, char byte, unsigned int len)
{
	unsigned int i;

	for (i = 0; i < len; i++)
		ptr[i] = byte;
	return (ptr);
}

/**
 * custom_realloc - Reallocates a block of memory
 * @ptr: Pointer to prev malloc'ated block
 * @old_size: Byte size of ptr
 * @new_size: Byte size of new ptr
 * Return: Pointer to the reallocated block
 */
void *custom_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new_ptr;
	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	
	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		new_ptr[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (new_ptr);
}
