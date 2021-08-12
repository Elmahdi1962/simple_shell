#include <stdlib.h>
#include "main.h"

int sc_exit(int ac, char *av[])
{
	int status = 0;

	if (av == NULL)
	{
		/* TODO: Print error message */
		/* return (-1); */
	}
	if (ac >= 1)
	{
		;
	}
	/* write history to file */
	exit(status);
	return (0);
}

int sc_env(int ac, char *av[])
{
	(void)ac;
	(void)av;
	return (0);
}
