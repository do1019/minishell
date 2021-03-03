#include "../include/minishell.h"

void	put_error_exit()
{
	int	errnum;

	errnum = errno;
	ft_putstr_fd("\x1b[32mminishell: \x1b[m", 2);
	ft_putendl_fd(strerror(errnum), 2);
	exit(EXIT_FAILURE);
}

void	put_error()
{
	int	errnum;

	errnum = errno;
	ft_putstr_fd("\x1b[32mminishell: \x1b[m", 2);
	ft_putendl_fd(strerror(errnum), 2);
}

int		put_error_rt()
{
	int	errnum;

	errnum = errno;
	ft_putstr_fd("\x1b[32mminishell: \x1b[m", 2);
	ft_putendl_fd(strerror(errnum), 2);
	return (ERROR);
}

char	*put_error_free(char **ptr)
{
	int	errnum;

	errnum = errno;
	if (ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
	ft_putstr_fd("\x1b[32mminishell: \x1b[m", 2);
	ft_putendl_fd(strerror(errnum), 2);
	return (NULL);
}
