#include "main.h"

/**
 * swap - Swaps two digits
 * @x: The first digit
 * @y: The second digit
 */
void swap(char *x, char *y)
{
	char t = *x;

	*x = *y;
	*y = t;
}

/**
 * reverse - Reverses a buffer
 * @buffer: The buffer to reverse
 * @i: The first digit or index
 * @j: The last digit or index
 *
 * Return: The reversed buffer
 */
char *reverse(char *buffer, int i, int j)
{
	while (i < j)
	{
		swap(&buffer[i++], &buffer[j--]);
	}

	return (buffer);
}

/**
 * str_in_arr - Checks if a string is in an array
 * @arr: The array to look through
 * @n: The length of the array
 * @str: The string to search for
 *
 * Return: TRUE if the string is in the array, otherwise FALSE
 */
char str_in_arr(char **arr, int n, char *str)
{
	int i;

	for (i = 0; (arr != NULL) && (i < n); i++)
	{
		if (str_eql(*(arr + i), str))
			return (TRUE);
	}
	return (FALSE);
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
	char *res = str != NULL ? str_copy(str) : NULL;
	int rep_len = str_len(rep_str), sub_len = str_len(sub_str);
	int i = 0, j = 0;

	if ((res != NULL) && (sub_str != NULL) && (rep_str != NULL))
	{
		while ((res != NULL) && (*(res + i) != '\0'))
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
					res = rep_range(res, rep_str, i, i + rep_len);
					i += (rep_len == sub_len ? rep_len : rep_len - sub_len);
				}
			}
			i++;
		}
	}
	if (can_free)
	{
		if (str != NULL)
			free(str);
		if (sub_str != NULL)
			free(sub_str);
		if (rep_str != NULL)
			free(rep_str);
	}
	return (res);
}
