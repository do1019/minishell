/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 15:10:38 by dogata            #+#    #+#             */
/*   Updated: 2021/04/25 00:23:37 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	put_error_exit(char *s)
{
	int	errnum;
	int	rt;

	errnum = errno;
	rt = EXIT_FAILURE;
	if (errnum == EACCES)
		rt = COMMAND_CAN_NOT_EXECUTE;
	ft_putstr_fd("\x1b[32mminishell: \x1b[m", 2);
	if (s)
	{
		ft_putstr_fd(s, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(strerror(errnum), 2);
	exit(rt);
}

int	put_error_rt(t_ms *ms, int rt)
{
	int	errnum;

	errnum = errno;
	ms->exit_code = EXIT_FAILURE;
	ft_putstr_fd("\x1b[32mminishell: \x1b[m", 2);
	ft_putendl_fd(strerror(errnum), 2);
	return (rt);
}

void	put_error_exit_for_execve(char *s)
{
	int	errnum;
	int	rt;

	errnum = errno;
	rt = EXIT_FAILURE;
	if (errnum == EACCES)
		rt = COMMAND_CAN_NOT_EXECUTE;
	if (errnum == ENOENT)
		rt = COMMAND_NOT_FOUND;
	ft_putstr_fd("\x1b[32mminishell: \x1b[m", 2);
	if (s)
	{
		ft_putstr_fd(s, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(strerror(errnum), 2);
	exit(rt);
}
