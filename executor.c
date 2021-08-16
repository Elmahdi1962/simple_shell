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

/* TODO: Test this function */
int exec_program(cmd_t *node, char *program_path)
{
	int exit_code = 0, rc, rc_wait, i;
	char **arg_list = node->args;
	int env_count = *(int *)get_shell_prop(ENVP_COUNT_ID);
	char **env = *(char ***)get_shell_prop(ENVP_ID);
	char **env_c = NULL;
	char **arg_list_c = NULL;

	env_c = malloc(sizeof(void *) * (env_count + 1));
	if (env_c != NULL)
	{
		for (i = 0; i < env_count; i++)
			*(env_c + i) = str_copy(*(env + i));
		*(env_c + i) = NULL;
	}
	arg_list_c = malloc(sizeof(void *) * (node->args_count + 2));
	if (arg_list_c != NULL)
	{
		*arg_list_c = str_copy(node->command);
		for (i = 0; i < node->args_count; i++)
			*(arg_list_c + i + 1) = str_copy(*(node->args + i));
		*(arg_list_c + i + 1) = NULL;
	}
	rc = fork();
	if (rc < 0)
	{
		printf("Failed to create process");
	}
	else if (rc == 0)
	{
		exit_code = execve(program_path, arg_list_c, env_c);
		/* _exit(0); */
	}
	else
	{
		rc_wait = wait(NULL);
		/* TODO: Store the exit code */
		printf("exit code: %d\n", exit_code);
		free(arg_list);
		free(env);
	}
}
