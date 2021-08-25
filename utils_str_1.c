#include "main.h"

/**
 * str_eql - Checks if the left string is equal to the right string
 * @left: The string on the left side
 * @right: The string on the right side
 *
 * Return: TRUE if they're equal and not NULL, otherwise FALSE
 */
char str_eql(char *left, char *right)
{
	int i;

	if ((left == NULL) || (right == NULL))
	{
		return (FALSE);
	}
	else
	{
		for (i = 0; *(left + i) != '\0'; i++)
		{
			if (*(right + i) == '\0')
				return (FALSE);
			if (*(left + i) != *(right + i))
				break;
		}
		if ((*(left + i) == '\0') && (*(right + i) == '\0'))
			return (TRUE);
		else
			return (FALSE);
	}
}

/**
 * str_copy - Makes a copy of a string
 * @str: The string to copy
 *
 * Return: The copied string, otherwise NULL
 */
char *str_copy(const char *str)
{
	char *new_str = NULL;
	int i;
	int len = str_len(str);

	if (str == NULL)
		return (NULL);
	new_str = malloc(sizeof(char) * (len + 1));
	if (new_str != NULL)
	{
		for (i = 0; i < len; i++)
			*(new_str + i) = *(str + i);
		*(new_str + i) = '\0';
	}
	return (new_str);
}

/**
 * str_cat - Concatenates two strings
 * @left: The left string
 * @right: The right string
 * @can_free: Specifies if the given strings can be freed
 *
 * Return: A pointer to the concatenated string
 */
char *str_cat(char *left, char *right, char can_free)
{
	int left_length = str_len(left);
	int right_length = str_len(right);
	int i;
	char *str = NULL;

	str = malloc(sizeof(char) * (left_length + right_length + 1));
	if (str != NULL)
	{
		for (i = 0; left != NULL && *(left + i) != '\0'; i++)
			*(str + i) = *(left + i);
		for (i = 0; right != NULL && *(right + i) != '\0'; i++)
			*(str + left_length + i) = *(right + i);
		*(str + left_length + i) = '\0';
	}
	if (can_free)
	{
		if (left != NULL)
			free(left);
		if (right != NULL)
			free(right);
	}
	return (str);
}

/**
 * copy_range - Copies a range of chracters from a to b inclusive
 * @str: The string to copy from
 * @a: The start index
 * @b: The end index
 *
 * Return: A newly created string, otherwise NULL
 */
char *copy_range(char *str, int a, int b)
{
	int i;
	int start = MIN(a, b);
	int end = MAX(a, b);
	char *res = NULL;

	res = malloc(sizeof(char) * (end - start + 2));
	if (res != NULL)
	{
		for (i = 0; i < (end - start + 1); i++)
			*(res + i) = *(str + start + i);
		*(res + i) = '\0';
	}
	return (res);
}

/**
 * str_split - Splits a string into smaller strings at a given character
 * @str: The string to split
 * @c: The character at which to perform the split
 * @len_out: The pointer which would contain the number of smaller strings
 * @can_free: Specifies if the string can be freed
 *
 * Return: A pointer to the first string in the array of strings
*/
char **str_split(char *str, char c, int *len_out, char can_free)
{
	int i = 0, j = 0, o = 0, s = 0, n = 0;
	char **strs = NULL;

	if (str == NULL)
		return (NULL);
	for (i = 0; *(str + i) != '\0'; i++)
	{
		if (((*(str + i) == c))
			|| ((*(str + i) != c) && (*(str + i + 1) == '\0')))
		{
			strs = _realloc(strs, sizeof(void *) * n, sizeof(void *) * (n + 1));
			if (strs != NULL)
			{
				s = *(str + i) == c ? i - j : i - j + 1;
				*(strs + n) = malloc(sizeof(char) * (s + 1));
				if (*(strs + n) != NULL)
				{
					for (o = 0; o < s; o++)
						*(*(strs + n) + o) = *(str + j + o);
					*(*(strs + n) + o) = '\0';
					j = i + 1;
					n++;
				}
			}
		}
	}
	if (len_out != NULL)
		*len_out = n;
	if (can_free)
		free(str);
	return (strs);
}
