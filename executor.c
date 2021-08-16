#include "main.h"

/**
 * exec_built_in_cmd - Executes a built-in command
 * @node: The built-in command's node
 *
 * Return: The exit code of the command
 */
int exec_built_in_cmd(cmd_t *node)
{
	int i;
	struct built_in_cmd_s built_in_cmds[] = {
		{"alias", sc_alias},
		{"cd", sc_cd},
		{"env", sc_env},
		{"exit", sc_exit},
		{"help", sc_help},
		{"history", sc_history},
		{"setenv", sc_setenv},
		{"unsetenv", sc_unsetenv}
	};

	for (i = 0; i < 8; i++)
	{
		if (str_cmp(built_in_cmds[i].cmd_name, node->command) == 0)
		{
			return (built_in_cmds[i].run(node->args_count, node->args));
		}
	}
	return (0);
}
