#include "../include/minishell.h"

int		run_cd(char **args)
{
	extern	char	**environ;

	if (args[1] == NULL)
	{
		while (ft_strncmp(*environ, "HOME", 4))
			(*environ)++;
		if (chdir(*environ + 5) == ERROR)
			ft_putendl_fd("\x1b[32mminishell: \x1b[mcd : HOME not set", 1);
	}
	else
	{
		if (chdir(args[1]) == ERROR)
			put_error();
	}
	return (1);
}