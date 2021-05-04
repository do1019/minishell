/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 18:32:20 by hikeda            #+#    #+#             */
/*   Updated: 2021/04/18 20:02:29 by hikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_quote(t_args *list)
{
	if (list->sq_flag == 0 && list->dq_flag == 0 && list->bs_flag == 0
		&& list->old_str[list->osp] == '\'')
		list->sq_flag = 1;
	else if (list->sq_flag == 0 && list->dq_flag == 0 && list->bs_flag == 0
		&& list->old_str[list->osp] == '\"')
		list->dq_flag = 1;
	else if (list->sq_flag == 1 && list->dq_flag == 0 && list->bs_flag == 0
		&& list->old_str[list->osp] == '\'')
		list->sq_flag = 0;
	else if (list->sq_flag == 0 && list->dq_flag == 1 && list->bs_flag == 0
		&& list->old_str[list->osp] == '\"')
		list->dq_flag = 0;
	else if ((list->dq_flag == 1 && check_dq_backslash(list))
		|| (list->sq_flag == 1)
		|| (list->sq_flag == 0 && (list->old_str[list->osp] != '\\'
				|| (list->old_str[list->osp] == '\\' && list->bs_flag == 1))))
		list->new_str[list->nsp++] = list->old_str[list->osp];
}

void	create_str(t_ms *ms, t_args *list, char *args)
{
	list->old_str = args;
	list->new_str = (char *)malloc(sizeof(char) * (ft_strlen(args) + 1));
	if (list->new_str == NULL)
		put_error_exit(NULL);
	while (list->old_str[list->osp] != '\0')
	{
		if (list->osp > 0)
			check_backslash(list);
		check_redirect(ms, list);
		check_quote(list);
		list->osp++;
	}
	list->new_str[list->nsp] = '\0';
	ms->redirect_num += list->red_num;
}

void	parse_args(t_ms *ms, t_args *list, char **args)
{
	t_args	*current_list;
	int		argc;
	int		i;

	ms->redirect_flag = false;
	ms->redirect_num = 0;
	argc = 0;
	while (args[argc])
		argc++;
	init_list(list, 0);
	create_list(list, argc);
	list->num = argc;
	current_list = list;
	i = -1;
	while (++i < argc)
	{
		create_str(ms, current_list, args[i]);
		check_upcase(current_list->new_str, i);
		current_list = current_list->next;
	}
	if (ms->redirect_flag == true)
		create_argv1(ms, list);
}
