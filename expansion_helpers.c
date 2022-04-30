#include "main.h"

/**
 * read_variable - Reads a variable from the given string
 * @str: The string to read from
 * @pos: The position in the string to start from
 *
 * Return: The variable, otherwise NULL
 */
char *read_variable(char *str, int pos)
{
	int i = pos, j, len;
	char *var = NULL;

	while (*(str + i) != '\0')
	{
		if (is_digit(*(str + i))
			|| is_letter(*(str + i))
			|| (*(str + i) == '_'))
		{
			if (is_digit(*(str + pos)) && !is_digit(*(str + i)))
				break;
			i++;
		}
		else
		{
			i += (i > pos ? 0 : 1);
			break;
		}
	}
	len = i - pos;
	var = len > 0 ? malloc(sizeof(char) * (len + 1)) : NULL;
	if (var != NULL)
	{
		for (j = 0, i = pos; j < len; j++, i++)
			*(var + j) = *(str + i);
		*(var + j) = '\0';
	}
	return (var);
}
