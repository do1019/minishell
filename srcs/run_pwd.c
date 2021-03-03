#include "../include/minishell.h"

int		run_pwd(void)
{
	char	*buf;

	if ((buf = getcwd(NULL, 0)) == NULL)
		perror("getcwd error");
	else
	{
		printf("%s\n", buf);
		free(buf);
	}
	return 1;
}
