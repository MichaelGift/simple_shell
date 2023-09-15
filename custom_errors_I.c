#include "shell.h"


/**
 * put_file_d - writes the file descriptor
 * @c: char to print
 * @file_d: descriptor
 * Return: 1 on success else -1
 */
int put_file_d(char c, int file_d)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(file_d, buf, i);
		i = 0;
	}
	if (c  != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * puts_file_d - print input strin
 * @str: target string
 * @file_d: file desciptor to write to
 * Return: number of chars
 */
int puts_file_d(char *str, int file_d)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
		i += put_file_d(*str++, file_d);
	return (i);
}
/**
 * puts_error - prints input str
 * @str: target string
 * Return: NULL
 */
void puts_error(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		putchar_error(str[i]);
		i++;
	}
}

/**
 * put_char_to_stderr - outputs a character to stderr
 * @c: The char to write
 * Return: 1 on success else 0
 */
int put_char_to_stderr(char c)
{
	static int buffer_index;
	static char error_buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || buffer_index >= WRITE_BUF_SIZE)
	{
		write(2, error_buffer, buffer_index);
		buffer_index = 0;
	}
	if (c != BUF_FLUSH)
		error_buffer[buffer_index++] = c;
	return (1);

}

