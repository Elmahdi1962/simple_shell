#include "main.h"

/**
 * parse_cmd_line - Processes a line of commands into a list of cmd_list_t
 * @line: The line of commands
 *
 * Return: The list of cmd_list_t
 */
cmd_t *parse_cmd_line(char *line)
{
	proc_tbl_t *proc_tbl;
	token_t *tokens = NULL;
	char **alias_expansions = NULL;
	int n = 0;
	cmd_t *cmd_list = NULL;

	tokens = tokenize_command_string(line);
	if (tokens == NULL)
		return (NULL);
	if (*((char *)get_shell_prop(IS_INTERACTIVE_ID)) == TRUE)
		process_alias_expansion(&tokens, alias_expansions, &n, ' ');
	if ((proc_tbl = malloc(sizeof(proc_tbl_t))) && (proc_tbl == NULL))
		return (NULL);
	proc_tbl->error = FALSE;
	proc_tbl->tokens_list = &tokens;
	proc_tbl->cmds_list_head = &cmd_list;
	proc_tbl->cur_cmd_node = NULL;
	proc_tbl->pos = 0;
	proc_tbl->cur_token = tokens;
	write(STDOUT_FILENO, "Parsing starting\n", 17), fflush(stdout);
	while ((proc_tbl->cur_token != NULL) && (proc_tbl->error == FALSE))
	{
		write(STDOUT_FILENO, proc_tbl->cur_token->value, str_len(proc_tbl->cur_token->value));
		write(STDOUT_FILENO, ",\n", 2);
		if ((proc_tbl->cur_token)->type == TKN_SEP_OP)
		{
			process_commands_separator(proc_tbl);
		}
		else if ((proc_tbl->cur_token)->type == TKN_OP)
		{
			process_operator(proc_tbl);
		}
		else if ((proc_tbl->cur_token)->type == TKN_WORD)
		{
			process_word(proc_tbl);
		}
		else
		{
			/* TODO: Remove this else block */
			printf("Invalid tokenization on line %d, value: %s\n", __LINE__, (proc_tbl->cur_token)->value);
		}
		proc_tbl->pos++;
		proc_tbl->cur_token = (proc_tbl->cur_token)->next;
	}
	write(STDOUT_FILENO, "Parsing complete\n", 17);
	free_token_t(tokens);
	if (proc_tbl->error == TRUE)
		free_cmd_t(cmd_list), cmd_list = NULL;
	if (proc_tbl != NULL)
		free(proc_tbl);
	free_array(alias_expansions, n);
	return (cmd_list);
}

/**
 * process_commands_separator - Processes a separator
 * @proc_tbl: The pointer to the processing table
 */
void process_commands_separator(proc_tbl_t *proc_tbl)
{
	char *prog_name = *((char **)get_shell_prop(EXEC_NAME_ID));
	token_t *tmp_tkn = NULL;

	tmp_tkn = get_token_at_index(proc_tbl->pos - 1, proc_tbl->tokens_list);
	if ((tmp_tkn == NULL) || (tmp_tkn->type != TKN_WORD))
	{
		write(STDERR_FILENO, "-", 1);
		write(STDERR_FILENO, prog_name, str_len(prog_name));
		write(STDERR_FILENO, ": syntax error near unexpected token `", 38);
		write(STDERR_FILENO, proc_tbl->cur_token->value,
			str_len(proc_tbl->cur_token->value));
		write(STDERR_FILENO, "'\n", 2);
		proc_tbl->error = TRUE;
	}
	else
	{
		if (proc_tbl->cur_cmd_node != NULL)
			(proc_tbl->cur_cmd_node)->next_cond = OP_SEP;
	}
}

/**
 * process_operator - Processes an separator
 * @proc_tbl: The pointer to the processing table
 */
void process_operator(proc_tbl_t *proc_tbl)
{
	char *prog_name = *((char **)get_shell_prop(EXEC_NAME_ID));
	token_t *tmp_tkn = NULL;

	tmp_tkn = get_token_at_index(proc_tbl->pos - 1, proc_tbl->tokens_list);
	if ((tmp_tkn == NULL) || (tmp_tkn->type != TKN_WORD))
	{
		write(STDERR_FILENO, "-", 1);
		write(STDERR_FILENO, prog_name, str_len(prog_name));
		write(STDERR_FILENO, ": syntax error near unexpected token `", 38);
		write(STDERR_FILENO, proc_tbl->cur_token->value,
			str_len(proc_tbl->cur_token->value));
		write(STDERR_FILENO, "'\n", 2);
	}
	else
	{
		if (proc_tbl->cur_cmd_node != NULL)
		{
			if (str_eql(proc_tbl->cur_token->value, "&&"))
				(proc_tbl->cur_cmd_node)->next_cond = OP_AND;
			else if (str_eql(proc_tbl->cur_token->value, "||"))
				(proc_tbl->cur_cmd_node)->next_cond = OP_OR;
		}
	}
}

/**
 * process_word - Processes a word
 * @proc_tbl: The pointer to the processing table
 */
void process_word(proc_tbl_t *proc_tbl)
{
	cmd_t *node = NULL;
	token_t *tmp_tkn = NULL;

	tmp_tkn = get_token_at_index(proc_tbl->pos - 1, proc_tbl->tokens_list);
	if ((tmp_tkn == NULL) || (tmp_tkn->type != TKN_WORD))
	{
		/* create node to be added as a command */
		node = new_cmd_node();
		if (node != NULL)
		{
			node->command = str_copy(proc_tbl->cur_token->value);
			add_node_to_end(proc_tbl->cmds_list_head, &node);
			proc_tbl->cur_cmd_node = node;
		}
	}
	else
	{
		/* add argument to current command */
		if (proc_tbl->cur_cmd_node != NULL)
		{
			(proc_tbl->cur_cmd_node)->args = _realloc(
				(proc_tbl->cur_cmd_node)->args,
				sizeof(void *) * ((proc_tbl->cur_cmd_node)->args_count),
				sizeof(void *) * ((proc_tbl->cur_cmd_node)->args_count + 1)
				);
			*((proc_tbl->cur_cmd_node)->args
				+ (proc_tbl->cur_cmd_node)->args_count) = str_copy(
					proc_tbl->cur_token->value);
			(proc_tbl->cur_cmd_node)->args_count++;
		}
	}
}
