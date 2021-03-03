#include "../include/minishell.h"

int		run_env(void)
{
	extern	char	**environ;
	int				i;

	i = 0;
	while (environ[i] != NULL)
		printf("%s\n", environ[i++]);
	return 1;
}
