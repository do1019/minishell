/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_pipeline_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 15:07:57 by dogata            #+#    #+#             */
/*   Updated: 2021/04/26 04:52:24 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	is_valid_pipeline_exists(t_ms *ms, char *line)
{
	int	i;

	i = 0;
	ms->single_quate_flag = false;
	ms->double_quate_flag = false;
	ms->back_slash_flag = false;
	while (line[i])
	{
		is_valid_quates(ms, line, i);
		if (!ms->single_quate_flag && !ms->double_quate_flag && \
									!ms->back_slash_flag && line[i] == '|')
		{
			ms->pipeline_num++;
			ms->pipeline_flag = true;
		}
		is_valid_backslash(ms, line, i);
		i++;
	}
}

static int	create_splited_line_with_pipeline(t_ms *ms,
												char *line, int **i, int **j)
{
	char	*tmp;

	ms->pl_splited_count++;
	if (ms->pl_splited_count == 1)
	{
		ms->pl_splited_line = ft_calloc(sizeof(char *), ms->pipeline_num + 2);
		if (ms->pl_splited_line == NULL)
			return (put_error_rt(ms, ERROR));
	}
	tmp = ft_substr(line, **j, **i - **j);
	if (tmp == NULL)
		return (put_error_rt(ms, ERROR));
	ms->pl_splited_line[ms->pl_splited_count - 1] = ft_strtrim(tmp, " ");
	if (ms->pl_splited_line[ms->pl_splited_count - 1] == NULL)
		return (put_error_rt(ms, free_od_array(&tmp, ERROR)));
	**j = **i + 1;
	free(tmp);
	return (0);
}

static void	is_splited_line_creatable(t_ms *ms, char *line, int *i, int *j)
{
	is_valid_quates(ms, line, *i);
	if (!ms->single_quate_flag && !ms->double_quate_flag && !ms->back_slash_flag
		&& (line[*i] == '|' || line[*i] == '\0'))
	{
		ms->loop_count--;
		if (create_splited_line_with_pipeline(ms, line, &i, &j) == ERROR)
			exit(EXIT_FAILURE);
	}
	is_valid_backslash(ms, line, *i);
}

int	split_command_line_with_pipeline(t_ms *ms, char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	ms->pl_splited_count = 0;
	ms->pipeline_num = 0;
	if (ft_strchr(line, '|'))
	{
		is_valid_pipeline_exists(ms, line);
		if (ms->pipeline_flag != true)
			return (0);
		ms->loop_count = ms->pipeline_num + 1;
		while (ms->loop_count)
		{
			is_splited_line_creatable(ms, line, &i, &j);
			i++;
		}
		ms->pl_splited_line[ms->pl_splited_count] = NULL;
		ms->exec_count = 0;
	}
	return (0);
}
