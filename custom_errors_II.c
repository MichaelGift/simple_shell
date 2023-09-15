#include "shell.h"

/**
 * number_converter - itoa clone
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *number_converter(long int num, int base, int flags)
{
	static char *array, buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	while (n != 0)
	{
		*--ptr = array[n % base];
		n /= base;
	}
	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * replace_comments - replace '#' with '\0'
 * @buffer: string address
 *
 * Return: 0
 */
void replace_comments(char *buffer)
{
	int i;

	for (i = 0; buffer[i] != '\0'; i++)
	{
		if (buffer[i] == '#' && (!i || buffer[i - 1] == ' '))
		{
			buffer[i] = '\0';
			break;
		}
	}
}
/**
 * error_sti - string to int
 * @str: target string
 * Return: 0 on success else 1
 */
int error_sti(char *str)
{
	int i = 0;
	unsigned long int result = 0;

	if (*str == '+')
		str++;
	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			result *= 10;
			result += (str[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * output_error - prints error messages
 * @info: struct address
 * @e_str_t: error type
 * Return: 0 on success -1 on error
 */
void output_error(shell_info *info, char *e_str_t)
{
	puts_error(info->fname);
	puts_error(": ");
	print_decimal(info->line_count, STDERR_FILENO);
	puts_error(": ");
	puts_error(info->argv[0]);
	puts_error(": ");
	puts_error(e_str_t);
}

/**
 * print_decimal - well, prints a decimal
 * @input: input
 * @file_d: File descriptor
 * Return: lenght of input
 */
int print_decimal(int input, int file_d)
{
	int (*__putchar)(char) = custom_putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (file_d == STDERR_FILENO)
		__putchar = put_char_to_stderr;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;

	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}
