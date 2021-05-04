/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 15:34:49 by hikeda            #+#    #+#             */
/*   Updated: 2021/04/12 22:04:42 by hikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_backslash(t_args *list)
{
	if (list->osp == 0)
		list->bs_flag = 0;
	else if (list->osp >= 1 && list->old_str[list->osp - 1] == '\\'
		&& list->bs_flag == 0 && list->sq_flag == 0)
		list->bs_flag = 1;
	else if (list->osp >= 1 && list->old_str[list->osp - 1] == '\\'
		&& list->bs_flag == 1 && list->sq_flag == 0)
		list->bs_flag = 0;
	else
		list->bs_flag = 0;
}

int	check_dq_backslash(t_args *list)
{
	if (list->old_str[list->osp] == '\\' && list->old_str[list->osp + 1])
	{
		if (list->old_str[list->osp + 1] == '\"'
			|| list->old_str[list->osp + 1] == '$'
			|| list->old_str[list->osp + 1] == '`'
			|| list->old_str[list->osp + 1] == '\\')
			return (0);
		else
			return (1);
	}
	else
		return (1);
}

void	check_redirect(t_ms *ms, t_args *list)
{
	if (list->sq_flag == 0 && list->dq_flag == 0 && list->osp == 0)
	{
		if (list->old_str[list->osp] == '>'
			|| list->old_str[list->osp] == '<')
		{
			ms->redirect_flag = true;
			list->red_num += 1;
		}
	}
	else if (list->sq_flag == 0 && list->dq_flag == 0 && list->osp >= 1
		&& list->old_str[list->osp - 1] != '>'
		&& list->old_str[list->osp - 1] != '<'
		&& (list->old_str[list->osp - 1] != '\\'
			|| (list->old_str[list->osp - 1] = '\\' && list->bs_flag == 0)))
	{
		if (list->old_str[list->osp] == '>'
			|| list->old_str[list->osp] == '<')
		{
			ms->redirect_flag = true;
			list->red_num += 1;
		}
	}
}
