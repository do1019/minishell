/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_split_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 15:07:50 by dogata            #+#    #+#             */
/*   Updated: 2021/04/21 07:20:19 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static bool	is_separator(t_ms *ms, char c, char *separator)
{
	if (!ms->single_quate_flag && !ms->double_quate_flag)
	{
		while (*separator)
		{
			if (c == *separator || c == '\0')
				return (true);
			separator++;
		}
	}
	return (false);
}

static void	sc_count_array(t_ms *ms, char *line)
{
	int	i;

	i = 0;
	ms->array_count = 0;
	prepare_split_command(ms);
	while (line[i])
	{
		ms->separate_flag = false;
		while (is_separator(ms, line[i], SEPARATOR) && line[i])
		{
			ms->separate_flag = false;
			i++;
		}
		while (!is_separator(ms, line[i], SEPARATOR) && line[i])
		{
			is_valid_quates(ms, line, i);
			is_valid_backslash(ms, line, i);
			if (!ms->single_quate_flag && !ms->double_quate_flag)
				ms->separate_flag = true;
			i++;
		}
		if (ms->separate_flag)
			ms->array_count++;
	}
}

static void	creation(t_ms *ms, char *line, int i, int *j)
{
	if (ms->separate_flag == true
		&& !ms->single_quate_flag && !ms->double_quate_flag)
	{
		ms->args[*j] = ft_substr(line, ms->start, i - ms->start);
		if (ms->args[*j] == NULL)
			put_error_exit(NULL);
		ms->separate_flag = false;
		(*j)++;
	}
}

static void	sc_create_array(t_ms *ms, char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	prepare_split_command(ms);
	while (j < ms->array_count)
	{
		if (is_separator(ms, line[i], SEPARATOR))
			creation(ms, line, i, &j);
		else
		{
			is_valid_quates(ms, line, i);
			is_valid_backslash(ms, line, i);
			if (ms->separate_flag != true)
				ms->start = i;
			ms->separate_flag = true;
		}
		i++;
	}
}

void	split_command(t_ms *ms, char *line)
{
	sc_count_array(ms, line);
	ms->args = ft_calloc(ms->array_count + 1, sizeof(char *));
	if (ms->args == NULL)
		put_error_exit(NULL);
	sc_create_array(ms, line);
	ms->args[ms->array_count] = NULL;
}
