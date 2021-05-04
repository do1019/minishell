/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 18:05:54 by hikeda            #+#    #+#             */
/*   Updated: 2021/04/23 18:41:09 by hikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_args	*put_newstr(t_args *list, t_args *current_list)
{
	write(list->fd_out, current_list->new_str, strlen(current_list->new_str));
	if (current_list->next != NULL)
		write(list->fd_out, " ", 1);
	return (current_list->next);
}

int	ft_strcmp_n(char *str)
{
	int		i;
	int		len;

	len = ft_strlen(str);
	if (str[0] != '-')
		return (1);
	i = 1;
	while (i < len)
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

int	run_echo(t_args *list)
{
	t_args	*current_list;
	int		n_flag;

	current_list = list->next;
	n_flag = 0;
	if (current_list == NULL)
		write(list->fd_out, "\n", 1);
	else if (current_list->new_str[0] == '-' && current_list->new_str[1] == '\0'
		&& current_list->next == NULL)
		write(list->fd_out, "-\n", 2);
	else
	{
		while (current_list != NULL && !ft_strcmp_n(current_list->new_str))
		{
			n_flag = 1;
			current_list = current_list->next;
		}
		while (current_list != NULL)
			current_list = put_newstr(list, current_list);
		if (!n_flag)
			write(list->fd_out, "\n", 1);
	}
	return (0);
}
