#include "main.h"
#include <sys/wait.h>

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
		{"unsetenv", sc_unsetenv},
		{NULL, NULL}
	};

	for (i = 0; i < 8; i++)
	{
		if (str_eql(built_in_cmds[i].cmd_name, node->command))
		{
			return (built_in_cmds[i].run(node->args_count, node->args));
		}
	}
	return (0);
}

/**
 * exec_program - Executes a program by spawning a new process
 * @node: The command node
 * @program_path: The abolute path of the program
 *
 * Return: The program's exit code
 */
int exec_program(cmd_t *node, char *program_path)
{
	int exit_stat = 0, rc;
	int env_count = *(int *)get_shell_prop(ENVP_COUNT_ID);
	char **env = *(char ***)get_shell_prop(ENVP_ID);
	char **env_c = NULL, **arg_list_c = NULL;

	env_c = copy_environment(env, env_count);
	arg_list_c = copy_arguments(node);
	rc = fork();
	if (rc < 0)
	{
		write(STDERR_FILENO, "Failed to create process\n", 25);
	}
	else if (rc == 0)
	{
		exit(execve(program_path, arg_list_c, env_c));
	}
	else
	{
		wait(&exit_stat);
		if (WIFEXITED(exit_stat))
			return (WEXITSTATUS(exit_stat));
		else
			return (0);
		if ((arg_list_c != NULL) && !(WIFEXITED(exit_stat)))
			free_array(arg_list_c, node->args_count);
		if ((env_c != NULL) && !(WIFEXITED(exit_stat)))
			free_array(env_c, env_count);
	}
	return (0);
}

/**
 * copy_environment - Copies the environment to be passed to a child process
 * @env: The environment variables array
 * @env_count: The number of items in the environmet variables array
 *
 * Return: A copy of the environment variables, otherwise NULL
 */
char **copy_environment(char **env, int env_count)
{
	int i;
	char **env_c = NULL;

	env_c = malloc(sizeof(void *) * (env_count + 1));
	if (env_c != NULL)
	{
		for (i = 0; i < env_count; i++)
			*(env_c + i) = str_copy(*(env + i));
		*(env_c + i) = NULL;
	}
	return (env_c);
}

/**
 * copy_arguments - Copies the arguments to be passed to a child process
 * @node: The command node containing the arguments
 *
 * Return: A copy of the arguments, otherwise NULL
 */
char **copy_arguments(cmd_t *node)
{
	int i;
	char **arg_list_c = NULL;

	arg_list_c = malloc(sizeof(void *) * (node->args_count + 2));
	if (arg_list_c != NULL)
	{
		*arg_list_c = str_copy(node->command);
		for (i = 0; i < node->args_count; i++)
			*(arg_list_c + i + 1) = str_copy(*(node->args + i));
		*(arg_list_c + i + 1) = NULL;
	}
	return (arg_list_c);
}
