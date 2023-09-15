#include "shell.h"

/**
 * str_chr - string finder
 * @str: string store
 * @c: target char
 * Return: pointer to str
 */
char *str_chr(char *str, char c)
{
	do {
		if (*str == c)
			return (str);
	} while (*str++ != '\0');
	return (NULL);
}

/**
 * strn_cpy - copy str
 * @dest: string destination
 * @src: string source
 * @len: length of chars
 * Return: concatenated string
 */
char *strn_cpy(char *dest, char *src, int len)
{
	int i = 0, j;
	char *s = dest;

	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 * strn_cat - concats two string
 * @dest: destination
 * @src: source
 * @len: amount of bytes needed
 * Return: pointer to str
 */
char *strn_cat(char *dest, char *src, int len)
{
	int i = 0, j = 0;
	char *s = dest;

	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}

