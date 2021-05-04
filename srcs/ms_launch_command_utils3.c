/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_launch_command_utils3.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 03:21:11 by dogata            #+#    #+#             */
/*   Updated: 2021/04/26 03:21:36 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	close_and_dup_write(t_ms *ms)
{
	close(ms->current_pipe_fd[READ]);
	if (dup2(ms->current_pipe_fd[WRITE], 1) == ERROR)
		put_error_exit(NULL);
	close(ms->current_pipe_fd[WRITE]);
}

void	close_and_dup_read(t_ms *ms)
{
	close(ms->prev_pipe_fd[WRITE]);
	if (dup2(ms->prev_pipe_fd[READ], 0) == ERROR)
		put_error_exit(NULL);
	close(ms->prev_pipe_fd[READ]);
}

void	close_prev_pipe_fd(t_ms *ms)
{
	if (ms->exec_count > 0)
	{
		close(ms->prev_pipe_fd[READ]);
		close(ms->prev_pipe_fd[WRITE]);
	}
}
