#include "main.h"
#include <sys/wait.h>

/**
 * execute_cmds_list - Executes a list of commands
 * @cmds_list: The pointer to the list of commands to execute
 * @exit_code: The pointer to the exit code
 */
void execute_cmds_list(cmd_t **cmds_list, uchar_t *exit_code)
{
	char *buf0, *buf1, *buf2;
	cmd_t *cur = *cmds_list;

	while (cur != NULL)
	{
		add_env_var("_", cur->command);
		dissolve_cmd_parts(cur);
		if (is_built_in_cmd(cur) == TRUE)
		{
			*exit_code = exec_built_in_cmd(cur);
		}
		else if (is_normal_program(cur, &buf2))
		{
			*exit_code = exec_program(cur, buf2);
			if (buf2 != NULL)
				free(buf2);
		}
		else
		{
			buf0 = *((char **)get_shell_prop(EXEC_NAME_ID));
			buf1 = long_to_str(get_line_num());
			write(STDERR_FILENO, buf0, str_len(buf0));
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, buf1, str_len(buf1));
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, cur->command, str_len(cur->command));
			write(STDERR_FILENO, ": not found\n", 12);
			if (buf1 != NULL)
				free(buf1);
			*exit_code = EC_COMMAND_NOT_FOUND;
		}
		cur = get_next_command(cur, *exit_code);
	}
}

/**
 * exec_built_in_cmd - Executes a built-in command
 * @node: The built-in command's node
 *
 * Return: The exit code of the command
 */
int exec_built_in_cmd(cmd_t *node)
{
	int i;
	built_in_cmd_t built_in_cmds[] = {
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

	for (i = 0; built_in_cmds[i].cmd_name != NULL; i++)
	{
		if (str_eql(built_in_cmds[i].cmd_name, node->command))
		{
			return (built_in_cmds[i].run(node->args_count, node->args));
		}
	}
	return (EC_COMMAND_NOT_FOUND);
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
		free_array(arg_list_c, node->args_count + 1);
		free_array(env_c, env_count);
		if (WIFEXITED(exit_stat))
			return (WEXITSTATUS(exit_stat));
		else
			return (EC_SUCCESS);
	}
	return (EC_SUCCESS);
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
		{
			*(arg_list_c + i + 1) = str_copy(*(node->args + i));
		}
		*(arg_list_c + i + 1) = NULL;
	}
	return (arg_list_c);
}
