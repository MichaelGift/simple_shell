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

/**
 * struct shell_information - contains information about the shell as a while
 * @read_file_d: The file descriptor to read line input
 */
typedef struct shell_information
{
	int read_file_d
} shell_info;


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
/* lists */
str_ll *add_head_node(str_ll **, const char *, int);
str_ll *add_tail_node(str_ll **, const char *, int);
size_t print_list_str(const str_ll *);
int delete_node_at_index(stl_ll **, unsigned int);
void free_list(str_ll **);

/* errors */
void puts_error(char *);
int put_char_to_stderr(char);

/* environment */
int add_envs_to_llist(shell_info *info);

/* alloc */
char *const_mem_set(char *, char, unsigned int);

/* list */
int str_len(char *);
int str_cmp(char *, char *);
char *starts_with(const char *, const char *);
char *str_cat(char *, char *);
char *str_cpy(char *, char *);
char *str_dup(const char *);
void _puts(char *);
int _putchar(char);
#endif
