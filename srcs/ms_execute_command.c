/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 15:07:15 by dogata            #+#    #+#             */
/*   Updated: 2021/04/28 02:47:46 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_builtin_and_redirect_command(t_ms *ms, t_args *list)
{
	int		i;

	i = -1;
	ms->builtin_command_flag = false;
	while (list->argv[++i])
	{
		if (!ft_strcmp(list->argv[i], "echo")
			|| !ft_strcmp(list->argv[i], "pwd")
			|| !ft_strcmp(list->argv[i], "env")
			|| !ft_strcmp(list->argv[i], "exit")
			|| !ft_strcmp(list->argv[i], "cd")
			|| !ft_strcmp(list->argv[i], "export")
			|| !ft_strcmp(list->argv[i], "unset"))
			ms->builtin_command_flag = true;
	}
	if ((check_redirect_command(list->argv[list->argc - 1], 0) > 0)
		&& list->argc == 1)
		list->red_err = 1;
}

void	is_builtin_command(t_ms *ms, t_args *list)
{
	if (ms->redirect_flag == true)
		return ;
	ms->builtin_command_flag = false;
	if (!ft_strcmp(list->new_str, "echo") || \
		!ft_strcmp(list->new_str, "pwd") || \
		!ft_strcmp(list->new_str, "env") || \
		!ft_strcmp(list->new_str, "exit") || \
		!ft_strcmp(list->new_str, "cd") || \
		!ft_strcmp(list->new_str, "export") || \
		!ft_strcmp(list->new_str, "unset"))
		ms->builtin_command_flag = true;
}

void	execute_buildin_command(t_ms *ms, t_args *list, char **args)
{
	if (ms->redirect_flag == true && ms->builtin_command_flag == false)
		ms->exit_code = run_redirect(ms, list);
	else if (ms->redirect_flag == true && ms->builtin_command_flag == true)
		ms->exit_code = run_redirect_builtin_command(ms, list);
	if (ms->builtin_command_flag == false)
		return ;
	if (!ft_strcmp(list->new_str, "echo"))
		ms->exit_code = run_echo(list);
	else if (!ft_strcmp(list->new_str, "pwd"))
		ms->exit_code = run_pwd(ms, list);
	else if (!ft_strcmp(list->new_str, "env"))
		ms->exit_code = run_env(list);
	else if (!ft_strcmp(list->new_str, "exit"))
		ms->exit_code = run_exit(ms, list);
	else if (!ft_strcmp(list->new_str, "cd"))
		ms->exit_code = run_cd(ms, list, args);
	else if (!ft_strcmp(list->new_str, "export"))
		ms->exit_code = run_export(ms, list, args);
	else if (!ft_strcmp(list->new_str, "unset"))
		ms->exit_code = run_unset(ms, list, args);
	if (ms->redirect_flag == true && ms->builtin_command_flag == true)
		reset_fd(list);
}

int	execute_command(t_ms *ms, t_args *list, char **args)
{
	if (!args[0])
		return (1);
	is_builtin_command(ms, list);
	if (ms->pipeline_flag != true)
	{
		execute_buildin_command(ms, list, args);
		if (ms->builtin_command_flag == true || ms->redirect_flag == true)
			return (1);
	}
	return (launch_command(ms, list, args));
}
