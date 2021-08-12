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
	char interactive = TRUE, running = TRUE;
	cmd_t *cmds = NULL;

	if (ac > 1)
	{
		/* Run in non-interactive mode */
		interactive = FALSE;
	}

	(void)av;
	(void)envp;
	(void)CMD_HISTORY;
	ENVP = envp;
	(void)ENVP;
	SHELL_PROC_ID = getpid();
	(void)SHELL_PROC_ID;
	signal(SIGINT, handle_signal);
	/* while (envp[i] != NULL)
	{
		printf("%s\n", envp[i]);
		i++;
	} */
	write(STDOUT_FILENO, PS1, 4);
	get_cmd_line();

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
