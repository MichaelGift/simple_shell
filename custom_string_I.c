#include "shell.h"
/**
 * if_starts_with_str - checks the if target_str starts with str
 * @str: string to search
 * @target_str: the substring to find
 * Return: address of next char of haystack or NULL
 */
char *if_starts_with_str(const char *str, const char *target_str)
{
	while (*target_str)
		if (*target_str++ != *str++)
			return (NULL);
	return ((char *)str);
}

/**
 * str_len - will return the lenght of a string
 * @s: the string whose lenght to check
 * Return: integer length of string
 */
int str_len(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
* str_cmp - performs lexicogarphic comparison of two strangs.
* @s1: the first strang
* @s2: the second strang
*
* Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
*/
int str_cmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
* str_cat - concatenates two strings
* @dest: the destination buffer
* @src: the source buffer
*
* Return: pointer to destination buffer
*/
char *str_cat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}

