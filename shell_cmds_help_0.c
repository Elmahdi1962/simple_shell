#include "main.h"

/**
 * help_program - Prints the help text of the shell rash
 */
void help_program(void)
{
	char *help_text[] =
	{
		""
	};

	print_text(STDOUT_FILENO, help_text, 1);
}

/**
 * help_alias - Prints the help text of the alias built-in command
 */
void help_alias(void)
{
	char *help_text[] =
	{
		"alias: alias [name[=value] ... ]\n",
		"    Define or display aliases.\n\n",
		"    Without arguments, `alias' prints the list of ",
		"aliases in the reusable\n",
		"    form `alias NAME=VALUE' on standard output.\n\n",
		"    Otherwise, an alias is defined for each NAME whose ",
		"VALUE is given.\n",
		"    A trailing space in VALUE causes the next word to ",
		"be checked for\n",
		"    alias substitution when the alias is expanded.\n\n",
		"    Exit Status:",
		"    alias returns true unless a NAME is supplied for ",
		"which no alias has been\n",
		"    defined.\n",
	};

	print_text(STDOUT_FILENO, help_text, 14);
}

/**
 * help_cd - Prints the help text of the cd built-in command
 */
void help_cd(void)
{
	char *help_text[] =
	{
		"cd: cd [-|DIR]\n",
		"    Change the shell working directory.\n\n",
		"    Change the current directory to DIR.  The default DIR ",
		"is the value of the\n",
		"    HOME shell variable.\n\n",
		"    Exit Status:\n",
		"    Returns 0 if the directory is changed; non-zero otherwise.\n",
	};

	print_text(STDOUT_FILENO, help_text, 7);
}

/**
 * help_env - Prints the help text of the env built-in command
 */
void help_env(void)
{
	char *help_text[] =
	{
		""
	};

	print_text(STDOUT_FILENO, help_text, 1);
}

/**
 * help_exit - Prints the help text of the exit built-in command
 */
void help_exit(void)
{
	char *help_text[] =
	{
		"exit: exit [n]\n",
		"    Exit the shell.\n\n",
		"    Exits the shell with a status of N.  If N is omitted, ",
		"the exit status\n",
		"    is that of the last command executed.\n"
	};

	print_text(STDOUT_FILENO, help_text, 5);
}
