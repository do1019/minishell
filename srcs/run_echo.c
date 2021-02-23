#include "../include/minishell.h"

int		run_echo(char **args)
{
	int		i;
	int		argc;
	int		n_flag;

	argc = 0;
	while (args[argc])
		argc++;
	if (*args[1] && !ft_strcmp(args[1], "-n"))
		n_flag = 1;
	else
		n_flag = 0;
	i = 1;
	if (n_flag)
		i++;
	while (i < argc)
	{
		printf("%s", args[i]);
		if (i + 1 == argc && !n_flag)
			printf("\n");
		else if (i + 1 != argc)
			printf(" ");
		i++;
	}
	return 1;
}
