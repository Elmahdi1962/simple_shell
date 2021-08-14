#include "main.h"
#include <unistd.h>

void help_program(void)
{}
void help_alias(void)
{}

/**
 * help_cd - print help text on output
 * Return:void
 **/

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
void help_env(void)
{}
void help_exit(void)
{}
void help_help(void)
{}
void help_history(void)
{}
void help_setenv(void)
{}
void help_unsetenv(void)
{}
