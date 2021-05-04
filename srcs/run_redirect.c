/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 14:02:28 by hikeda            #+#    #+#             */
/*   Updated: 2021/04/29 13:08:20 by hikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	change_argv(t_args *list, int i, int j, int k)
{
	list->red_argv = (char **)malloc(sizeof(char *)
			* (list->argc - list->red_num + 2));
	if (list->red_argv == NULL)
		put_error_exit(NULL);
	while (list->argv[++i])
	{
		if (check_redirect_command(list->argv[i], 0))
		{
			if (k <= list->red_num)
			{
				k++;
				if (list->argv[i + 1] != NULL)
					i++;
			}
			continue ;
		}
		list->red_argv[j] = ft_strdup(list->argv[i]);
		if (list->red_argv[j++] == NULL)
			put_error_exit(NULL);
	}
	list->red_argv[j] = NULL;
}

void	set_fd(t_args *list, int i)
{
	if (!ft_strcmp(list->argv[i], ">") || !ft_strcmp(list->argv[i], "1>"))
		input_redirect(list, list->argv[i + 1], 1);
	else if (!ft_strcmp(list->argv[i], ">>")
		|| !ft_strcmp(list->argv[i], "1>>"))
		input_redirect(list, list->argv[i + 1], 2);
	else if (!ft_strcmp(list->argv[i], "2>"))
		input_redirect_error(list, list->argv[i + 1], 1);
	else if (!ft_strcmp(list->argv[i], "2>>"))
		input_redirect_error(list, list->argv[i + 1], 2);
	else if (!ft_strcmp(list->argv[i], "<"))
		output_redirect(list, list->argv[i + 1]);
}

void	reset_dup_fd(t_args *list)
{
	if (dup2(0, 0) < 0)
	{
		close(0);
		put_error_exit("dup2");
	}
	if (dup2(1, 1) < 0)
	{
		close(1);
		put_error_exit("dup2");
	}
	if (dup2(2, 2) < 0)
	{
		close(2);
		put_error_exit("dup2");
	}
	close(0);
	close(1);
	close(2);
	list->fd_in = 0;
	list->fd_out = 1;
	list->fd_err = 2;
}

void	check_redirect_in_string(t_args *list, int i)
{
	extern char	**environ;

	while (list->argv[i])
		set_fd(list, i++);
	if (list->red_argv[0] != NULL)
	{
		if (execve(list->red_argv[0], list->red_argv, environ) == ERROR)
		{
			put_command_error(list->red_argv[0]);
			exit(127);
		}
		reset_dup_fd(list);
	}
	else
		exit(0);
}

int	run_redirect(t_ms *ms, t_args *list)
{
	check_consecutive_redirect(ms, list);
	if (ms->exit_code == 1 || ms->exit_code == 258)
		return (ms->exit_code);
	ms->wpid_status = 0;
	ms->pid = fork();
	if (ms->pid == ERROR)
		put_error_exit("fork");
	if (ms->pid == 0)
	{
		if (list->red_argv[0] != NULL)
			if (!ft_strchr(list->red_argv[0], '/'))
				convert_command_name(ms, list);
		check_redirect_in_string(list, 0);
	}
	else
	{
		ms->wpid = waitpid(ms->pid, &ms->wpid_status, WUNTRACED);
		if (ms->wpid < 0)
			put_error_exit("wait");
		else
			ms->exit_code = WEXITSTATUS(ms->wpid_status);
	}
	return (ms->exit_code);
}
