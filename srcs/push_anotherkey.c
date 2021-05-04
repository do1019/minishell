/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_anotherkey.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 15:25:29 by hikeda            #+#    #+#             */
/*   Updated: 2021/04/22 07:01:18 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*push_anotherkey2(t_ms *ms)
{
	char	*ptr;

	write(1, "\033[4h", 4);
	write(1, &ms->c, 1);
	if ((g_signal_flags & SIGNAL_RESET_LINE_FLAG))
	{
		free_od_array(&ms->rd_line, 0);
		ms->rd_line = ft_strdup("");
		if (ms->rd_line == NULL)
			put_error_exit(NULL);
		ms->rd_p = 0;
		g_signal_flags &= ~(SIGNAL_RESET_LINE_FLAG);
	}
	ptr = malloc(sizeof(char) * (ft_strlen(ms->rd_line) + 2));
	if (ptr == NULL)
		put_error_exit(NULL);
	return (ptr);
}

void	push_anotherkey(t_ms *ms, int i, int j, int flag)
{
	char	*tmp;

	tmp = push_anotherkey2(ms);
	if (ft_strlen(ms->rd_line) == 0)
		tmp[j++] = ms->c;
	else
	{
		while (j < (int)(ft_strlen(ms->rd_line) + 1))
		{
			if (j == ms->rd_p && flag == 0)
			{
				tmp[j++] = ms->c;
				flag = 1;
				continue ;
			}
			tmp[j++] = ms->rd_line[i++];
		}
	}
	tmp[j] = '\0';
	free_od_array(&ms->rd_line, 0);
	ms->rd_line = ft_strdup(tmp);
	if (ms->rd_line == NULL)
		put_error_exit(NULL);
	free(tmp);
	ms->rd_p++;
}

void	push_enter(t_ms *ms)
{
	if ((g_signal_flags & SIGNAL_RESET_LINE_FLAG))
	{
		free_od_array(&ms->rd_line, 0);
		ms->rd_line = ft_strdup("");
		if (ms->rd_line == NULL)
			put_error_exit(NULL);
		g_signal_flags &= ~(SIGNAL_RESET_LINE_FLAG);
	}
	write(1, "\033[4l", 4);
	write(1, "\n", 1);
}

void	push_backspace(t_ms *ms, int i, int j)
{
	char	*tmp;

	if (ms->rd_p == 0)
		return ;
	tmp = (char *)malloc(sizeof(char) * (ft_strlen(ms->rd_line)));
	if (tmp == NULL)
		put_error_exit(NULL);
	while (ms->rd_line[i] != '\0')
	{
		if (i == ms->rd_p - 1)
		{
			i++;
			continue ;
		}
		tmp[j++] = ms->rd_line[i++];
	}
	tmp[j] = '\0';
	free_od_array(&ms->rd_line, 0);
	ms->rd_line = ft_strdup(tmp);
	if (ms->rd_line == NULL)
		put_error_exit(NULL);
	free(tmp);
	write(1, "\033[1D", 4);
	write(1, "\033[1P", 4);
	ms->rd_p--;
}

void	ctrl_d(t_ms *ms)
{
	write(1, "\033[4l", 4);
	ft_putendl_fd("exit", 1);
	tcsetattr(0, TCSANOW, &ms->oldtio);
	exit(EXIT_SUCCESS);
}
