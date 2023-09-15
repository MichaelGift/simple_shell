#include "shell.h"
/**
 * str_cpy - this copies a string
 * @dest: the destination
 * @src: the source
 * Return: pointer to destination
 */
char *str_cpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * str_dup - this duplicates a string
 * @str: the string to be duplicated
 * Return: pointer to the duplicated string
 */
char *str_dup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 * custom_puts - this prints an input string
 * @str: the string to that will be printed
 * Return: nothing
 */
void custom_puts(char *str)
{
	int index = 0;

	if (!str)
		return;
	while (str[index] != '\0')
	{
		custom_putchar(str[index]);
		index++;
	}
}

/**
 * custom_putchar - this writes the character c to stdout
 * @c: the character to print
 * Return: on success 1.
 * on error, -1 is returned, and errno is set appropriately.
 */
int custom_putchar(char c)
{
	static int i;
	static char buf[WRITE_BUFFER_SIZE];

	if (c == FLUSH_BUFFER || i >= WRITE_BUFFER_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != FLUSH_BUFFER)
		buf[i++] = c;
	return (1);
}

