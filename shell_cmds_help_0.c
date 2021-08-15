#include "main.h"

/**
 * help_program - print help text of the shell rash
 */
void help_program(void)
{
	int fd = open("./help_docs/rash.txt", O_RDONLY);
	char buf[1024];
	int buflen;

	while((buflen = read(fd, buf, 1024)) > 0)
	{
		write(STDOUT_FILENO, buf, buflen);
	}
	close(fd);
}

/**
 * help_alias - print help text of alias
 */
void help_alias(void)
{
	int fd = open("./help_docs/alias.txt", O_RDONLY);
	char buf[1024];
	int buflen;

	while((buflen = read(fd, buf, 1024)) > 0)
	{
		write(STDOUT_FILENO, buf, buflen);
	}
	close(fd);
}

/**
 * help_cd - print help text of cd
 */
void help_cd(void)
{
	int fd = open("./help_docs/cd.txt", O_RDONLY);
	char buf[1024];
	int buflen;

	while((buflen = read(fd, buf, 1024)) > 0)
	{
		write(STDOUT_FILENO, buf, buflen);
	}
	close(fd);
}

/**
 * help_env - print help text of env
 */
void help_env(void)
{
	int fd = open("./help_docs/env.txt", O_RDONLY);
	char buf[1024];
	int buflen;

	while((buflen = read(fd, buf, 1024)) > 0)
	{
		write(STDOUT_FILENO, buf, buflen);
	}
	close(fd);
}

/**
 * help_exit - print help text of exit
 */
void help_exit(void)
{
	int fd = open("./help_docs/exit.txt", O_RDONLY);
	char buf[1024];
	int buflen;

	while((buflen = read(fd, buf, 1024)) > 0)
	{
		write(STDOUT_FILENO, buf, buflen);
	}
	close(fd);
}

/**
 * help_help - print help text of help
 */
void help_help(void)
{
	int fd = open("./help_docs/help.txt", O_RDONLY);
	char buf[1024];
	int buflen;

	while((buflen = read(fd, buf, 1024)) > 0)
	{
		write(STDOUT_FILENO, buf, buflen);
	}
	close(fd);
}

/**
 * help_history - print help text of history
 */
void help_history(void)
{
	int fd = open("./help_docs/history.txt", O_RDONLY);
	char buf[1024];
	int buflen;

	while((buflen = read(fd, buf, 1024)) > 0)
	{
		write(STDOUT_FILENO, buf, buflen);
	}
	close(fd);
}

/**
 * help_setenv - print help text of setenv
 */
void help_setenv(void)
{
	int fd = open("./help_docs/setenv.txt", O_RDONLY);
	char buf[1024];
	int buflen;

	while((buflen = read(fd, buf, 1024)) > 0)
	{
		write(STDOUT_FILENO, buf, buflen);
	}
	close(fd);
}

/**
 * help_unsetenv - print help text of unsetenv
 */
void help_unsetenv(void)
{
	int fd = open("./help_docs/unsetenv.txt", O_RDONLY);
	char buf[1024];
	int buflen;

	while((buflen = read(fd, buf, 1024)) > 0)
	{
		write(STDOUT_FILENO, buf, buflen);
	}
	close(fd);
}
