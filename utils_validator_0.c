#include "main.h"

/**
 * is_digit - Checks if the given character is a digit character
 * @c: The character to check
 *
 * Return: 1 or 0
 */
char is_digit(char c)
{
	return (c >= '0' && c <= '9' ? TRUE : FALSE);
}

/**
 * is_whitespace - Checks if the given character is a whitespace character
 * @c: The character to check
 *
 * Return: 1 or 0
 */
char is_whitespace(char c)
{
	return ((c == ' ' || c == '\t' || c == '\r') ? TRUE : FALSE);
}

/**
 * is_operator - Checks if the given character is an operator character
 * @c: The character to check
 *
 * Return: 1 or 0
 */
char is_operator(char c)
{
	return ((c == ';' || c == '|' || c == '&') ? TRUE : FALSE);
}

/**
 * is_letter - Checks if the given character is a letter
 * @c: The character to check
 *
 * Return: 1 or 0
 */
char is_letter(char c)
{
	return (((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) ? TRUE : FALSE);
}

char is_built_in_cmd(char *cmd)
{
	int i;
	char *built_in_cmds[] = {
		"alias",
		"cd",
		"env",
		"exit",
		"help",
		"history",
		"setenv",
		"unsetenv",
		NULL
	};

	for (i = 0; *(built_in_cmds + i) != NULL; i++)
		if (str_cmp(*(built_in_cmds + i), cmd) == 0)
			return (TRUE);

	return (FALSE);
}

