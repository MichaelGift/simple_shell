#include "shell.h"

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
