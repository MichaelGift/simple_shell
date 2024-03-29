#include "shell.h"
/**
 * dup_chars - duplicate characters
 * @pathstr: this is the PATH string
 * @start: starting index
 * @stop: stopping index
 *
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
	buf[k] = 0;
	return (buf);
}

/**
 * is_command - this determines if a file is an executable command
 * @info: the info struct
 * @path: the path to the file
 * Return: 1 if true, 0 otherwise
 */
int is_command(shell_info *info, char *path)
{
	struct stat st;
	(void)info;

	if (!path || stat(path, &st))
		return (0);
	if (st.st_mode & S_IFREG)
		return (1);
	return (0);
}

/**
 * find_cmd_path - it will find the cmd in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 * Return: full path of cmd if found or NULL.
 */
char *find_cmd_path(shell_info *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((str_len(cmd) > 2) && if_starts_with_str(cmd, "./"))
	{
		if (is_command(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_chars(pathstr, curr_pos, i);
			if (!*path)
				str_cat(path, cmd);
			else
			{
				str_cat(path, "/");
				str_cat(path, cmd);
			}
			if (is_command(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}

