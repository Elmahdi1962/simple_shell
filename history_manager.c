#include "main.h"

/**
 * The path containing the previous commands that were run
 */
const char HISTORY_PATH[] = "~/.simple_shell_history";
/**
 * The maximum size of the history buffer
 */
const short HISTORY_SIZE = 1 << 12;
/**
 * The previous commands run by the shell program
 */
static char **Cmd_History;
/**
 * Specifies if the history buffer is full. If TRUE, command_strings \
 * in the buffer would be replaced by newer commands
 */
static char Is_Full;
/**
 * The current line number of the shell program
 */
static int Line_Num;

void manage_history(int op)
{
	int i, fd;

	if (op == MO_INIT)
	{
		/* Load history file*/
		fd = open(HISTORY_PATH, O_RDONLY | O_CREAT);
		if (fd >= 0)
		{
			close(fd);
		}
	}
	else if (op == MO_FREE)
	{
		save_history();
		for (i = 0; i < (Is_Full ? HISTORY_SIZE : Line_Num); i++)
		{
			if (*(Cmd_History + i) != NULL)
				free(*(Cmd_History + i));
		}
		free(Cmd_History);
	}
}

/**
 * add_to_history - Adds a line to this shell's history
 * @str: The line to add
 */
void add_to_history(char *str)
{
	char new_lines = 0;
	int i;
	int size = Is_Full ? HISTORY_SIZE : Line_Num;

	for (i = 0; *(str + i) != '\0'; i++)
	{
		if (*(str + i) == '\n')
		{
			new_lines++;
			break;
		}
	}
	if (new_lines == 0)
	{
		Cmd_History = _realloc(Cmd_History, sizeof(void *) * size,
			sizeof(void *) * (size + 1));
		*(Cmd_History + Line_Num) = str_copy(str);
		Is_Full = Is_Full ? Is_Full : (Line_Num + 1 == HISTORY_SIZE ? TRUE : FALSE);
		Line_Num = ((Line_Num + 1) % HISTORY_SIZE);
	}
}

/**
 * save_history - Saves this shell's history to the history's file path
 */
void save_history()
{
	int fd, i;

	fd = open(HISTORY_PATH, O_WRONLY | O_TRUNC | O_CREAT);
	if (fd >= 0)
	{
		for (i = 0; i < (Is_Full ? HISTORY_SIZE : Line_Num); i++)
		{
			write(fd, *(Cmd_History + i), str_len(*(Cmd_History + i)));
			write(fd, "\n", 1);
		}
		if (Cmd_History != NULL)
			free(Cmd_History);
		close(fd);
	}
}

/**
 * get_history - Retrieves this shell's past commands
 *
 * Return: A list of stings, otherwise, NULL
 */
char **get_history()
{
	return (Cmd_History);
}

/**
 * get_line_num - Retrieves this shell's current line number
 *
 * Return: The current line number of the shell
 */
int get_line_num()
{
	return (Line_Num);
}
