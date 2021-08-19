#include "main.h"

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
					res_len = res_len + (rep_len == sub_len ? 0 : rep_len - sub_len);
					tmp = malloc(sizeof(char) * (res_len + 1));
					if (tmp != NULL)
					{
						for (a = 0, b = 0, c = 0; a < res_len; a++)
						{
							c = (a == i) ? i + sub_len : c;
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
					i += (rep_len == sub_len ? rep_len : rep_len - sub_len);
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

/**
 * long_to_str - Converts a long to its string representation
 * @num: The long integer
 *
 * Return: The string representation of the long integer
 */
char *long_to_str(long num)
{
	char *str;
	long rem = num;
	char sign = rem < 0 ? -1 : 1;
	char size = 20, j;

	str = malloc(sizeof(char) * (size + 1));
	if (str)
	{
		*(str + size) = '\0';
		mem_set(str, size, '0');
		j = size - 1;
		if (rem == 0)
			*(str + j) = '0';

		while ((sign == -1 && rem < 0) || (sign == 1 && rem > 0))
		{
			*(str + j) = (rem % 10) * sign + '0';
			rem /= 10;
			j--;
		}
		if (sign < 0)
			*(str + j) = '-';
		str = trim_start(str, '0', TRUE);
		str = num == 0 ? str_cat("0", "", FALSE) : str;
	}
	return (str);
}

/**
 * rep_range - Replaces a range of characters in a string
 * @str: The source string
 * @val: The value to use as a replacement
 * @a: The starting index
 * @b: The ending index
 *
 * Return: The replaced string, otherwise NULL
 */
char *rep_range(char *str, char *val, int a, int b)
{
	int len = str_len(str), in_len = str_len(val), i = 0, j = 0, k = 0;
	int start = MIN(a, b), end = MAX(a, b), size;
	char *res = NULL;
	int out_len = end - start + 1;

	size = len + (in_len == out_len ? 0 : in_len - out_len);
	res = malloc(sizeof(char) * (size + 1));
	if (res != NULL)
	{
		for (i = 0; i < size;)
		{
			if (i == start)
			{
				for (j = 0; j < in_len; j++)
				{
					*(res + i) = *(val + j);
					i++;
				}
				k = start + out_len;
			}
			else
			{
				*(res + i) = *(str + k);
				k++;
				i++;
			}
		}
		*(res + i) = '\0';
	}
	return (res);
}

/**
 * strs_join - Joins an array of strings into a string
 * @arr: The array of strings
 * @c: The character to join the strings with
 * @can_free: Specifies if the given array can be freed
 *
 * Return: The concatenated strings, otherwise NULL
 */
char *strs_join(char **arr, int n, char c, char can_free)
{
	int size = 0;
	int i, j, k;
	char *res = NULL;

	for (i = 0; i < n; i++)
		size += str_len(*(arr + i));
	size += (c == 0 ? 0 : n - 1);
	res = malloc(sizeof(char) * (size + 1));
	if (res != NULL)
	{
		i = 0;
		for (k = 0; k < n; k++)
		{
			for (j = 0; *(*(arr + k) + j) != '\0'; j++)
			{
				*(res + i) = *(*(arr + k) + j);
				i++;
			}
			if ((c != 0) && (k < n - 1))
			{
				*(res + i) = c;
				i++;
			}
		}
		*(res + i) = '\0';
	}
	if (can_free == TRUE)
		free_array(arr, n);
	return (res);
}

/**
 * print_error - Prints custom error messages
 * @command_name: The command name that will print the error
 * @userinput: The input of the user that made the command print this error
 * @error_message: The error message
 */
void print_error(char *command_name, char *userinput, char *error_message)
{
	char *shell_name = "simple_shell: ";
	char line_number[5];
	int number_len;

	_itoa(get_line_num(), line_number, 10);
	number_len = str_len(line_number);

	write(STDOUT_FILENO, shell_name, 14);
	write(STDOUT_FILENO, line_number, number_len);
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, command_name, str_len(command_name));
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, error_message, str_len(error_message));
	write(STDOUT_FILENO, userinput, str_len(userinput));
	write(STDOUT_FILENO, "\n", 1);
}

/**
 * _itoa - Convert int to string
 * @value: Number to convert int
 * @buffer: Pointer to a buffer where to store the result
 * @base: Base to convert the integer into
 *
 * Return: A pointer to the string holding the result
 */
char *_itoa(int value, char *buffer, int base)
{
	int n, i;

	/* invalid input*/
	if (base < 2 || base > 32)
	{
		return buffer;
	}

	/* consider the absolute value of the number*/
	n = value;

	i = 0;
	while (n)
	{
		int r = n % base;

		if (r >= 10)
		{
			buffer[i++] = 65 + (r - 10);
		}
		else
		{
			buffer[i++] = 48 + r;
		}

		n = n / base;
	}

	/* if the number is 0*/
	if (i == 0)
	{
		buffer[i++] = '0';
	}

	/* If the base is 10 and the value is negative, the resulting string*/
	/* is preceded with a minus sign (-)*/
	/* With any other base, value is always considered unsigned*/
	if (value < 0 && base == 10)
	{
		buffer[i++] = '-';
	}

	buffer[i] = '\0'; /* null terminate string*/

	/* reverse the string and return it*/
	return reverse(buffer, 0, i - 1);
}
