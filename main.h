#ifndef MAIN_H
#define MAIN_H

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

/**
 * SHELL_PROP_IDS - Consists of the shell's property ids
 */
enum SHELL_PROP_IDS
{
	/* The id for the shell's environment variables */
	ENVP_ID = 0,
	ENVP_COUNT_ID = 1,
	CMD_HISTORY = 4,
	CMD_HISTORY_COUNT_ID = 5
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

typedef struct command_node cmd_t;

/* ******** Program (rash.c) ******** */

void *get_shell_prop(char prop_id);
/* ******** ---------------- ******** */

/* ******** CLI Helpers (cli_helpers_#.c) ******** */

char *get_cmd_line();
void handle_signal(int sig_num);
char *get_env_var(char *str);
/* ******** ---------------- ******** */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/* ******** Built-In Commands (shell_cmds_#.c) ******** */

int sc_env(int ac, char *av[]);
int sc_exit(int ac, char *av[]);
/* ******** ---------------- ******** */

/* ******** Math Utilities (utils_math_#.c) ******** */

int str_to_int(char *num);
/* ******** ---------------- ******** */

/* ******** String Utilities (utils_str_#.c) ******** */

void mem_set(char *str, int n, char c);
char *trim_start(char *str, char c, char can_free);
char *trim_end(char *str, char c, char can_free);
int str_len(char *str);
int str_cmp(char *left, char *right);
/* ******** ---------------- ******** */

/* ******** Validator Utilities (utils_validator_#.c) ******** */

char is_digit(char c);
char is_whitespace(char c);
char is_letter(char c);
char is_operator(char c);
char is_built_in_cmd(char *cmd);
/* ******** ---------------- ******** */

#endif
