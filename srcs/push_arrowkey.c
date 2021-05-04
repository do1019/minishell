/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_arrowkey.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 15:23:29 by hikeda            #+#    #+#             */
/*   Updated: 2021/04/22 06:56:49 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	push_up(t_ms *ms)
{
	write(1, "\033[12G", 5);
	write(1, "\033[0J", 4);
	if (ms->rd_i == 1000 && ms->his == 0)
		ms->rd_i = 0;
	else if (ms->rd_i == 1000 && ms->his != 0)
		ms->rd_i = ms->his - 1;
	else if (ms->rd_i <= 0)
		ms->rd_i = 0;
	else
		ms->rd_i--;
	if (ms->his > 0 && ms->rd_i >= 0)
	{
		write(1, ms->history[ms->rd_i], ft_strlen(ms->history[ms->rd_i]));
		free_od_array(&ms->rd_line, 0);
		ms->rd_line = ft_strdup(ms->history[ms->rd_i]);
		if (ms->rd_line == NULL)
			put_error_exit(NULL);
		ms->rd_p = ft_strlen(ms->rd_line);
	}
}

void	push_down(t_ms *ms)
{
	write(1, "\033[12G", 5);
	write(1, "\033[0J", 4);
	if (ms->rd_i == 1000)
		return ;
	else if (ms->rd_i >= ms->his)
		ms->rd_i = ms->his;
	else
		ms->rd_i++;
	if (ms->his > 0 && ms->rd_i < ms->his)
	{
		write(1, ms->history[ms->rd_i], ft_strlen(ms->history[ms->rd_i]));
		free_od_array(&ms->rd_line, 0);
		ms->rd_line = ft_strdup(ms->history[ms->rd_i]);
		if (ms->rd_line == NULL)
			put_error_exit(NULL);
		ms->rd_p = ft_strlen(ms->rd_line);
	}
	else if (ms->rd_i == ms->his)
	{
		free_od_array(&ms->rd_line, 0);
		ms->rd_line = ft_strdup("");
		if (ms->rd_line == NULL)
			put_error_exit(NULL);
		ms->rd_p = 0;
	}
}

void	push_arrowkey(t_ms *ms)
{
	if ((g_signal_flags & SIGNAL_RESET_LINE_FLAG))
		g_signal_flags &= ~(SIGNAL_RESET_LINE_FLAG);
	if (ms->c == UP)
		push_up(ms);
	else if (ms->c == DOWN)
		push_down(ms);
	if (ms->c == RIGHT && (int)ft_strlen(ms->rd_line) >= ms->rd_p + 1)
	{
		write(1, "\033[1C", 4);
		ms->rd_p++;
	}
	else if (ms->c == LEFT && ms->rd_p > 0)
	{
		write(1, "\033[1D", 4);
		ms->rd_p--;
	}
}
