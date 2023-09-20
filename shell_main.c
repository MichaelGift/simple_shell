#include "shell.h"
/**
 * main - the entry point
 * @arg_c: argument vector
 * @arg_v: argument count
 * Return: 0 on success, 1 on error
 */

int main(int arg_c, char **arg_v)
{
	shell_info info[] = { INITIALIZE };
	int file_d = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (file_d)
			: "r" (file_d));
	if (arg_c == 2)
	{
		file_d = open(arg_v[1], O_RDONLY);
		if (file_d == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				puts_error(arg_v[0]);
				puts_error(": 0: Can't open ");
				puts_error(arg_v[1]);
				put_char_to_stderr('\n');
				put_char_to_stderr(FLUSH_BUFFER);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->read_file_d = file_d;
	}
	add_envs_to_llist(info);
	read_history_from_file(info);
	main_shell_loop(info, arg_v);
	return (EXIT_SUCCESS);
}

