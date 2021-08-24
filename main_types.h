#ifndef _ALX_MAIN_TYPES_H
#define _ALX_MAIN_TYPES_H
/**
 * enum Shell_Prop_Ids - Consists of the shell's property ids
 * @ENVP_ID: The prop id for the shell's environment variables
 * @ENVP_COUNT_ID: The prop id for the shell's environment variables count
 * @EXEC_NAME_ID: The prop id for the shell's given executale file name
 * @SHELL_PID_ID: The prop id for the shell's process identifier
 * @NODE_EXIT_CODE_ID: The prop id for the last executed command's exit code
 * @IS_INTERACTIVE_ID: The prop id for the interactive status of the shell
 */
enum Shell_Prop_Ids
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
 * @OP_NONE: The operator code for no operator
 * @OP_AND: The operator code for a logical AND character
 * @OP_OR: The operator code for a logical OR character
 * @OP_SEP: The operator code for a command separator character
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
 * @TKN_BEG: The beginning of the command line
 * @TKN_WORD: A word in the command line
 * @TKN_SPACE: An open space in the command line
 * @TKN_OP: An open operator in the command line
 * @TKN_SEP_OP: An open separator in the command line
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
 * @MO_INIT: Initialize the resources
 * @MO_FREE: Free the resources
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
 * @EC_SUCCESS: The command executed successfully
 * @EC_GENERAL_ERROR: Catchall for general errors
 * @EC_INVALID_ARGS: Misuse of shell built-ins
 * @EC_CANNOT_EXECUTE: Command invoked cannot execute
 * @EC_COMMAND_NOT_FOUND: Command not found
 * @EC_INVALID_EXIT_ARGS: Invalid argument to exit
 * @EC_FATAL_ERROR_SIGNAL: Fatal error signal "n"
 * @EC_CONTROL_C_TERMINATION: Script terminated by Control-C
 * @EC_EXIT_STATUS_OUT_OF_RANGE: Exit status out of range
 */
enum Exit_Codes
{
	/* The command executed successfully */
	EC_SUCCESS = 0,
	/* Catchall for general errors */
	/* E.g.; Miscellaneous errors, such as "divide by zero" and other */
	/* impermissible operations */
	EC_GENERAL_ERROR = 1,
	/* Misuse of shell built-ins */
	EC_INVALID_ARGS = 2,
	/* Command invoked cannot execute */
	/* Permission problem or command is not an executable */
	EC_CANNOT_EXECUTE = 126,
	/* Command not found */
	/* Possible problem with $PATH or a typo */
	EC_COMMAND_NOT_FOUND = 127,
	/* Invalid argument to exit */
	EC_INVALID_EXIT_ARGS = 128,
	/* Fatal error signal "n" */
	/* Ranges from 128 to 255; 0 <= n <= 127 */
	EC_FATAL_ERROR_SIGNAL = 128,
	/* Script terminated by Control-C */
	EC_CONTROL_C_TERMINATION = 130,
	/* Exit status out of range */
	/* exit takes only integer args in the range 0 - 255 */
	EC_EXIT_STATUS_OUT_OF_RANGE = 255
};

/**
 * struct token - Represents a word or operator on the command line
 * @value: The value of the token
 * @type: The type of the token
 * @next: The next token on the command line
 */
struct token
{
	/* The value of the token */
	char *value;
	/* The type of the token */
	char type;
	/* The next token on the command line */
	struct token *next;
};

/**
 * struct command_node - Represent a command and its arguments.
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
 * struct processing_table - Represents the parameters used in \
 * parsing a list of tokens
 * @tokens_list: The pointer to the list of tokens being processed
 * @cur_token: The current token being processed
 * @cur_cmd_node: The current command node being built
 * @cmds_list_head: The pointer to the head of the commands list being built
 * @error: The error flag that represents a processing error
 * @pos: The current index in the list of tokens being processed
 */
struct processing_table
{
	/* The pointer to the list of tokens being processed */
	struct token **tokens_list;
	/* The current token being processed */
	struct token *cur_token;
	/* The current command node being built */
	struct command_node *cur_cmd_node;
	/* The pointer to the head of the commands list being built */
	struct command_node **cmds_list_head;
	/* The error flag that represents a processing error */
	char error;
	/* The current index in the list of tokens being processed */
	int pos;
};

/**
 * struct built_in_cmd - Represents a built-in command node
 * @cmd_name: The name of the built-in command
 * @run: The handler for the built-in command
 */
struct built_in_cmd
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

typedef unsigned char uchar_t;
typedef struct token token_t;
typedef struct command_node cmd_t;
typedef struct cmd_help cmd_help_t;
typedef struct built_in_cmd built_in_cmd_t;
typedef struct alias alias_t;
typedef struct processing_table proc_tbl_t;
#endif
