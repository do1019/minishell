/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_redirect_builtin_command.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 19:26:03 by hikeda            #+#    #+#             */
/*   Updated: 2021/04/29 13:08:44 by hikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	reset_fd(t_args *list)
{
	if (list->fd_in != 0)
	{
		close(list->fd_in);
		list->fd_in = 0;
	}
	if (list->fd_out != 1)
	{
		close(list->fd_out);
		list->fd_out = 1;
	}
	if (list->fd_err != 2)
	{
		close(list->fd_err);
		list->fd_err = 2;
	}
}

void	redirect_builtin_command(t_ms *ms, t_args *list,
		char *filename, int flag)
{
	reset_fd(list);
	if (flag == 0)
		list->fd_in = open(filename, O_RDONLY);
	else if (flag == 1)
		list->fd_out
			= open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IREAD | S_IWRITE);
	else if (flag == 2)
		list->fd_out
			= open(filename, O_WRONLY | O_CREAT | O_APPEND, S_IREAD | S_IWRITE);
	else if (flag == 3)
		list->fd_err
			= open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IREAD | S_IWRITE);
	else if (flag == 4)
		list->fd_err
			= open(filename, O_WRONLY | O_CREAT | O_APPEND, S_IREAD | S_IWRITE);
	if (list->fd_in < 0 || list->fd_out < 0 || list->fd_err < 0)
	{
		put_filename_error(filename);
		ms->builtin_command_flag = false;
		ms->exit_code = 1;
	}
}

void	check_list(t_ms *ms, t_args *list)
{
	int		i;
	int		j;

	i = -1;
	j = 1;
	ms->exit_code = 0;
	while (list->argv[++i] && ms->exit_code == 0)
	{
		if (check_redirect_command(list->argv[i], 0))
		{
			if (list->argv[i + 1] == NULL)
				put_syntax_error_redirect(ms);
			else if (check_redirect_command(list->argv[i + 1], 0) > 0)
				put_syntax_error(ms, list->argv[i + 1]);
			if (j <= list->red_num)
			{
				j++;
				if (list->argv[i + 1] != NULL)
					i++;
			}
			continue ;
		}
	}
	if (ms->exit_code == 0)
		check_filename(ms, list);
}

int	run_redirect_builtin_command(t_ms *ms, t_args *list)
{
	int		i;

	check_list(ms, list);
	if (ms->exit_code == 1 || ms->exit_code == 258)
		return (ms->exit_code);
	i = -1;
	while (list->argv[++i])
	{
		if (!ft_strcmp(list->argv[i], ">") || !ft_strcmp(list->argv[i], "1>"))
			redirect_builtin_command(ms, list, list->argv[i + 1], 1);
		else if (!ft_strcmp(list->argv[i], ">>")
			|| !ft_strcmp(list->argv[i], "1>>"))
			redirect_builtin_command(ms, list, list->argv[i + 1], 2);
		else if (!ft_strcmp(list->argv[i], "2>"))
			redirect_builtin_command(ms, list, list->argv[i + 1], 3);
		else if (!ft_strcmp(list->argv[i], "2>>"))
			redirect_builtin_command(ms, list, list->argv[i + 1], 4);
		else if (!ft_strcmp(list->argv[i], "<"))
			redirect_builtin_command(ms, list, list->argv[i + 1], 0);
	}
	return (ms->exit_code);
}
