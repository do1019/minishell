/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 16:12:24 by hikeda            #+#    #+#             */
/*   Updated: 2021/04/17 16:08:16 by hikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	input_redirect(t_args *list, char *filename, int flag)
{
	if (flag == 1)
		list->fd_out
			= open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IREAD | S_IWRITE);
	else if (flag == 2)
		list->fd_out
			= open(filename, O_WRONLY | O_CREAT | O_APPEND, S_IREAD | S_IWRITE);
	if (list->fd_out < 0)
		put_error_exit(filename);
	if (list->red_argv[0] != NULL)
	{
		close(1);
		if (dup2(list->fd_out, 1) == ERROR)
		{
			close(list->fd_out);
			put_error_exit("dup2");
		}
	}
	close(list->fd_out);
}

void	input_redirect_error(t_args *list, char *filename, int flag)
{
	if (flag == 1)
		list->fd_err
			= open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IREAD | S_IWRITE);
	else if (flag == 2)
		list->fd_err
			= open(filename, O_WRONLY | O_CREAT | O_APPEND, S_IREAD | S_IWRITE);
	if (list->fd_err < 0)
		put_error_exit(filename);
	if (list->red_argv[0] != NULL)
	{
		close(2);
		if (dup2(list->fd_err, 2) == ERROR)
		{
			close(list->fd_err);
			put_error_exit("dup2");
		}
	}
	close(list->fd_err);
}

void	output_redirect(t_args *list, char *filename)
{
	list->fd_in = open(filename, O_RDONLY);
	if (list->fd_in < 0)
		put_error_exit(filename);
	if (list->red_argv[0] != NULL)
	{
		close(0);
		if (dup2(list->fd_in, 0) == ERROR)
		{
			close(list->fd_in);
			put_error_exit("dup2");
		}
	}
	close(list->fd_in);
}
