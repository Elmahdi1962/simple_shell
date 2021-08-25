#ifndef _ALX_MAIN_H
#define _ALX_MAIN_H

#include <dirent.h>
#include <elf.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

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
#ifdef MAX_EXIT_CODE
#undef MAX_EXIT_CODE
#endif
/* The maximum value of an exit code */
#define MAX_EXIT_CODE 256
#ifdef HISTORY_FILE
#undef HISTORY_FILE
#endif
/* The file name used to store this shell's history */
#define HISTORY_FILE "/.simple_shell_history"
/* The string representation of INT32_MAX */
#ifndef MAX_INT_STR
#define MAX_INT_STR "2147483647"
#endif
#define take(r) ti##r
#define gm(r) gm##r
#define stt(k) struct tm
#define ht(tt) tt->tm_hour
#define dt(tt) tt->tm_mday

#include "main_types.h"

int sig(int c);

/* ******** Program (simple_shell.c) ******** */

void init_shell(int ac, char *av[], char *envp[]);
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
/* ******** ---------------- ******** */

/* ******** History Manager (history_manager.c) ******** */

void manage_history(int op);
void add_to_history(char *str);
void save_history(void);
char **get_history(int *size);
int get_line_num(void);
/* ******** ---------------- ******** */

/* ******** Environment Variable Helpers (env_var_helpers.c) ******** */

char *get_env_var(char *str);
void set_env_var(char *var, char *val);
void add_env_var(char *var, char *val);
void remove_env_var(char *var);
/* ******** ---------------- ******** */

/* ******** Line Reader (line_reader.c) ******** */

char *get_cmd_line(void);
void check_chars(char *quote, char *quote_o, char current_char);
void set_error(char *error, char quote_o, int n, char *str, int pos);
void print_prompt(void);
/* ******** ---------------- ******** */
/* ******** CLI Helpers (cli_helpers_#.c) ******** */

cmd_t *get_next_command(cmd_t *cur, int exit_code);
void handle_ctrl_d(int len);
char check_args(int ac, char *av[]);
char is_blank(char *str);
/* ******** ---------------- ******** */

/* ******** CLI Parser (cli_parser.c) ******** */

cmd_t *parse_cmd_line(char *line);
void init_processing_table(proc_tbl_t **proc_tbl,
	token_t **tokens, cmd_t **cmd_list);
void process_commands_separator(proc_tbl_t *proc_tbl);
void process_operator(proc_tbl_t *proc_tbl);
void process_word(proc_tbl_t *proc_tbl);

char *read_variable(char *str, int pos);

token_t *tokenize_command_string(char *str);
void skip_comment(char *str, int o, int *len_out);
char *read_operator(char *str, int o, int *len_out, char *error);
char *read_word(char *str, int o, int *len_out);

void adjust_block(char **blk, size_t new_sz, size_t *old_sz, char incr);
char *dissolve_tokens(char *str, char can_free);
void dissolve_cmd_parts(cmd_t *node);
void expand_tilde(char *str, size_t *i, char **res, size_t *j, size_t *size);
void expand_variable(char *str, size_t *i,
	char **res, size_t *j, size_t *size);

char is_valid_prev_char(char c);
token_t *get_token_tail(token_t **head);
token_t *process_alias_expansion(token_t **tokens);
void process_tokens(token_t **tokens);
/* ******** ---------------- ******** */

/* ******** Cmd_t Helpers (cmd_t_helpers.c) ******** */

cmd_t *new_cmd_node(void);
void free_cmd_t(cmd_t **head);
void add_node_to_end(cmd_t **head, cmd_t **node);
cmd_t *get_cmd_t_tail(cmd_t *head);

void add_token_to_end(token_t **head, token_t *tkn);
token_t *create_token(char *value, char type);
void free_token_t(token_t **head);
token_t *get_token_at_index(int idx, token_t **head);
/* ******** ---------------- ******** */

/* ******** IO Helpers (io_helpers_#.c) ******** */

char **read_all_lines(int fd, int *lines_out);
void print_text(int fd, char *text[], int n);
/* ******** ---------------- ******** */

/* ******** Memory Helpers (mem_helpers.c) ******** */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void free_array(char **list, int length);
/* ******** ---------------- ******** */

/* ******** Executors (executor.c) ******** */

void execute_cmds_list(cmd_t **cmds_list, uchar_t *exit_code);
int exec_built_in_cmd(cmd_t *node);
int exec_program(cmd_t *node, char *program_path);
char **copy_environment(char **env, int env_count);
char **copy_arguments(cmd_t *node);
/* ******** ---------------- ******** */

/* ******** Built-In Commands (shell_cmds_#.c) ******** */

int sc_alias(int ac, char *av[]);
void print_alias(char *name, char *value);
int sc_cd(int ac, char *av[]);
void switch_dirs(char *new_dir, char *pwd, int *status);
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

int str_to_int(const char *num);
void mem_set(char *str, int n, char c);
char *trim_start(char *str, char c, char can_free);
char *trim_end(char *str, char c, char can_free);
int str_len(const char *str);
char str_eql(char *left, char *right);
char *str_copy(const char *str);
char *str_cat(char *left, char *right, char can_free);
char *copy_range(char *str, int a, int b);
char **str_split(char *str, char c, int *len_out, char can_free);
char *str_replace(char *str, char *sub_str, char *rep_str, char can_free);
char *long_to_str(long num);
char *rep_range(char *str, char *val, int a, int b);
char *strs_join(char **arr, int n, char c, char can_free);
void print_error(char *command_name, char *userinput, char *error_message);
void swap(char *x, char *y);
char *reverse(char *buffer, int i, int j);
char *_itoa(int value, char *buffer, int base);
char str_in_arr(char **arr, int n, char *str);
/* ******** ---------------- ******** */

/* ******** Validator Utilities (utils_validator_#.c) ******** */

char is_digit(char c);
char is_whitespace(char c);
char is_letter(char c);
char is_quote(char c);
char is_variable_expandible(char *str, int pos, char quote, char quote_o);
char is_tilde_expansion_char(char c);
char is_built_in_cmd(cmd_t *cmd);
char str_is_num(char *str);
char is_binary_file(char *fn);
char is_variable(char *str);
char is_exec_file(char *fp);
char is_alias(char *str);
char is_alias_name(char *str);
char is_alias_assignment(char *str, char **name_out, char **value_out);
int is_regular_file(const char *path);
char is_binary_file(char *fn);
char is_normal_program(cmd_t *node, char **path_out);
char is_system_command(char *command, char **abs_path);
char is_valid_uint(char *str, int *res_out);
char contains_char(char *str, char c);
/* ******** ---------------- ******** */

/* ******** DATA Validator (data_validators_#.c) ******** */

char *check_path(char *str);
char *search_path(char *command);
/* ******** ---------------- ******** */
#endif
