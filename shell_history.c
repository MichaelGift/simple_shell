#include "shell.h"
/**
 * write_shell_history_to_file - it creates a file, or appends it to an existing file
 * @info: the parameter struct
 * Return: 1 on success, else -1
 */
int write_shell_history_to_file(shell_info *info)
{
ssize_t fd;
char *filename = get_history_file_path(info);
str_ll *node = NULL;

if (!filename)
return (-1);

fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
free(filename);
if (fd == -1)
return (-1);
for (node = info->history; node; node = node->next)
{
_putsfd(node->str, fd);
_putfd('\n', fd);
}
_putfd(FLUSH_BUFFER, fd);
close(fd);
return (1);
}

/**
 * get_history_file_path - Get the path of the history file
 * @info: Pointer to shell information struct
 *
 * Return: Allocated string containing path to history files
 */
char *get_history_file_path(shell_info *info)
{
	char *path, *home_dir;

	home_dir = get_env(info, "HOME=");
	if (!home_dir)
		return (NULL);
	path = malloc(sizeof(char) * (str_len(home_dir) + str_len(HIST_FILE) + 2));
	if (!path)
		return (NULL);
	path[0] = 0;
	str_cpy(path, home_dir);
	str_cat(path, "/");
	str_cat(path, HIST_FILE);
	return (path);
}

/**
 * read_history_from_file - this reads history from the file
 * @info: Pointer to the shell information struct
 *
 * Return:  Number of successful history entries read else 0
 */
int read_history_from_file(shell_info *info)
{
	struct stat file_stat;
	int i, last = 0, line_count = 0;
	ssize_t file_descriptor, read_len, file_size = 0;
	char *buffer = NULL, *filename = get_history_file_path(info);

	if (!filename)
		return (0);
	file_descriptor = open(filename, O_RDONLY);
	free(filename);
	if (file_descriptor == -1)
		return (0);
	if (!fstat(file_descriptor, &file_stat))
		file_size = file_stat.st_size;
	if (file_size < 2)
		return (0);
	buffer = malloc(sizeof(char) * (fsize + 1));
	if (!buffer)
		return (0);
	read_len = read(file_descriptor, buffer, file_size);
	buffer[file_size] = 0;
	if (read_len <= 0)
		return (free(buffer), 0);
	close(file_descriptor);
	for (i = 0; i < file_size; i++)
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			add_history_entry(info, buffer + last, line_count++);
			last = i + 1;
		}
	if (last != i)
		add_history_entry(info, buffer + last, line_count++);
	free(buffer);
	info->histcount = line_count;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history_entries(info);
	return (info->histcount);
}

/**
 * add_history_entry- Add an entry to the history linked list
 * @info: Pointer to the shell information struct
 * @entry: Entry to add
 * @line_count: The history linecount
 *
 * Return: Always 0
 */
int add_history_entry(shell_info *info, char *entry, int line_count)
{
	str_ll *node = NULL;

	if (info->history)
		node = info->history;

	add_tail_node(&node, entry, line_count);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history_entries - Renumber the history entries after changes
 * @info: Pointer to the shell_information struct
 *
 * Return: the new histcount
 */
int renumber_history_entries(shell_info *info)
{
	str_ll *node = info->history;
	int new_count = 0;

	while (node)
	{
		node->num = new_count++;
		node = node->next;
	}
	return (info->histcount = new_count);
}

