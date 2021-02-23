#include "../include/minishell.h"

int		run_env(char **args)
{
	extern	char	**environ;
	char			**env;

	(void)args;
	env = environ;
	while (*env != NULL)
		printf("%s \n", *env++);
	return 1;
}
