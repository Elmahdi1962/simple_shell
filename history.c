#include "main.h"

/**
 * The path containing the previous commands that were run
 */
const char HISTORY_PATH[] = "~/.simple_shell_history";

/**
 * add_to_history - Adds a line to this shell's history
 * @str: The line to add
 */
void add_to_history(char *str)
{
	char new_lines = 0;
	int i;
	char **history = *((char ***)get_shell_prop(CMD_HISTORY_ID));
	int hist_count = *((int *)get_shell_prop(CMD_HISTORY_COUNT_ID));

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
		history = _realloc(history, sizeof(void *) * hist_count, sizeof(void *) * (hist_count + 1));
		*(history + hist_count) = str_copy(str);
		/* *((int *)get_shell_prop(CMD_HISTORY_COUNT_ID)) += 1; */
		history += 1;
	}
}

/**
 * save_history - Saves this shell's history
 */
void save_history()
{
	int fd, i;
	char ***history = (char ***)get_shell_prop(CMD_HISTORY_ID);
	int *hist_count = (int *)get_shell_prop(CMD_HISTORY_COUNT_ID);

	fd = open(HISTORY_PATH, O_WRONLY | O_APPEND | O_CREAT);
	if (fd >= 0)
	{
		for (i = 0; i < *hist_count; i++)
		{
			write(fd, *(*history + i), str_len(*(*history + i)));
			write(fd, "\n", 1);
		}
		free(history);
		free(hist_count);
		close(fd);
	}
}
