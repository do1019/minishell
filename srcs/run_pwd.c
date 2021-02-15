#include "../include/minishell.h"

int		run_pwd(char **args)
{
	char	*buf;

	(void)args;
	if ((buf = getcwd(NULL, 0)) == NULL)
		perror("getcwd error");
	else
	{
		printf("%s\n", buf);
		free(buf);
	}
	return 1;
}