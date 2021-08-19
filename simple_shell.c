#include "main.h"

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
static int SHELL_PID;
/**
 * The exit code of the last executed process in this shell program
 */
static int NODE_EXIT_CODE;
/**
 * Specifies the interactiveness of this shell program
 */
static char IS_INTERACTIVE;
/**
 * The lines of the file passed to this shell program
 */
char **FILE_LINES;
/**
 * The number of lines in the file passed to this shell program
 */
int CMD_LINES_COUNT;

/**
 * main - Entry point to the simple shell program
 * @ac: The number of arguments passed
 * @av: The arguments passed
 *
 * Return: The exit code of the last command executed
 */
int main(int ac, char *av[], char *envp[])
{
	int a = 0;
	char *cmd_line = NULL;
	cmd_t *cmd_list = NULL;

	init_shell(ac, av, envp);
	write(STDIN_FILENO, "\0", 1);/* Clear any previous input */
	printf(">> pid: %d\n", getpid());
	while (a < CMD_LINES_COUNT)
	{
		print_prompt();
		cmd_line = FILE_LINES == NULL ? get_cmd_line() : FILE_LINES[a];
		if (str_len(cmd_line) > 0)
		{
			add_to_history(cmd_line);
			cmd_list = parse_cmd_line(cmd_line);
			execute_cmds_list(&cmd_list, &NODE_EXIT_CODE);
			free_cmd_t(cmd_list);
			if (cmd_line != NULL)
				free(cmd_line);
		}
		a += (!IS_INTERACTIVE ? 1 : 0);
	}
	return (NODE_EXIT_CODE);
}

/**
 * init_shell - Entry point to the simple shell program
 * @ac: The number of arguments passed
 * @av: The arguments passed
 * @cmd_lines_count: The number of lines of commands strings in a passed file
 * @file_lines: The lines of command strings in a passed file
 * @interactive: The pointer to the interactive variable
 */
void init_shell(int ac, char *av[], char *envp[])
{
	int fd, i;

	if (ac > 2)
	{
		write(STDERR_FILENO, "Usage: ", 7);
		write(STDERR_FILENO, av[0], str_len(av[0]));
		write(STDERR_FILENO, " [file]", 7);
		write(STDERR_FILENO, "\n", 1);
		exit(EC_INVALID_ARGS);
	}
	if (ac == 2)
	{
		/* TODO: Load first arg as a file */
		fd = open(av[1], O_RDONLY);
		FILE_LINES = read_all_lines(fd, &CMD_LINES_COUNT);
	}
	else
	{
		CMD_LINES_COUNT = 1;
		FILE_LINES = NULL;
	}
	for (i = 0; (envp != NULL) && (envp[i] != NULL); i++)
	{
		ENVP = _realloc(ENVP, sizeof(void *) * i, sizeof(void *) * (i + 1));
		*(ENVP + i) = str_copy(envp[i]);
		ENVP_COUNT++;
	}
	EXEC_NAME = str_copy(av[0]);
	SHELL_PID = getpid();
	IS_INTERACTIVE = (!isatty(STDIN_FILENO) || (ac == 2) ? FALSE : TRUE);
	signal(SIGINT, handle_signal);
	add_env_var("SHELL", av[0]);
	NODE_EXIT_CODE = 0;
	manage_aliases(MO_INIT);
	manage_history(MO_INIT);
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
	case EXEC_NAME_ID:
		return (&EXEC_NAME);
	case SHELL_PID_ID:
		return (&SHELL_PID);
	case NODE_EXIT_CODE_ID:
		return (&NODE_EXIT_CODE);
	case IS_INTERACTIVE_ID:
		return (&IS_INTERACTIVE);
	default:
		break;
	}
	return (NULL);
}

/**
 * clean_up_shell - Frees resources used by this shell instance
 */
void clean_up_shell(void)
{
	save_history();
	manage_aliases(MO_FREE);
	manage_history(MO_FREE);
	if (FILE_LINES != NULL)
		free_array(FILE_LINES, CMD_LINES_COUNT);
	if (ENVP != NULL)
		free_array(ENVP, ENVP_COUNT);
	if (EXEC_NAME != NULL)
		free(EXEC_NAME);
}
