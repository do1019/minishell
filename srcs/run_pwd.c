/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 18:06:36 by hikeda            #+#    #+#             */
/*   Updated: 2021/04/15 16:54:30 by hikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	run_pwd(t_ms *ms, t_args *list)
{
	if (ms->getcwd_buf)
		free(ms->getcwd_buf);
	ms->getcwd_buf = getcwd(NULL, 0);
	if (ms->getcwd_buf == NULL)
	{
		write(list->fd_out, ms->current_dir_path,
			ft_strlen(ms->current_dir_path));
		write(list->fd_out, "\n", 1);
		return (0);
	}
	else
	{
		write(list->fd_out, ms->getcwd_buf, ft_strlen(ms->getcwd_buf));
		write(list->fd_out, "\n", 1);
		return (0);
	}
}
