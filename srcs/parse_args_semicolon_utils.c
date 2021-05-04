/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_semicolon_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 15:08:36 by dogata            #+#    #+#             */
/*   Updated: 2021/04/21 00:09:27 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	is_valid_semicolon_syntax(t_ms *ms, char *line, int num)
{
	if (line[num])
		num += 1;
	while (line[num])
	{
		if (is_space(line[num]))
			num++;
		else if (line[num] == ';' || line[num] == '|')
		{
			ft_putstr_fd("\x1b[32mminishell: \x1b[m", 2);
			ft_putstr_fd("syntax error near unexpected token `", 2);
			if (line[num - 1] == line[num])
				ft_putchar_fd(line[num - 1], 2);
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

static int	is_valid_syntax(t_ms *ms, int i)
{
	int	k;

	if (is_valid_semicolon_syntax(ms, ms->line, i) == ERROR)
	{
		k = 0;
		while (k < ms->sc_splited_count)
			free(ms->sc_splited_line[k++]);
		free_od_array(&ms->line, 0);
		return (ERROR);
	}
	return (0);
}

static int	create_splited_line(t_ms *ms, int **i, int **j)
{
	char	*tmp;

	ms->sc_splited_count++;
	if (ms->sc_splited_count == 1)
	{
		ms->sc_splited_line = ft_calloc(sizeof(char *), ms->semicolon_num + 2);
		if (ms->sc_splited_line == NULL)
			return (put_error_rt(ms, ERROR));
	}
	tmp = ft_substr(ms->line, **j, **i - **j);
	if (tmp == NULL)
		return (put_error_rt(ms, ERROR));
	ms->sc_splited_line[ms->sc_splited_count - 1] = ft_strtrim(tmp, " ");
	if (ms->sc_splited_line[ms->sc_splited_count - 1] == NULL)
		return (put_error_rt(ms, free_od_array(&tmp, ERROR)));
	**j = **i + 1;
	free(tmp);
	return (0);
}

int	create_splited_line_with_semicolon(t_ms *ms, int *i, int *j)
{
	if (!ms->single_quate_flag && !ms->double_quate_flag && \
	!ms->back_slash_flag && (ms->line[*i] == ';' || ms->line[*i] == '\0'))
	{
		ms->loop_count--;
		if (is_valid_syntax(ms, *i) == ERROR)
			return (free_od_array(&ms->line, ERROR));
		if (create_splited_line(ms, &i, &j) == ERROR)
		{
			while (ms->sc_splited_count--)
				free(ms->sc_splited_line[ms->sc_splited_count]);
			free(ms->sc_splited_line);
			return (free_od_array(&ms->line, ERROR));
		}
	}
	return (0);
}
