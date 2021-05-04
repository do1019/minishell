/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 15:08:51 by dogata            #+#    #+#             */
/*   Updated: 2021/04/22 06:14:17 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_foot_charactor_exists(t_ms *ms, char c)
{
	int		i;
	char	*start;

	i = 0;
	start = ft_strrchr(ms->line, c);
	if (start == NULL)
		return (0);
	i++;
	while (is_space(start[i]))
		i++;
	if (start[i] == '\0')
	{
		ft_putstr_fd("\x1b[32mminishell: \x1b[m", 2);
		ft_putstr_fd("syntax error near unexpected token `", 2);
		ft_putchar_fd(c, 2);
		ft_putendl_fd("'", 2);
		ms->exit_code = SYNTAX_ERROR;
		return (free_od_array(&ms->line, ERROR));
	}
	return (0);
}

int	is_head_charactor_exists(t_ms *ms, char c)
{
	int	i;

	i = 0;
	while (is_space(ms->line[i]))
		i++;
	if (ms->line[i] == c)
	{
		ft_putstr_fd("\x1b[32mminishell: \x1b[m", 2);
		ft_putstr_fd("syntax error near unexpected token `", 2);
		if (ms->line[i + 1] == c)
			ft_putchar_fd(c, 2);
		ft_putchar_fd(c, 2);
		ft_putendl_fd("'", 2);
		ms->exit_code = SYNTAX_ERROR;
		return (free_od_array(&ms->line, ERROR));
	}
	return (0);
}

void	is_valid_backslash(t_ms *ms, char *line, int i)
{
	if ((line[i] == '\\') && \
				ms->back_slash_flag == false && !ms->single_quate_flag)
		ms->back_slash_flag = true;
	else
		ms->back_slash_flag = false;
}

bool	is_valid_next_quotes_exists(t_ms *ms, char *line, int i, char c)
{
	i++;
	while (line[i])
	{
		is_valid_backslash(ms, line, i);
		if (line[i] == c && !ms->back_slash_flag)
			return (true);
		i++;
	}
	return (false);
}

void	is_valid_quates(t_ms *ms, char *line, int i)
{
	if ((line[i] == '\'') && !ms->single_quate_flag && !ms->back_slash_flag)
	{
		if (is_valid_next_quotes_exists(ms, line, i, '\''))
			ms->single_quate_flag = true;
	}
	else if ((line[i] == '\'') && ms->single_quate_flag && !ms->back_slash_flag)
		ms->single_quate_flag = false;
	else if ((line[i] == '\"') && \
								!ms->double_quate_flag && !ms->back_slash_flag)
	{
		if (is_valid_next_quotes_exists(ms, line, i, '\"'))
			ms->double_quate_flag = true;
	}
	else if ((line[i] == '\"') && ms->double_quate_flag && !ms->back_slash_flag)
		ms->double_quate_flag = false;
}
