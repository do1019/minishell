/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_pipeline.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 15:08:11 by dogata            #+#    #+#             */
/*   Updated: 2021/04/22 05:57:06 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	is_valid_pipeline_syntax(t_ms *ms, char *line, int num)
{
	if (line[num])
		num += 1;
	while (line[num])
	{
		if (is_space(line[num]))
			num++;
		else if (line[num] == '|' || line[num] == ';')
		{
			ft_putstr_fd("\x1b[32mminishell: \x1b[m", 2);
			ft_putstr_fd("syntax error near unexpected token `", 2);
			if (line[num + 1] == line[num])
				ft_putchar_fd(line[num], 2);
			ft_putchar_fd(line[num], 2);
			ft_putendl_fd("'", 2);
			ms->exit_code = SYNTAX_ERROR;
			return (ERROR);
		}
		else
			break ;
	}
	return (0);
}

static int	check_pipeline_syntax_with_semicolon(t_ms *ms)
{
	int	i;
	int	j;

	i = 0;
	while (i < ms->sc_splited_count)
	{
		j = 0;
		while (ms->sc_splited_line[i][j])
		{
			is_valid_quates(ms, ms->sc_splited_line[i], j);
			if (!ms->single_quate_flag && !ms->double_quate_flag \
											&& ms->sc_splited_line[i][j] == '|')
			{
				if (is_valid_pipeline_syntax(ms, ms->sc_splited_line[i], \
																	j) == ERROR)
					return (free_od_array(&ms->line, \
								free_td_array(&ms->sc_splited_line, ERROR)));
			}
			is_valid_backslash(ms, ms->sc_splited_line[i], j);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_pipeline_syntax(t_ms *ms)
{
	int	i;

	i = 0;
	while (ms->line[i])
	{
		is_valid_quates(ms, ms->line, i);
		if (!ms->single_quate_flag && !ms->double_quate_flag \
					&& !ms->back_slash_flag && ms->line[i] == '|')
		{
			if (is_valid_pipeline_syntax(ms, ms->line, i) == ERROR)
				return (free_od_array(&ms->line, ERROR));
		}
		is_valid_backslash(ms, ms->line, i);
		i++;
	}
	return (0);
}

int	is_valid_pipeline_with_correct_syntax(t_ms *ms)
{
	int	rt;

	ms->single_quate_flag = false;
	ms->double_quate_flag = false;
	ms->back_slash_flag = false;
	if (is_head_charactor_exists(ms, '|') == ERROR)
		return (ERROR);
	if (is_foot_charactor_exists(ms, '|') == ERROR)
		return (ERROR);
	if (ms->semicolon_flag == true)
		rt = check_pipeline_syntax_with_semicolon(ms);
	else
		rt = check_pipeline_syntax(ms);
	return (rt);
}
