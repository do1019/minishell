/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_error2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hikeda <hikeda@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/13 19:59:01 by hikeda            #+#    #+#             */
/*   Updated: 2021/04/28 20:31:11 by hikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	put_command_error(char *s)
{
	int	errnum;

	errnum = errno;
	ft_putstr_fd("\x1b[32mminishell: \x1b[m", 2);
	if (s)
	{
		ft_putstr_fd(s, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(strerror(errnum), 2);
}

void	put_filename_error(char *s)
{
	int	errnum;

	errnum = errno;
	ft_putstr_fd("\x1b[32mminishell: \x1b[m", 2);
	if (s)
	{
		ft_putstr_fd(s, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(strerror(errnum), 2);
}

void	put_syntax_error_redirect(t_ms *ms)
{
	ft_putstr_fd("\x1b[32mminishell: \x1b[m", 2);
	ft_putstr_fd("syntax error near unexpected token `newline'", 2);
	ft_putstr_fd("\n", 2);
	ms->builtin_command_flag = false;
	ms->exit_code = 258;
}

void	put_syntax_error(t_ms *ms, char *s)
{
	char	str[3];

	str[1] = '\0';
	str[2] = '\0';
	if (ft_isdigit(s[0]))
		str[0] = s[0];
	else
	{
		str[0] = s[0];
		if (s[1])
			str[1] = s[1];
	}
	ft_putstr_fd("\x1b[32mminishell: \x1b[m", 2);
	ft_putstr_fd("syntax error near unexpected token `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("'\n", 2);
	ms->builtin_command_flag = false;
	ms->exit_code = 258;
}

void	put_ambiguous_error(t_ms *ms, char *s)
{
	ft_putstr_fd("\x1b[32mminishell: \x1b[m", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": ambiguous redirect", 2);
	ft_putstr_fd("\n", 2);
	ms->builtin_command_flag = false;
	ms->exit_code = 1;
}
