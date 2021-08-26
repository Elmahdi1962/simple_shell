#include "main.h"

/* The modifiable environment variable for this shell program */
static char **Envp;
/* The number of environment variable in this shell program */
static int Envp_Count;
/* The current line number in this shell program */
static int Line_Num;
/* The name of the current instance of this shell program */
static char *Exec_Name;
/* The process ID of the current instance of this shell program */
static int Shell_PID;
/* The exit code of the last executed process in this shell program */
static uchar_t Node_Exit_Code;
/* Specifies the interactiveness of this shell program */
static char Is_Interactive;
/* The lines of the file passed to this shell program */
static char **File_Lines;
/* The number of lines in the file passed to this shell program */
static int Cmd_Lines_Count;
/* The current line of command to be executed */
static char *Cmd_Line;
/* The current list of command nodes to be executed */
static cmd_t *Cmd_List;

/**
 * main - Entry point to the simple shell program
 * @ac: The number of arguments passed
 * @av: The arguments passed
 * @envp: The environment variables that were passed
 *
 * Return: The exit code of the last command executed
 */
int main(int ac, char *av[], char *envp[])
{
	int a = 0;

	init_shell(ac, av, envp);
	while (a < Cmd_Lines_Count)
	{
		print_prompt();
		Cmd_Line = (Is_Interactive == TRUE ? get_cmd_line() : File_Lines[a]);
		add_to_history(Cmd_Line);
		Line_Num++;
		Cmd_List = parse_cmd_line(Cmd_Line);
		execute_cmds_list(&Cmd_List, &Node_Exit_Code);
		if (Cmd_List != NULL)
			free_cmd_t(&Cmd_List);
		if ((Is_Interactive == TRUE) && (Cmd_Line != NULL))
		{
			free(Cmd_Line);
			Cmd_Line = NULL;
		}
		a += (Is_Interactive ? 0 : 1);
	}
	clean_up_shell();
	return (Node_Exit_Code);
}

/**
 * init_shell - Initializes the simple shell program
 * @ac: The number of arguments passed
 * @av: The arguments passed
 * @envp: The environment variables that were passed
 */
void init_shell(int ac, char *av[], char *envp[])
{
	int fd, i;

	Is_Interactive = ((ac < 2) && isatty(STDIN_FILENO) ? TRUE : FALSE);
	if (check_args(ac, av))
	{
		fd = open(av[1], O_RDONLY);
		File_Lines = read_all_lines(fd, &Cmd_Lines_Count);
		if ((fd >= 0))
			close(fd);
	}
	else
	{
		Cmd_Lines_Count = 1;
		File_Lines = NULL;
		if (!isatty(STDIN_FILENO))
			File_Lines = read_all_lines(STDIN_FILENO, &Cmd_Lines_Count);
	}
	for (i = 0; (envp != NULL) && (envp[i] != NULL); i++)
	{
		Envp = _realloc(Envp, sizeof(void *) * i, sizeof(void *) * (i + 1));
		*(Envp + i) = str_copy(envp[i]);
		Envp_Count++;
	}
	Line_Num = 0;
	Exec_Name = str_copy(av[0]);
	Shell_PID = getpid();
	signal(SIGINT, handle_signal);
	Node_Exit_Code = 0;
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
		return (&Envp);
	case ENVP_COUNT_ID:
		return (&Envp_Count);
	case LINE_NUMBER_ID:
		return (&Line_Num);
	case EXEC_NAME_ID:
		return (&Exec_Name);
	case SHELL_PID_ID:
		return (&Shell_PID);
	case NODE_EXIT_CODE_ID:
		return (&Node_Exit_Code);
	case IS_INTERACTIVE_ID:
		return (&Is_Interactive);
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
	if ((File_Lines == NULL) && (Cmd_Line != NULL))
		free(Cmd_Line);
	if (Cmd_List != NULL)
		free_cmd_t(&Cmd_List);
	if (File_Lines != NULL)
		free_array(File_Lines, Cmd_Lines_Count);
	if (Envp != NULL)
		free_array(Envp, Envp_Count);
	if (Exec_Name != NULL)
		free(Exec_Name);
}
