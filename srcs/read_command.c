/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 15:25:29 by hikeda            #+#    #+#             */
/*   Updated: 2021/04/22 07:08:10 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static	void	set_exit_code(t_ms *ms)
{
	if ((g_signal_flags & SIGNAL_RESET_LINE_FLAG))
		ms->exit_code = EXIT_FAILURE;
}

void	rd_command(t_ms *ms)
{
	ms->c = 0;
	ms->read_rt = read(0, &ms->c, sizeof(ms->c));
}

int	rd_loop(t_ms *ms)
{
	rd_command(ms);
	while (ms->read_rt > 0)
	{
		set_exit_code(ms);
		if (ms->c == UP || ms->c == DOWN || ms->c == RIGHT || ms->c == LEFT)
			push_arrowkey(ms);
		else if (ms->c == 10)
		{
			push_enter(ms);
			break ;
		}
		else if (ms->c == 127)
			push_backspace(ms, 0, 0);
		else if (ms->c == 4 && ms->rd_p == 0)
			ctrl_d(ms);
		else if (ms->c == 9)
		{
			rd_command(ms);
			continue ;
		}
		else
			push_anotherkey(ms, 0, 0, 0);
		rd_command(ms);
	}
	return (ms->read_rt);
}

void	pre_rd_loop(t_ms *ms)
{
	ms->rd_line = ft_strdup("");
	if (ms->rd_line == NULL)
		put_error_exit(NULL);
	ms->rd_i = 1000;
	ms->rd_p = 0;
	ft_putstr_fd("\x1b[32mminishell: \x1b[m", 1);
}

char	*read_command_loop(t_ms *ms)
{
	struct termios	newtio;

	tcgetattr(0, &ms->oldtio);
	newtio = ms->oldtio;
	newtio.c_lflag &= ~ICANON;
	newtio.c_lflag &= ~ECHO;
	newtio.c_cc[VMIN] = 1;
	newtio.c_cc[VTIME] = 0;
	tcsetattr(0, TCSANOW, &newtio);
	while (ms->c != 10)
	{
		pre_rd_loop(ms);
		if (rd_loop(ms) == ERROR)
			put_error_exit(NULL);
	}
	tcsetattr(0, TCSANOW, &ms->oldtio);
	if (ft_strcmp(ms->rd_line, ""))
	{
		ms->history[ms->his] = ft_strdup(ms->rd_line);
		if (ms->history[ms->his++] == NULL)
			put_error_exit(NULL);
	}
	ms->line = ms->rd_line;
	return (ms->rd_line);
}
