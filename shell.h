#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define FLUSH_BUFFER -1

#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND	2
#define CMD_CHAIN 3

#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE ".shell_history"
#define HIST_MAX 4096


#define INITIALIZE \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 * struct string_llist - singly linked list
 * @num: the number
 * @str: the str
 * @next: next node
 */
typedef struct string_llist
{
	int num;
	char *str;
	struct string_llist *next;
} str_ll;

/**
 * struct shell_information - contains information about the shell as a while
 * @read_file_d: The file descriptor to read line input
 * @arg: will be a string generated from getline containing arguements
 * @argv: contains an array of strings generated from arg
 * @path: this is a string path for the current command
 * @argc: this contains the argument count
 */
typedef struct shell_information
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	str_ll *env;
	str_ll *history;
	str_ll *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int read_file_d;
	int histcount;
} shell_info;

/**/
typedef struct builtin_commands
{
	char *command;
	int (*function)(shell_info *);
} builtin_comms;

/* Lists */
str_ll *add_head_node(str_ll **, const char *, int);
str_ll *add_tail_node(str_ll **, const char *, int);
str_ll *node_starts_with(str_ll *, char *, char);
char **llist_to_strarr(str_ll *);
size_t print_str_llist(const str_ll *);
size_t list_str_ll_len(const str_ll *);
size_t print_llist(const str_ll *);
ssize_t get_node_index(str_ll *, str_ll *);
int delete_node_at_index(str_ll **, unsigned int);
void free_list(str_ll **);

/* Shell info*/
void initialize_shell_info(shell_info *);
void set_shell_info(shell_info *, char **);
void free_shell_info(shell_info *, int);

/* Errors */
void puts_error(char *);
int puts_file_d(char *, int);
int put_file_d(char , int);
int put_char_to_stderr(char);
void replace_comments(char *);
void output_error(shell_info *, char *);
int error_sti(char *);
int print_decimal(int, int);
char *number_converter(long int, int, int);

/* Environment */
char *get_env(shell_info *, const char *);
char **get_shell_environ(shell_info *);
int add_envs_to_llist(shell_info *);
int set_env(shell_info *, char *, char *);
int set_my_env(shell_info *);
int unset_env(shell_info *, char *);
int unset_my_env(shell_info *);

/* Parser */
char *find_cmd_path(shell_info *, char *, char *);
int is_command(shell_info *, char *);

/* String to int*/
int is_interactive(shell_info *);
int is_delimiter(char, char *);

/* Get line*/
ssize_t get_input_command(shell_info *);
int get_line_input(shell_info *, char **, size_t *);
void sigint_handler(int);

/* Exits */
char *strn_cpy(char *, char *, int);
char *strn_cat(char *, char *, int);

/* Alloc */
char *const_mem_set(char *, char, unsigned int);
void free_field(char **);
void *custom_realloc(void *, unsigned int, unsigned int);

/* List */
int str_len(char *);
int str_cmp(char *, char *);
char *if_starts_with_str(const char *, const char *);
char *str_cat(char *, char *);
char *str_cpy(char *, char *);
char *str_dup(const char *);
char *str_chr(char *, char);
void custom_puts(char *);
int custom_putchar(char);

/* Tokenize*/
char **str_tow(char *, char *);

/* History*/
int write_shell_history_to_file(shell_info *);
int read_history_from_file(shell_info *);
char *get_history_file_path(shell_info *);
int add_history_entry(shell_info *, char *, int);
int renumber_history_entries(shell_info *);

/* Main shell loop*/
int main_shell_loop(shell_info *, char **);
int find_and_execute_builtin(shell_info *);
void find_and_execute_cmd(shell_info *);
void fork_command(shell_info *);

/* Vars */
void check_cmd_chain(shell_info *, char *, size_t *, size_t, size_t);
int is_chain_delimiter(shell_info *, char *, size_t *);
int sub_str(char **, char *);
int alias_replace(shell_info *);
int substitute_vars(shell_info *);

/* Builtin */
int custom_exit(shell_info *);
int custom_help(shell_info *);
int command_history(shell_info *);
int custom_cd(shell_info *);
int custom_alias(shell_info *);
int alias_print(str_ll *);
int alias_set(shell_info *, char *);
int alias_unset(shell_info *, char *);

/* Environ */
int custom_env(shell_info *);

/* Memory */
int free_buffer(void **);
#endif
