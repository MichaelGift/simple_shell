#include "shell.h"


/**
 * string_to_int - changes string to int
 * @str: target_str
 * Return: 0 on success, else 1
 */
int string_to_int(char *str)
{
	int i, is_positive = 1, flag, output;
	unsigned int result = 0;

	for (i = 0; str[i] != '\0' && flag != 2; i++)
	{
		if (str[i] == '-')
			is_positive *= -1;
		if (str[i] >= '0' && str[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (str[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}
	if (sign == -1)
		output = -result;
	else
		output = result;
	return (output);
}
/**
 * is_interactive - checks shell interactive mode
 * @info: struct address
 * Return: 1 if true else 0
 */
int is_interactive(shell_info *info)
{
	int mode;

	mode = (isatty(STDIN_FILENO) && info->read_file_D <= 2);
	return (mode);
}

/**
 * is_delimiter - checks for delimiters
 * @c: target char
 * @delimiter: target string
 * Return: 1 if true else 0
 */
int is_delimiter(char c, char *delimiter)
{
	while (*delimiter)
		if (*delimiter++ == c)
			return (1);
	return (0);
}

/**
 * is_alpha - checks for alphabet
 * @a: target char
 * Return: 1 if true else 0
 */
int is_alpha(int a)
{
	if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z'))
		return (1);
	else
		return (0);
}
