#include "shell.h"
/**
 * main - the entry point
 * @arg_c: arg vector
 * @arg_v: arg count
 * Return: 0 on success, 1 on error
 */

int main(int arg_c, char **arg_v)
{
	shell_info info[] = { INFO_INIT };
	int file_d = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (file_d)
			: "r" (file_d));
	if (arg_c == 2)
	{
		fd = open(arg_v[1], O_RDONLY);
		if (file_d == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				puts_error(arg_v[0]);
				puts_error(": 0: Cannot open ");
				puts_error(arg_v[1]);
				put_char_to_stderr('\n');
				put_char_to_stderr(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->read_file_d = file_d;
	}
	add_envs_to_llist(info);
	read_history(info);
	main_shell_loop(info, arg_v);
	return (EXIT_SUCCESS);
}

