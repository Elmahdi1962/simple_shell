#include "main.h"

/**
 * adjust_block - Adjusts a block of memory to allow additional bytes
 * @blk: The pointer to the memory block
 * @new_sz: The new size of the block
 * @old_sz: The pointer to the block's old size
 * @incr: The amount of bytes to increase the block by
 */
void adjust_block(char **blk, size_t new_sz, size_t *old_sz, char incr)
{
	if (blk != NULL)
	{
		if (new_sz >= *old_sz)
		{
			*blk = _realloc(*blk, sizeof(char) * (*old_sz),
				sizeof(char) * (*old_sz + incr));
			(*old_sz) += incr;
		}
	}
}

/**
 * dissolve_tokens - Performs a context-aware dissolution of tokens
 * @str: The source string
 * @can_free: Specifies if the given string can be freed
 *
 * Return: The dissolved string, otherwise NULL
 */
char *dissolve_tokens(char *str, char can_free)
{
	size_t size = 0, i = 0, j = 0;
	char incr = 0x40, *res = NULL, quote = FALSE, quote_o = FALSE;

	for (i = 0; *(str + i) != '\0';)
	{
		adjust_block(&res, j, &size, incr);
		if ((str[i] == '~') && (i == 0))
		{
			expand_tilde(str, &i, &res, &j, &size);
		}
		else if (is_quote(*(str + i)))
		{
			if (quote == FALSE)
				quote = *(str + i), quote_o = TRUE, i++;
			else if ((*(str + i) == quote))
				quote = FALSE, quote_o = FALSE, i++;
			else
				*(res + j) = *(str + i), j++, i++;
		}
		else if (*(str + i) == '$')
		{
			if (is_variable_expandible(str, i, quote, quote_o))
				expand_variable(str, &i, &res, &j, &size);
			else
				*(res + j) = '$', j++, i++;
		}
		else
		{
			*(res + j) = *(str + i), j++, i++;
		}
	}
	res = _realloc(res, sizeof(char) * j, sizeof(char) * (j + 1));
	if (res != NULL)
		*(res + j) = '\0';
	if (can_free && (str != NULL))
		free(str);
	return (res);
}

/**
 * expand_tilde - Expands a tilde at the beginning of a word
 * @str: The string containing the variable
 * @i: The pointer to the current position in the string
 * @res: The pointer to the expandion buffer
 * @j: The pointer to the new buffer's index
 * @size: The pointer to the new buffer's size
 */
void expand_tilde(char *str, size_t *i, char **res, size_t *j, size_t *size)
{
	char *tmp = NULL;
	int tmp_len = 0, k = 0;

	if ((*(str + *i + 1) == '/') || (*(str + *i + 1) == '\0'))
	{
		tmp = str_copy(get_env_var("HOME"));
		tmp_len = str_len(tmp);
	}
	if (tmp != NULL)
	{
		tmp_len += (*(str + *i + 1) == '/' ? 1 : 0);
		if (((*j) + tmp_len) > *size)
		{
			/* allocate space for extra data */
			*res = _realloc(*res, sizeof(char) * (*size),
				sizeof(char) * (*size + ((*j) + tmp_len - (*size))));
			(*size) += ((*j) + tmp_len - (*size));
		}
		for (k = 0; k < tmp_len; k++)
		{
			if ((k == tmp_len - 1) && (*(str + *i + 1) == '/'))
				*(*res + (*j)) = '/';
			else
				*(*res + (*j)) = *(tmp + k);
			(*j)++;
		}
		(*i) += (*(str + *i + 1) == '/' ? 2 : 1);
		free(tmp);
	}
	else
	{
		*(*res + (*j)) = '~';
		(*j)++;
		(*i)++;
	}
}

/**
 * expand_variable - Expands a variable
 * @str: The string containing the variable
 * @i: The pointer to the current position in the string
 * @res: The pointer to the expandion buffer
 * @j: The pointer to the new buffer's index
 * @size: The pointer to the new buffer's size
 */
void expand_variable(char *str, size_t *i, char **res, size_t *j, size_t *size)
{
	char *var = NULL, *val = NULL;
	int var_len = 0, k, val_len = 0;

	var = read_variable(str, *i + 1);
	if (str_eql("?", var))
		val = long_to_str(*((uchar_t *)get_shell_prop(NODE_EXIT_CODE_ID)));
	else if (str_eql("$", var))
		val = long_to_str(*((int *)get_shell_prop(SHELL_PID_ID)));
	else if (var != NULL)
		val = str_copy(get_env_var(var));
	/* insert variable */
	var_len = str_len(var) + 1;
	val_len = str_len(val);
	if ((*j + val_len) > *size)
	{
		/* allocate space for extra data */
		*res = _realloc(*res, sizeof(char) * *size,
			sizeof(char) * (*size + (*j + val_len - *size)));
	}
	for (k = 0; k < val_len; k++)
	{
		*(*res + (*j)) = *(val + k);
		(*j)++;
	}
	(*i) += var_len;
	if (val != NULL)
		free(val);
	val = NULL;
	if (var != NULL)
		free(var), var = NULL;
}

/**
 * dissolve_cmd_parts - Dissolves the parts of the command node
 * @node: The command node
 */
void dissolve_cmd_parts(cmd_t *node)
{
	int i;

	node->command = dissolve_tokens(node->command, TRUE);
	for (i = 0; i < node->args_count; i++)
	{
		*(node->args + i) = dissolve_tokens(*(node->args + i), TRUE);
	}
}
