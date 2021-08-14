#ifndef MAIN_H
#define MAIN_H

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif
#ifndef NULL
#define NULL ((void *)0)
#endif
#define MAX_INT_STR "2147483647"
#define SIG_SHELL_ERROR 1738


/**
 * SHELL_PROP_IDS - Consists of the shell's property ids
 */
enum SHELL_PROP_IDS
{
	/* The id for the shell's environment variables */
	ENVP_ID = 0,
	ENVP_COUNT_ID = 1,
	CMD_HISTORY_ID = 4,
	CMD_HISTORY_COUNT_ID = 5,
	EXEC_NAME_ID = 6
};

/**
 * Operators - The operator codes for this shell program.
 */
enum Operators
{
	/**
	 * The operator code for a logical AND character (&&)
	 */
	AND_OP = 1,
	/**
	 * The operator code for a logical OR character (||)
	 */
	OR_OP = 2,
	/**
	 * The operator code for a command separator character (;)
	 */
	SEP_OP = 3
};

enum Token_Types
{
	TKN_BEG = 0,
	TKN_WORD = 1,
	TKN_SPACE = 2,
	TKN_OP = 3
};


/**
 * command_node - Represent a command and its arguments.
 * @command: The name of the command
 * @args_count: The number of arguments provided
 * @args: The arguments provided
 * @next_cond: The condition for executing the next command
 * @next: The next command that can be executed
 */
struct command_node
{
	char *command;
	int args_count;
	char **args;
	char next_cond;
	struct command_node *next;
};

struct built_in_cmd
{
	char *cmd_name;
	int (*run)(int, char**);
};

struct alias_s
{
	char *name;
	char *cmds;
};

struct cmd_help
{
	char *cmd_name;
	void (*run)(void);
};

typedef struct command_node cmd_t;
typedef struct alias_s alias_t;

/* ******** Program (rash.c) ******** */

void handle_signal(int sig_num);
char can_cancel_input();
void *get_shell_prop(char prop_id);
/* ******** ---------------- ******** */

/* ******** Environment Variable Helpers (env_var_helpers.c) ******** */

char *get_env_var(char *str);
void set_env_var(char *var, char*val);
void add_env_var(char *var, char*val);
void remove_env_var(char *var);
/* ******** ---------------- ******** */

/* ******** CLI Helpers (cli_helpers_#.c) ******** */

char *get_cmd_line();

cmd_t *parse_cmd_line(char *line);
char *read_word(char *line, int *pos);
void read_operator(char *line, int *pos, char prev_token,
	cmd_t **head, cmd_t **node, char **error);
/* ******** ---------------- ******** */

/* ******** IO Helpers (io_helpers_#.c) ******** */

char get_char(int fd, char action);
char *read_line(int fd, char action);
char **read_all_lines(char *file_name, int *lines);
/* ******** ---------------- ******** */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/* ******** Built-In Commands (shell_cmds_#.c) ******** */

int exec_built_in_cmd(cmd_t *node);
int sc_alias(int ac, char *av[]);
int sc_cd(int ac, char *av[]);
int sc_env(int ac, char *av[]);
int sc_exit(int ac, char *av[]);
int sc_help(int ac, char *av[]);
int sc_history(int ac, char *av[]);
int sc_setenv(int ac, char *av[]);
int sc_unsetenv(int ac, char *av[]);
/* ******** ---------------- ******** */

/* ******** Built-In Commands Help (shell_cmds_help_#.c) ******** */

void help_program(void);
void help_alias(void);
void help_cd(void);
void help_env(void);
void help_exit(void);
void help_help(void);
void help_history(void);
void help_setenv(void);
void help_unsetenv(void);
/* ******** ---------------- ******** */

/* ******** String Utilities (utils_str_#.c) ******** */

int str_to_int(char *num);
void mem_set(char *str, int n, char c);
char *trim_start(char *str, char c, char can_free);
char *trim_end(char *str, char c, char can_free);
int str_len(char *str);
int str_cmp(char *left, char *right);
char *str_copy(char *str);
char *str_cat(char *left, char *right, char can_free);
char **str_split(char *str, char c, int *len, char can_free);
char *str_replace(char *str, char *sub_str, char *rep_str, char can_free);
/* ******** ---------------- ******** */

/* ******** Validator Utilities (utils_validator_#.c) ******** */

char is_digit(char c);
char is_whitespace(char c);
char is_letter(char c);
char is_operator(char c);
char is_quote(char c);
char is_built_in_cmd(char *cmd);
char str_is_num(char *str);
/* ******** ---------------- ******** */

/* ******** Validator Utilities (utils_validator_#.c) ******** */

cmd_t *new_cmd_node();
void free_list(cmd_t *head);
void add_node_to_end(cmd_t **head, cmd_t **node);
/* ******** ---------------- ******** */

#endif
