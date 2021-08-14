#include <stdlib.h>
#include "main.h"

/**
 * str_to_int - Converts a string to an int
 * @num: The string to convert
 *
 * Return: The converted number
 */
int str_to_int(char *num)
{
	int i = 1, len, exp = 1;
	int res = 0;

	len = str_len(num);
	for (i = len - 1; i >= 0; i--)
	{
		if (*(num + i) == '-')
			res *= -1;
		else if (is_digit(*(num + i)))
		{
			res += (*(num + i) - '0') * exp;
			exp *= 10;
		}
	}
	return (res);
}

/**
 * str_len - Computes the length of a string
 * @str: The source string
 *
 * Return: The length of the string.
 */
int str_len(char *str)
{
	int len = 0;

	while (str != NULL && *(str + len) != '\0')
		len++;
	return (len);
}

/**
 * mem_set - Fills a section of a string with a given character
 * \ (starts from position 0)
 * @str: The string containing the section to be filled
 * @n: The length of the section to fill
 * @c: The character to fill the section with
 */
void mem_set(char *str, int n, char c)
{
	int i;

	for (i = 0; str != NULL && i < n; i++)
		*(str + i) = c;
}

/**
 * trim_start - Makes a trimmed copy of a string
 * @str: The string whose beginning is to be trimmed
 * @c: The character to strip from the beginning of the string
 * @can_free: Specifies if the given string can be freed
 *
 * Return: The trimmed copy, otherwise NULL
 */
char *trim_start(char *str, char c, char can_free)
{
	int i, j, len;
	char *new_str;

	for (i = 0; *(str + i) != '\0' && *(str + i) == c; i++)
		;
	len = str_len(str) - i;
	new_str = malloc(sizeof(char) * (len + 1));
	if (new_str)
	{
		for (j = 0; *(str + i) != '\0'; i++)
		{
			*(new_str + j) = *(str + i);
			j++;
		}
		*(new_str + j) = '\0';
		if (can_free)
			free(str);
	}
	return (new_str);
}

/**
 * trim_end - Makes a trimmed copy of a string
 * @str: The string whose ending is to be trimmed
 * @c: The character to strip from the end of the string
 * @can_free: Specifies if the given string can be freed
 *
 * Return: The trimmed copy, otherwise NULL
 */
char *trim_end(char *str, char c, char can_free)
{
	char *new_str;
	int len = str_len(str);
	int i, j;

	for (i = len - 1; i >= 0 && *(str + i) == c; i--)
		;
	new_str = malloc(sizeof(char) * (len + 1));
	if (new_str)
	{
		for (j = 0; j <= i; j++)
			*(new_str + j) = *(str + j);
		*(new_str + j) = '\0';
		if (can_free)
			free(str);
	}
	return (new_str);
}

/**
 * str_cmp - Makes a comparison between two strings
 * @left: The string on the left side
 * @right: The string on the right side
 *
 * Return: -1 if the left is < than right, 1 if left is > right and othrwise 0
*/
int str_cmp(char *left, char *right)
{
	int i;

	if (left == NULL && right != NULL)
		return (-1);
	if (left != NULL && right == NULL)
		return (1);
	if (left == NULL && right == NULL)
	{
		return (0);
	}
	else
	{
		for (i = 0; *(left + i) != '\0' && *(right + i) != '\0'; i++)
		{
			if (*(left + i) == '\0' && *(right + i) != '\0')
				return (-1);
			if (*(left + i) != '\0' && *(right + i) == '\0')
				return (1);
			if (*(left + i) > *(right + i))
				return (1);
			if (*(left + i) < *(right + i))
				return (-1);
		}
		return (0);
	}
}

/**
 * str_copy - Makes a copy of a string
 * @str: The string to copy
 *
 * Return: The copied string, otherwise NULL
 */
char *str_copy(char *str)
{
	char *new_str;
	int i;
	int len = str_len(str);

	new_str = malloc(sizeof(char) * (len + 1));
	if (new_str)
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
		free(left);
		free(right);
	}
	return (str);
}

/**
 * str_split - Splits a string into smaller strings at a given character
 * @str: The string to split
 * @c: The character at which to perform the split
 * @len: The pointer which would contain the number of smaller strings
 * @can_free: Specifies if the string can be freed
 *
 * Return: A pointer to the first string in the array of strings
*/
char **str_split(char *str, char c, int *len, char can_free)
{
	int i, j = 0, k, n = 0;
	char **strs = NULL;

	for (i = 0; ; i++)
	{
		if (*(str + i) == '\0')
		{
			if ((i > 0) && (*(str + i - 1) != c))
			{
				strs = _realloc(strs, sizeof(void *) * n, sizeof(void *) * (n + 1));
				*(strs + n) = strs != NULL ? malloc(sizeof(char) * (i - j + 1)) : NULL;
				if (*(strs + n) != NULL)
				{
					k = 0;
					for (; j < i; j++)
					{
						*(*(strs + n) + k) = *(str + j);
						k++;
					}
					*(*(strs + n) + k) = '\0';
					n++;
				}
			}
			break;
		}
		else if (*(str + i) == c)
		{
			if (i == 0)
				continue;
			strs = _realloc(strs, sizeof(void *) * n, sizeof(void *) * (n + 1));
			*(strs + n) = strs != NULL ? malloc(sizeof(char) * (i - j + 1)) : NULL;
			if (*(strs + n) != NULL)
			{
				k = 0;
				for (; j < i; j++)
				{
					*(*(strs + n) + k) = *(str + j);
					k++;
				}
				*(*(strs + n) + k) = '\0';
				j = i + 1;
				n++;
			}
		}
	}
	if (len != NULL)
		*len = n;
	if (can_free)
		free(str);
	return (strs);
}

/**
 * str_replace - Replaces a string with a given string in another string
 * @str: The source string
 * @sub_str: The string to look for in the source string
 * @rep_str: The string to use as a replacement
 * @can_free: Specifies whether the given strings can be freed
 *
 * Return: The string containing the replaced values, otherwise, NULL
*/
char *str_replace(char *str, char *sub_str, char *rep_str, char can_free)
{
	char *res = str != NULL ? str_copy(str) : NULL, *tmp;
	int rep_len = str_len(rep_str);
	int sub_len = str_len(sub_str);
	int res_len = str_len(str);
	int i = 0, j = 0, a, b, c;

	if (res != NULL && sub_str != NULL && rep_str != NULL)
	{
		while (res != NULL && *(res + i) != '\0')
		{
			if (*(res + i) == *sub_str)
			{
				for (j = 0; (*(sub_str + j) != '\0') && (*(res + i) != '\0'); j++, i++)
				{
					if (*(sub_str + j) != *(res + i))
						break;
				}
				i -= j;
				if (j == sub_len)
				{
					/* make replacement */
					res_len = res_len + (rep_len == sub_len ? 0 :  rep_len - sub_len);
					tmp = malloc(sizeof(char) * (res_len + 1));
					if (tmp != NULL)
					{
						for (a = 0, b = 0, c = 0; a < res_len; a++)
						{
							c =  (a == i) ? i + sub_len : c;
							if (a >= i && a < (i + rep_len))
							{
								*(tmp + a) = *(rep_str + b);
								b++;
							}
							else
							{
								*(tmp + a) = *(res + c);
								c++;
							}
						}
						*(tmp + a) = '\0';
					}
					free(res);
					res = tmp;
					i += (rep_len == sub_len ? rep_len :  rep_len - sub_len);
				}
			}
			i++;
		}
	}
	if (can_free)
	{
		free(str);
		free(sub_str);
		free(rep_str);
	}
	return (res);
}

