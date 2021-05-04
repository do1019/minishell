/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_semicolon.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 15:08:45 by dogata            #+#    #+#             */
/*   Updated: 2021/04/20 23:54:39 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	is_valid_semicolon_exists(t_ms *ms)
{
	int	i;

	i = 0;
	ms->single_quate_flag = false;
	ms->double_quate_flag = false;
	ms->back_slash_flag = false;
	if (is_head_charactor_exists(ms, ';') == ERROR)
		return (ERROR);
	while (ms->line[i])
	{
		is_valid_quates(ms, ms->line, i);
		if (!ms->single_quate_flag && !ms->double_quate_flag && \
								!ms->back_slash_flag && ms->line[i] == ';')
		{
			ms->semicolon_num++;
			ms->semicolon_flag = true;
		}
		is_valid_backslash(ms, ms->line, i);
		i++;
	}
	if (ms->semicolon_flag != true)
		ms->main_loop_count = 1;
	return (0);
}

static int	is_valid_line_syntax(t_ms *ms)
{
	if (check_pipeline_syntax(ms) == ERROR)
		return (ERROR);
	if (is_valid_semicolon_exists(ms) == ERROR)
		return (ERROR);
	return (0);
}

int	split_command_line_with_semicolon(t_ms *ms)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (ft_strchr(ms->line, ';'))
	{
		if (is_valid_line_syntax(ms) == ERROR)
			return (ERROR);
		if (ms->semicolon_flag != true)
			return (0);
		ms->loop_count = ms->semicolon_num + 1;
		while (ms->loop_count)
		{
			is_valid_quates(ms, ms->line, i);
			if (create_splited_line_with_semicolon(ms, &i, &j) == ERROR)
				return (ERROR);
			is_valid_backslash(ms, ms->line, i);
			i++;
		}
		ms->sc_splited_line[ms->sc_splited_count] = NULL;
	}
	ms->main_loop_count = ms->semicolon_num + 1;
	return (0);
}
