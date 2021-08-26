#include "main.h"

/* The maximum size of the history buffer */
static const short HISTORY_SIZE = 1 << 12;
/* The previous commands run by the shell program */
static char **Cmd_History;
/* Specifies if the history buffer is full. If TRUE, command_strings */
/* in the buffer would be replaced by newer commands */
static char Is_Full;
/* The first line number in the history file */
static int Line_Num;
static int Pos;

/**
 * manage_history - Performs some management operations \
 * on the commands history
 * @op: The operation to perform
 */
void manage_history(int op)
{
	int i, n = 0, fd;
	char **file_lines = NULL, *file_path = NULL;

	if (op == MO_INIT)
	{
		/* Load history file */
		file_path = str_cat(get_env_var("HOME"), HISTORY_FILE, FALSE);
		fd = open(file_path, O_RDONLY);
		file_lines = read_all_lines(fd, &n);
		Pos = 0;
		Is_Full = FALSE;
		if (file_lines != NULL)
		{
			Line_Num = n % HISTORY_SIZE;
			free_array(file_lines, n);
		}
		if (file_path != NULL)
			free(file_path);
		if (fd >= 0)
			close(fd);
	}
	else if (op == MO_FREE)
	{
		if (Cmd_History != NULL)
		{
			for (i = 0; i < (Is_Full ? HISTORY_SIZE : Pos); i++)
			{
				if (*(Cmd_History + i) != NULL)
					free(*(Cmd_History + i));
			}
			if (Cmd_History != NULL)
				free(Cmd_History);
		}
	}
}

/**
 * add_to_history - Adds a line to this shell's history
 * @str: The line to add
 */
void add_to_history(char *str)
{
	int size = Is_Full ? HISTORY_SIZE : Pos;

	Line_Num++;
	if ((str == NULL) || (str_len(str) == 0))
		return;
	Cmd_History = _realloc(Cmd_History, sizeof(void *) * size,
		sizeof(void *) * (size + 1));
	if (Is_Full)
		free(*(Cmd_History + Pos));
	*(Cmd_History + Pos) = str_copy(str);
	Is_Full = Is_Full ? Is_Full : (Pos + 1 == HISTORY_SIZE ? TRUE : FALSE);
	Pos = ((Pos + 1) % HISTORY_SIZE);
	/* Line_Num = ((Line_Num + 1) % HISTORY_SIZE); */
}

/**
 * save_history - Saves this shell's history to the history's file path
 */
void save_history(void)
{
	int fd, i;
	char *file_path = NULL;

	return;
	file_path = str_cat(get_env_var("HOME"), HISTORY_FILE, FALSE);
	fd = open(file_path, O_RDWR | O_TRUNC | O_CREAT, 0777);
	if (fd >= 0)
	{
		for (i = 0; i < (Is_Full ? HISTORY_SIZE : Pos); i++)
		{
			write(fd, *(Cmd_History + i), str_len(*(Cmd_History + i)));
			write(fd, "\n", 1);
		}
		close(fd);
	}
	if (file_path != NULL)
		free(file_path);
}

/**
 * get_history - Retrieves this shell's past commands
 * @size: The pointer to the size of the history buffer
 *
 * Return: A list of stings, otherwise, NULL
 */
char **get_history(int *size)
{
	if (size != NULL)
		*size = (Is_Full ? HISTORY_SIZE : Pos);
	return (Cmd_History);
}

/**
 * get_line_num - Retrieves this shell's current line number
 *
 * Return: The current line number of the shell
 */
int get_line_num(void)
{
	return (Line_Num);
}
