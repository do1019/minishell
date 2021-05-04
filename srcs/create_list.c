/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 18:07:52 by hikeda            #+#    #+#             */
/*   Updated: 2021/04/29 13:07:23 by hikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_list(t_args *list, int num)
{
	list->element = num;
	list->num = 0;
	list->sq_flag = 0;
	list->dq_flag = 0;
	list->bs_flag = 0;
	list->osp = 0;
	list->nsp = 0;
	list->env_flag = 0;
	list->red_num = 0;
	list->red_err = 0;
	list->fd_in = 0;
	list->fd_out = 1;
	list->fd_err = 2;
	list->argc = 0;
	list->old_str = NULL;
	list->new_str = NULL;
	list->argv = NULL;
	list->red_argv = NULL;
	list->next = NULL;
}

void	duplicate_list(t_args *list, int num)
{
	t_args	*new_list;

	new_list = (t_args *)malloc(sizeof(t_args));
	if (new_list == NULL)
		put_error_exit(NULL);
	init_list(new_list, num);
	list->next = new_list;
}

void	create_list(t_args *list, int argc)
{
	t_args	*current_list;
	int		i;

	current_list = list;
	i = 1;
	while (i < argc)
	{
		duplicate_list(current_list, i);
		current_list = current_list->next;
		i++;
	}
}
