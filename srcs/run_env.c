#include "../include/minishell.h"

int		run_env(char **args)
{
	extern	char	**environ;

	(void)args;
	while (*environ != NULL)
		printf("%s \n", *environ++);
	return 1;
}
