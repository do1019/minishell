/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_args_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 09:19:44 by hikeda            #+#    #+#             */
/*   Updated: 2021/04/18 19:44:02 by hikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_args_list(t_args *list)
{
	int		i;
	t_args	*current_list;
	t_args	*next;

	i = 0;
	current_list = list;
	while (current_list != NULL)
	{
		next = current_list->next;
		free_od_array(&current_list->new_str, 0);
		if (i > 0)
			free(current_list);
		current_list = next;
		i++;
	}
}

void	free_redirect_builtin_argv(t_args *list)
{
	int		i;

	if (list->argv != NULL)
	{
		i = 0;
		while (list->argv[i])
			free(list->argv[i++]);
		free(list->argv);
	}
}

void	free_redirect_argv(t_args *list)
{
	int		i;

	if (list->argv != NULL)
	{
		i = 0;
		while (list->argv[i])
			free(list->argv[i++]);
		free(list->argv);
	}
	if (list->red_argv != NULL)
	{
		i = 0;
		while (list->red_argv[i])
			free(list->red_argv[i++]);
		free(list->red_argv);
	}
}

void	free_exit(t_ms *ms, t_args *list)
{
	int		i;

	i = 0;
	while (i < ms->his)
		free(ms->history[i++]);
	free(ms->line);
	free(ms->current_dir_path);
	free_args_list(list);
	free_td_array(&ms->args, 0);
}
