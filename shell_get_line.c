#include "shell.h"

/**
 * input_buffer - buffers multi-commands
 * @info: struct address
 * @buffer: buffer address
 * @length: len var address
 * Return: bytres
 */
ssize_t input_buffer(shell_info *info, char **buffer, size_t *length)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(buffer);
		*buffer = NULL;
		signal(SIGINT, sigint_handler);
#if USE_GETLINE
		r = getlint(buffer, &len_p, stdin);
#else
		r = get_line(info, buffer, &len_p);
#endif
		if (r > 0)
		{
			if ((*buffer)[r - 1] == '\n')
			{
				(*buffer)[r - 1] = '\0';
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buffer, info->histcount++);
			{
				*length = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * get_input_command - get line minus \n
 * @info: struct address
 * Return: bytes read
 */
ssize_t get_input_command(shell_info *info)
{
	static char *buffer;
	static size_t i, j, length;
	ssize_t r = 0;
	char **buffer_ptr = &(info->arg), *ptr;

	_putchar(BUF_FLASH);
	r = input_buffer(info, &buffer, &len);
	if (r == -1)
		return (-1);
	if (length)
	{
		j = i;
		ptr = buffer + i;

		check_input_chain(info, buffer, &j, i, length);
		while (j < len)
		{
			if (is_chain_input(info, buffer, &j))
				break;
			j++;
		}
		i = j + 1;
		if (i >= length)
		{
			i = length = 0;
			info->cmd_buf_type = CMD_NORM;
		}
		*buffer_ptr = ptr;
		return (str_len(ptr));
	}
	*buffer_ptr = buffer;
	return (r);
}


/**
 * read_buffer - reads a buffer
 * @info: struct address
 * @buffer: buffer address
 * @size: size
 * Return: r
 */
ssize_t read_buffer(shell_info *info, char *buffer, size_t *size)
{
	ssize_t r = 0;

	if (*size)
		return (0);
	r = read(info->read_file_D, buffer, READ_BUF_SIZE);
	if (r >= 0)
		*size = r;
	return (r);
}


/**
 * get_line - get line input from stdin
 * @info: struct address
 * @buffer_ptr: address to a pointer
 * @length: size of ptr
 * Return: s
 */
int get_line(shell_info *info, char *buffer_ptr, size_t *length)
{
	static char buffer[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *ptr = NULL, *new_ptr = NULL, *c;

	ptr = *buffer_ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;
	r = read_buffer(info, buffer, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);
	c = str_chr(buffer + 1, '\n');
	k = c ? 1 + (unsigned int)(c - buffer) : len;
	new_ptr = _realloc(ptr, s, s ? s + k : k + 1);
	if (!new_ptr)
		return (ptr ? free(ptr), -1 : 1);

	if (s)
		strn_cat(new_ptr, buffer + i, k - 1);
	else
		strn_cpy(new_ptr, buffer + i, k - i + 1);

	s += k - i;
	i = k;
	ptr = new_ptr;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigint_handler - block interupt
 * @signal_num: signal number
 */
void sigint_handler(__attribut__((unused))int signal_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

