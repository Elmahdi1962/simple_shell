#include "main.h"

/**
 * help_help - Prints the help text of the help built-in command
 */
void help_help(void)
{
	char *help_text[] =
	{
		"help: help [BUILTIN]\n",
		"    Display information about builtin commands.\n",
		"    Displays brief summaries of builtin commands.  If BUILTIN is\n",
		"    specified, gives detailed help on the command named BUILTIN,\n",
		"    otherwise the list of help topics is printed.\n\n",
		"    Arguments:\n",
		"      BUILTIN   Name specifying a help topic\n\n",
		"    Exit Status:\n",
		"    Returns success unless BUILTIN is not found.\n"
	};

	print_text(STDOUT_FILENO, help_text, 9);
}

/**
 * help_history - Prints the help text of the history built-in command
 */
void help_history(void)
{
	char *help_text[] =
	{
		"history: history\n",
		"    Display or manipulate the history list.\n",
		"    Display the history list with line numbers.\n\n",
		"    The file at ~/.simple_shell_history is used as the history file\n\n",
		"    Exit Status:\n",
		"    Returns success unless an invalid option is given or an error occurs.\n"
	};

	print_text(STDOUT_FILENO, help_text, 6);
}

/**
 * help_setenv - Prints the help text of the setenv built-in command
 */
void help_setenv(void)
{
	char *help_text[] =
	{
		"setenv: Defines an environment variable and assigns a value to it\n\n",
		"Syntax:\n",
		"\t setenv <variable-name> <variable-value>\n\n",
		"Required Argument:\n",
   		"\tvariable-name:\n",
		"\tspecifies a UNIX environment variable that you can set.\n\n",
		"Optional Argument:\n",
   		"\tvariable-value:\n",
		"\tspecifies the value of a UNIX environment variable.\n"
	};
	
	print_text(STDOUT_FILENO, help_text, 9);
}

/**
 * help_unsetenv - Prints the help text of the unsetenv built-in command
 */
void help_unsetenv(void)
{
	char *help_text[] =
	{
		"unsetenv : removes an environment variable. The memory for the\n",
		"entry and the environment variable is released\n\n",
		"Syntax:\n",
		"\tunsetenv <variable-name>\n\n",
		"Required Argument:\n",
   		"\tvariable-name:\n",
        "\tspecifies a UNIX environment variable that you want to unset.\n"
	};

	print_text(STDOUT_FILENO, help_text, 7);
}
