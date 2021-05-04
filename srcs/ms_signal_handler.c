/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signal_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 15:05:19 by dogata            #+#    #+#             */
/*   Updated: 2021/04/27 07:58:20 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	signal_handler_in_launch(t_ms *ms)
{
	if (ms->wpid_status == SIGINT)
	{
		ms->exit_code = 130;
		if (!(g_signal_flags & SIGNAL_NEWLINE_FLAG))
			ft_putstr_fd("\n", 1);
	}
	else if (ms->wpid_status == SIGQUIT)
	{
		ft_putendl_fd("Quit: 3", 1);
		ms->exit_code = 131;
	}
}

void	signal_handler(int signal_number)
{
	if (!(g_signal_flags & SIGNAL_FORK_FLAG))
	{
		if (signal_number == SIGINT)
		{
			g_signal_flags |= SIGNAL_RESET_LINE_FLAG;
			ft_putstr_fd("\n\x1b[32mminishell: \x1b[m", 1);
		}
	}
	else if ((g_signal_flags & SIGNAL_PIPELINE_FLAG) && \
											(g_signal_flags & SIGNAL_FORK_FLAG))
	{
		g_signal_flags |= SIGNAL_NEWLINE_FLAG;
		if (signal_number == SIGINT)
			ft_putstr_fd("\n", 1);
	}
}
