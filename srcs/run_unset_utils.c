/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_unset_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 22:10:11 by dogata            #+#    #+#             */
/*   Updated: 2021/04/27 09:25:18 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static	void	is_empty_string(t_ms *ms, char *arg)
{
	if (arg[0] == '\0')
	{
		ms->exit_code = ERROR_BUILTINS;
		put_error_export_unset_for_argument_exists(ms, "unset");
	}
}

int	is_valid_unset_argument(t_ms *ms, t_args *list)
{
	int		i;
	char	*arg;

	while (ms->current_list != NULL)
	{
		i = 0;
		arg = ms->current_list->new_str;
		is_empty_string(ms, arg);
		while (arg[i])
		{
			if ((i == 0 && !ft_isalpha(arg[i]) && arg[i] != '_') || \
						(i > 0 && !ft_isalnum(arg[i]) && arg[i] != '_'))
			{
				ms->exit_code = ERROR_BUILTINS;
				put_error_export_unset_for_argument_exists(ms, "unset");
				break ;
			}
			i++;
		}
		ms->current_list = ms->current_list->next;
	}
	ms->current_list = list;
	ms->current_list = ms->current_list->next;
	return (0);
}
