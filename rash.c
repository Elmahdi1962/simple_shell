#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "main.h"

/**
 * TODO: Processing an executable file
 */

/**
 * The modifiable environment variable for this shell program
 */
static char **ENVP;
/**
 * The number of environment variable in this shell program
 */
static int ENVP_COUNT;
/**
 * The name of the current instance of this shell program
 */
static char *EXEC_NAME;
/**
 * The process ID of the current instance of this shell program
 */
static char *SHELL_PID;
static char *ERROR_MSG;
/* static char error_set; */
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
 * The current line number of the shell program
 */
static int LINE_NUM;
/**
 * The exit code of the last executed process in this shell program
 */
static int NODE_EXIT_CODE;

/**
 * main - Entry point to the simple shell program
 * @ac: The number of arguments passed
 * @av: The arguments passed
 *
 * Return: 0 if successful
 */
int main(int ac, char *av[], char *envp[])
{
	int i = 0, a = 0, cmd_lines_count = 1;
	char interactive, **file_lines = NULL;
	char *cmd_line = NULL, *ps1;
	cmd_t *cmds = NULL, *cur = NULL;

	ENVP = envp;
	for (ENVP_COUNT = 0; ENVP[ENVP_COUNT] != NULL; ENVP_COUNT++)
		;
	EXEC_NAME = av[0];
	SHELL_PID = long_to_str(getpid());
	signal(SIGINT, handle_signal);
	signal(SIG_SHELL_ERROR, handle_signal);
	add_env_var("SHELL", av[0]);
	/* printf("%d, %s, %d\n", ac, av[0], isatty(STDIN_FILENO)); */
	if (ac > 1)
	{
		/* TODO: Load first arg as a file */
		exit(127);
	}
	interactive = !isatty(STDIN_FILENO) || (ac == 2) ? FALSE : TRUE;
	/* write(STDOUT_FILENO, "\033[2J", 4); */
	/* write(STDOUT_FILENO, "\033[H", 3); */

	while (a < cmd_lines_count)
	{
		if (interactive)
		{
			ps1 = get_env_var("PS1");
			write(STDOUT_FILENO, ps1, str_len(ps1));
		}
		cmd_line = file_lines == NULL ? get_cmd_line() : *(file_lines + a);
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
		a += (!interactive ? 1 : 0);
	}
	/* printf("---\n"); */
	return (0);
}

/**
 * handle_signal - Handles a signal received by the program
 * @sig_num: The signal's code
 */
void handle_signal(int sig_num)
{
	char *buf;

	if (sig_num == SIG_SHELL_ERROR)
	{
		buf = long_to_str(LINE_NUM);
		write(STDERR_FILENO, EXEC_NAME, str_len(EXEC_NAME));
		write(STDERR_FILENO, ": ", 2);
		if (buf != NULL)
			write(STDERR_FILENO, buf, str_len(buf));
		write(STDERR_FILENO, ": ", 2);
		if (ERROR_MSG != NULL)
			write(STDERR_FILENO, ERROR_MSG, str_len(ERROR_MSG));
		write(STDERR_FILENO, "\n", 1);
		/* error_set = TRUE; */
		if (buf != NULL)
			free(buf);
		if (ERROR_MSG != NULL)
			free(ERROR_MSG);
		ERROR_MSG = NULL;
	}
	else if (sig_num == SIGINT)
	{
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
	case EXEC_NAME_ID:
		return (&EXEC_NAME);
	case SHELL_PID_ID:
		return (&SHELL_PID);
	case NODE_EXIT_CODE_ID:
		return (&NODE_EXIT_CODE);
	default:
		break;
	}
	return (NULL);
}
