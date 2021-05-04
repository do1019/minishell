/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 15:10:31 by dogata            #+#    #+#             */
/*   Updated: 2021/04/15 07:29:48 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	swap_content(t_list ***current)
{
	t_env_list		*tmp;

	tmp = (**current)->content;
	(**current)->content = (**current)->next->content;
	(**current)->next->content = tmp;
}

static void	ft_bubble_sort(t_list **current)
{
	t_env_list	*current_content;
	t_env_list	*next_content;

	current_content = (*current)->content;
	next_content = (*current)->next->content;
	if (ft_memcmp(current_content->var_name, \
		next_content->var_name, \
			ft_strlen(current_content->var_name) + 1) > 0)
		swap_content(&current);
	(*current) = (*current)->next;
}

void	ft_lstsort(t_list **env_lst, int lst_count)
{
	int		i;
	int		j;
	t_list	*current;

	i = 0;
	j = 0;
	while (i++ < lst_count - 1)
	{
		current = *env_lst;
		while (j++ < lst_count - 1)
			ft_bubble_sort(&current);
		j = i;
	}
}
