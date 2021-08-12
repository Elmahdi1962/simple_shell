#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "main.h"

/**
 * The modifiable environment variable for the simple shell
 */
static char **ENVP __attribute__((unused));
static int ENVP_COUNT  __attribute__((unused));
static int SHELL_PROC_ID;
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
static char **CMD_HISTORY __attribute__((unused));
static int CMD_HISTORY_COUNT  __attribute__((unused));

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
	char interactive = TRUE, running = TRUE;
	cmd_t *cmds = NULL, *cur = NULL;

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
		write(STDOUT_FILENO, PS1, 4);
		cmds = parse_cmd_line(get_cmd_line(), TRUE);
		cur = cmds;
		while (cur != NULL)
		{
			printf("cmd: %s ac: %d\n", cur->command, cur->args_count);
			for (i = 0; i < cur->args_count; i++)
			{
				printf("    arg[%d]: %s \n", i, *(cur->args + i));
			}
			cur = cur->next;
		}
		free_list(cmds);
	}

	(void)av;
	(void)cur;
	(void)envp;
	ENVP = envp;
	(void)ENVP;
	(void)running;
	SHELL_PROC_ID = getpid();
	(void)SHELL_PROC_ID;
	signal(SIGINT, handle_signal);
	/* while (envp[i] != NULL)
	{
		printf("%s\n", envp[i]);
		i++;
	} */

	return (0);
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
	case 0:
		return (&ENVP);
	default:
		break;
	}
	return (NULL);
}
