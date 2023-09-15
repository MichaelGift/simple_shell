#include "shell.h"

/**
 * input_buffer - buffers multi-commands
 * @info: struct address
 * @buffer: buffer address
 * @length: len var address
 * Return: bytes read
 */
ssize_t input_buffer(shell_info *info, char **buffer, size_t *length)
{
	ssize_t bytes_read = 0;
	size_t len_p = 0;

	if (!*length)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, sigint_handler);
#if USE_GETLINE
		bytes_read = getline(buffer, &len_p, stdin);
#else
		bytes_read = get_line_input(info, buffer, &len_p);
#endif
		if (bytes_read > 0)
		{
			if ((*buffer)[bytes_read - 1] == '\n')
			{
				(*buffer)[bytes_read - 1] = '\0';
				bytes_read--;
			}
			info->linecount_flag = 1;
			replace_comments(*buffer);
			add_history_entry(info, *buffer, info->histcount++);
			*length = bytes_read;
			info->cmd_buf = buffer;
		}
	}
	return (bytes_read);
}

/**
 * get_input_command - get line minus \n
 * @info: Pointer to the shell_information struct
 * Return: bytes read
 */
ssize_t get_input_command(shell_info *info)
{
	static char *buffer;
	static size_t i, j, length;
	ssize_t bytes_read = 0;
	char **buffer_ptr = &(info->arg), *ptr;

	custom_putchar(FLUSH_BUFFER);
	bytes_read = input_buffer(info, &buffer, &length);

	if (bytes_read == -1)
		return (-1);
	if (length)
	{
		j = i;
		ptr = buffer + i;

		check_cmd_chain(info, buffer, &j, i, length);
		while (j < length)
		{
			if (is_chain_delimiter(info, buffer, &j))
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
	return (bytes_read);
}


/**
 * read_input_buffer - Reads input into a buffer
 * @info: Pointer to shell information struct
 * @buffer: Pointer to the buffer address
 * @size: Pointer to buffer size
 * Return: Bytes_read
 */
ssize_t read_input_buffer(shell_info *info, char *buffer, size_t *size)
{
	ssize_t bytes_read = 0;

	if (*size)
		return (0);
	bytes_read = read(info->read_file_d, buffer, READ_BUFFER_SIZE);
	if (bytes_read >= 0)
		*size = bytes_read;
	return (bytes_read);
}


/**
 * get_line_input - Get line input from stdin
 * @info: Pointer to shell information struct
 * @buffer_ptr: Pointer to a buffer pointer
 * @length: Pointer to size of the buffer
 * Return: Bytes read
 */
int get_line_input(shell_info *info, char **buffer_ptr, size_t *length)
{
	static char buffer[READ_BUFFER_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t bytes_read = 0, total_bytes = 0;
	char *ptr = NULL, *new_ptr = NULL, *c;

	ptr = *buffer_ptr;
	if (ptr && length)
		total_bytes = *length;
	if (i == len)
		i = len = 0;
	bytes_read = read_input_buffer(info, buffer, &len);
	if (bytes_read == -1 || (bytes_read == 0 && len == 0))
		return (-1);
	c = str_chr(buffer + 1, '\n');
	k = c ? 1 + (unsigned int)(c - buffer) : len;
	new_ptr = custom_realloc
		(ptr, total_bytes, total_bytes ? total_bytes + k : k + 1);
	if (!new_ptr)
		return (ptr ? free(ptr), -1 : 1);

	if (total_bytes)
		strn_cat(new_ptr, buffer + i, k - 1);
	else
		strn_cpy(new_ptr, buffer + i, k - i + 1);

	total_bytes += k - i;
	i = k;
	ptr = new_ptr;

	if (length)
		*length = total_bytes;
	*buffer_ptr = ptr;
	return (total_bytes);
}

/**
 * sigint_handler - block interupt
 * @signal_num: signal number
 */
void sigint_handler(__attribute__((unused))int signal_num)
{
	custom_puts("\n");
	custom_puts("$ ");
	custom_putchar(FLUSH_BUFFER);
}

