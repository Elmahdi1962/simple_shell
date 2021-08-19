#ifndef _ALX_MAIN_H
#define _ALX_MAIN_H

#include <dirent.h>
#include <elf.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
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
#ifndef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif
#ifndef MAX
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif
/* The maximum value of an exit code */
#define MAX_EXIT_CODE 256
/* The file name used to store this shell's history */
#define HISTORY_FILE "/.simple_shell_history"
/* The string representation of INT32_MAX */
#define MAX_INT_STR "2147483647"
#define SIG_SHELL_ERROR 1738

/**
 * enum SHELL_PROP_IDS - Consists of the shell's property ids
 */
enum SHELL_PROP_IDS
{
	/* The prop id for the shell's environment variables */
	ENVP_ID = 0,
	/* The prop id for the shell's environment variables count */
	ENVP_COUNT_ID = 1,
	/* The prop id for the shell's given executale file name */
	EXEC_NAME_ID = 6,
	/* The prop id for the shell's process identifier */
	SHELL_PID_ID = 7,
	/* The prop id for the last executed command's exit code */
	NODE_EXIT_CODE_ID = 8,
	/* The prop id for the interactive status of the shell */
	IS_INTERACTIVE_ID
};

/**
 * enum Operator_Types - The operator codes for this shell program.
 */
enum Operator_Types
{
	/* The operator code for no operator */
	OP_NONE = 0,
	/* The operator code for a logical AND character (&&) */
	OP_AND = 1,
	/* The operator code for a logical OR character (||) */
	OP_OR = 2,
	/* The operator code for a command separator character (;) */
	OP_SEP = 3
};

/**
 * enum Token_Types - Types of tokens in a command line
 */
enum Token_Types
{
	/* The beginning of the command line */
	TKN_BEG = 0,
	/* A word in the command line */
	TKN_WORD = 1,
	/* An open (not enclosed in quotes) space in the command line */
	TKN_SPACE = 2,
	/* An open (not enclosed in quotes) operator in the command line */
	TKN_OP = 3,
	/* An open (not enclosed in quotes) separator in the command line */
	TKN_SEP_OP = 4
};

/**
 * enum Management_Operations - Operation codes for managing some resources
 */
enum Management_Operations
{
	/* Initialize the resources */
	MO_INIT = 0,
	/* Free the resources */
	MO_FREE = 1
};

/**
 * enum Exit_Codes - Exit codes for this shell program
 */
enum Exit_Codes
{
	/* The command executed successfully */
	EC_SUCCESS = 0,
	/**
	 * Catchall for general errors \
	 * (E.g.; Miscellaneous errors, such as "divide by zero" and other \
	 * impermissible operations)
	 */
	EC_GENERAL_ERROR = 1,
	/* Misuse of shell built-ins */
	EC_INVALID_ARGS = 2,
	/**
	 * Command invoked cannot execute \
	 * (Permission problem or command is not an executable)
	 */
	EC_CANNOT_EXECUTE = 126,
	/**
	 * Command not found \
	 * (Possible problem with $PATH or a typo)
	 */
	EC_COMMAND_NOT_FOUND = 127,
	/* Invalid argument to exit */
	EC_INVALID_EXIT_ARGS = 128,
	/**
	 * Fatal error signal "n" \
	 * (Ranges from 128 to 255; 0 <= n <= 127)
	 */
	EC_FATAL_ERROR_SIGNAL = 128,
	/* Script terminated by Control-C */
	EC_CONTROL_C_TERMINATION = 130,
	/**
	 * Exit status out of range \
	 * (exit takes only integer args in the range 0 - 255)
	 */
	EC_EXIT_STATUS_OUT_OF_RANGE = 255
};

struct token
{
	char *value;
	char type;
	struct token *next;
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
	/* The name of the command */
	char *command;
	/* The number of arguments provided */
	int args_count;
	/* The arguments provided */
	char **args;
	/* The condition for executing the next command */
	char next_cond;
	/* The next command that can be executed */
	struct command_node *next;
};

/**
 * struct commands_list - Represents a list of commands
 */
struct commands_list
{
	struct command_node *cmds;
	struct commands_list *next;
};

struct processing_table
{
	struct token **tokens_list;
	struct token *cur_token;
	struct command_node *cur_cmd_node;
	struct command_node **cmds_list_head;
	char error;
	int pos;
};

/**
 * struct built_in_cmd_s - Represents a built-in command node
 * @cmd_name: The name of the built-in command
 * @run: The handler for the built-in command
 */
struct built_in_cmd_s
{
	/* The name of the built-in command */
	char *cmd_name;
	/* The handler for the built-in command */
	int (*run)(int, char**);
};

/**
 * struct alias - Represents an alias command
 * @name: The name of the alias
 * @value: The value of the alias
 */
struct alias
{
	/* The name of the alias */
	char *name;
	/* The value of the alias */
	char *value;
};

/**
 * struct cmd_help - Represents this shell's help pages
 * @cmd_name: The name of the built-in command
 * @run: The handler for the built-in command's help
 */
struct cmd_help
{
	/* The name of the built-in command */
	char *cmd_name;
	/* The handler for the built-in command's help */
	void (*run)(void);
};

typedef struct token token_t;
typedef struct command_node cmd_t;
typedef struct alias alias_t;
typedef struct commands_list cmd_list_t;
typedef struct processing_table proc_tbl_t;

/* ******** Program (rash.c) ******** */

void init_shell(int ac, char *av[], char *envp[],
	int *cmd_lines_count, char ***file_lines);
void print_node(cmd_t *node);
void handle_signal(int sig_num);
void *get_shell_prop(char prop_id);
void clean_up_shell(void);
/* ******** ---------------- ******** */

/* ******** Alias Manager (alias_manager.c) ******** */

void manage_aliases(char op);
void add_alias(char *name, char *value);
char *get_alias_value(char *str);
alias_t **get_aliases(int *len);
void remove_alias(char *str);
/* ******** ---------------- ******** */

/* ******** History Manager (history_manager.c) ******** */

void manage_history(int op);
void add_to_history(char *str);
void save_history();
char **get_history(int *size);
int get_line_num();
/* ******** ---------------- ******** */

/* ******** Environment Variable Helpers (env_var_helpers.c) ******** */

char *get_env_var(char *str);
void set_env_var(char *var, char*val);
void add_env_var(char *var, char*val);
void remove_env_var(char *var);
/* ******** ---------------- ******** */

/* ******** CLI Helpers (cli_helpers_#.c) ******** */

/* void init_line_reader(); */
char *get_cmd_line();
void check_chars(char *quote, char *quote_o, char current_char);
void set_error(char *error, char quote_o, int n, char *str, int pos);
void print_prompt();

cmd_t *get_next_command(cmd_t *cur, int exit_code);
char **get_variables(char *str, int *vars_count);
/* ******** ---------------- ******** */

/* ******** CLI Parser (cli_parser.c) ******** */

cmd_t *parse_cmd_line(char *line);
void process_commands_separator(proc_tbl_t *proc_tbl);
void process_operator(proc_tbl_t *proc_tbl);
void process_word(proc_tbl_t *proc_tbl);
void insert_word(char **str, char **word, cmd_t **node, int *pos);

char *read_variable(char *str, int pos);

token_t *tokenize_command_string(char *str);
void skip_comment(char *str, int o, int *len_out);
char *read_operator(char *str, int o, int *len_out, char *error);
char *read_word(char *str, int o, int *len_out);

char *dissolve_tokens(char *str, char can_free);
void dissolve_cmd_parts(cmd_t *node);
char is_valid_prev_char(char c);
token_t *get_token_tail(token_t **head);
void process_alias_expansion(token_t **tokens, char **expansions, int *n, char prev_char);
/* TODO: Move declaration below to right position */
char str_in_list(char **arr, int n, char *str);
/* ******** ---------------- ******** */

/* ******** Cmd_t Helpers (cmd_t_helpers.c) ******** */

cmd_t *new_cmd_node();
void free_cmd_t(cmd_t *head);
void add_node_to_end(cmd_t **head, cmd_t **node);
cmd_t *get_cmd_t_tail(cmd_t *head);

void add_cmd_list_to_end(cmd_list_t **head, cmd_list_t *cmd_lst);
void add_cmd_t_to_cmd_list_t_end(cmd_list_t *head, cmd_t *node);
void free_cmd_list_t(cmd_list_t *head);
cmd_list_t *get_cmd_list_t_tail(cmd_list_t *head);
cmd_t *get_tail_cmd(cmd_list_t *head);

void add_token_to_end(token_t **head, token_t *tkn);
token_t *create_token(char *value, char type);
void free_token_t(token_t *head);
token_t *get_token_at_index(int idx, token_t **head);
/* ******** ---------------- ******** */

/* ******** IO Helpers (io_helpers_#.c) ******** */

/* char *read_line(int fd, char action); */
char **read_all_lines(int fd, int *lines);
void print_text(int fd, char *text[], int n);
/* ******** ---------------- ******** */

/* ******** Memory Helpers (mem_helpers.c) ******** */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void free_array(char **list, int length);
/* ******** ---------------- ******** */

/* ******** Executors (executor.c) ******** */

void execute_cmds_list(cmd_t **cmds_list, int *exit_code);
int exec_built_in_cmd(cmd_t *node);
int exec_program(cmd_t *node, char *program_path);
char **copy_environment(char **env, int env_count);
char **copy_arguments(cmd_t *node);
/* ******** ---------------- ******** */

/* ******** Built-In Commands (shell_cmds_#.c) ******** */

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
int str_eql(char *left, char *right);
char *str_copy(char *str);
char *str_cat(char *left, char *right, char can_free);
char *copy_range(char *str, int a, int b);
char **str_split(char *str, char c, int *len_out, char can_free);
char *str_replace(char *str, char *sub_str, char *rep_str, char can_free);
char *long_to_str(long num);
char *rep_range(char *str, char *val, int a, int b);
void print_error(char *command_name, char *userinput, char *error_message);
void swap(char *x, char *y);
char *reverse(char *buffer, int i, int j);
char *_itoa(int value, char* buffer, int base);
/* ******** ---------------- ******** */

/* ******** Validator Utilities (utils_validator_#.c) ******** */

char is_digit(char c);
char is_whitespace(char c);
char is_letter(char c);
char is_quote(char c);
char is_built_in_cmd(cmd_t *cmd);
char str_is_num(char *str);
char is_binary_file(char *fn);
char is_variable(char *str);
char is_exec_file(char *fn);
char is_alias(char *str);
char is_alias_name(char *str);
char is_alias_assignment(char *str, char **name_out, char **value_out);
int is_regular_file(const char *path);
char is_binary_file(char *fn);
char is_normal_program(cmd_t *node, char **path_out);
/* ******** ---------------- ******** */

/* ******** DATA Validator (data_validators_#.c) ******** */

char *check_path(char *str);
char *search_path(char *command);
/* ******** ---------------- ******** */
#endif
