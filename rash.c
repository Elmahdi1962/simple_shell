#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "main.h"

/**
 * The modifiable environment variable for the simple shell
 */
static char **ENVP;
static int ENVP_COUNT;
static int SHELL_PROC_ID;
static char error_set;
const int width_size = 0xff;
/**
 * The prompt displayed by the shell
 */
const char PS1[] = "($) ";
/**
 * The path containing the previous commands that were run
 */
const char HISTORY_PATH[] = "~/.simple_shell_history";
/**
 * The previous commands run by the program
 */
static char **CMD_HISTORY;
static int CMD_HISTORY_COUNT;

/**
 * main - Entry point to the simple shell
 * @ac: The number of arguments passed
 * @av: The arguments passed
 *
 * Return: 0 if successful
 */
int main(int ac, char *av[], char *envp[])
{
	int i = 0;
	char interactive = TRUE;
	int cmd_lines_count = 0;
	char **cmd_lines = NULL;
	char *cmd_line = NULL;
	cmd_t *cmds = NULL, *cur = NULL;

	ENVP = envp;
	for (ENVP_COUNT = 0; ENVP[ENVP_COUNT] != NULL; ENVP_COUNT++)
		;
	SHELL_PROC_ID = getpid();
	signal(SIGINT, handle_signal);
	/* signal(SIG_SHELL_ERROR, handle_signal); */
	/* add_env_var("PS1", "($) ");
	add_env_var("SHELL", av[0]); */
	if (ac > 1)
	{
		/* Run in non-interactive mode */
		interactive = FALSE;
	}

	if (!interactive)
	{
		/*  */
	}
	else
	{
		/* while (1)
		{ */
			write(STDOUT_FILENO, PS1, 4);
			cmd_line = get_cmd_line();
			if (str_len(cmd_line) > 0)
			{
				CMD_HISTORY = _realloc(CMD_HISTORY, sizeof(void *) * CMD_HISTORY_COUNT,
					sizeof(void *) * (CMD_HISTORY_COUNT + 1));
				*(CMD_HISTORY + CMD_HISTORY_COUNT) = str_copy(cmd_line);
				CMD_HISTORY_COUNT++;
				cmds = parse_cmd_line(cmd_line);
				cur = cmds;
				while (cur != NULL)
				{
					printf("cmd: %s, built-in: %d, ac: %d\n", cur->command,
						is_built_in_cmd(cur->command), cur->args_count);
					for (i = 0; i < cur->args_count; i++)
					{
						printf("    arg[%d]: %s \n", i, *(cur->args + i));
					}
					cur = cur->next;
				}
				free_list(cmds);
			}
			free(cmd_line);
		/* } */
		printf("---\n");
	}

	(void)av;
	(void)cmd_lines;
	(void)cmd_lines_count;
	(void)SHELL_PROC_ID;
	return (0);
}

/**
 * handle_signal - Handles a signal received by the program
 * @sig_num: The signal's code
 */
void handle_signal(int sig_num)
{
	if (sig_num == SIG_SHELL_ERROR)
	{
		error_set = TRUE;
	}
	else if (sig_num == SIGINT)
	{
		write(STDIN_FILENO, "\r", 1);
		write(STDIN_FILENO, "\n", 1);
		fflush(STDIN_FILENO);
		/* write(STDIN_FILENO, "\x07", 1); */
	}
}

/**
 * get_shell_prop - Retrieved the adddress of a shell prop based on an id
 * @prop_id: The id of the prop to retrieve
 *
 * Return: The pointer to the prop, otherwise NULL
 */
void *get_shell_prop(char prop_id)
{
	switch (prop_id)
	{
	case ENVP_ID:
		return (&ENVP);
	case ENVP_COUNT_ID:
		return (&ENVP_COUNT);
	case CMD_HISTORY_ID:
		return (&CMD_HISTORY);
	case CMD_HISTORY_COUNT_ID:
		return (&CMD_HISTORY_COUNT);
	default:
		break;
	}
	return (NULL);
}
