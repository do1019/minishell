/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_export_unset_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 15:09:44 by dogata            #+#    #+#             */
/*   Updated: 2021/04/29 00:27:27 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	prepare_export_unset_for_argument_exists(t_ms *ms, t_args *list)
{
	ms->current_list = list;
	ms->current_list = ms->current_list->next;
	ms->export_unset_args_count = 0;
	ms->duplicate_flag = false;
}

void	count_args_and_allocate_tmp_env_memory(t_ms *ms, t_args *list)
{
	t_args	*current_list;

	current_list = list;
	ms->export_unset_args_count = 0;
	while (current_list->next != NULL)
	{
		ms->export_unset_args_count++;
		current_list = current_list->next;
	}
	ms->tmp_env = ft_calloc(ms->export_unset_args_count + \
									ms->env_var_count + 1, sizeof(char *));
	if (ms->tmp_env == NULL)
		put_error_exit(NULL);
}

void	div_at_equal(t_ms *ms, char *env)
{
	char	*equal;

	ms->div = ft_calloc(3, sizeof(char *));
	if (ms->div == NULL)
		put_error_exit(NULL);
	equal = ft_strchr(env, '=');
	if (equal == NULL)
	{
		ms->div[0] = ft_strdup(env);
		ms->div[1] = NULL;
	}
	else
	{
		ms->div[0] = ft_substr(env, 0, equal - env);
		ms->div[1] = ft_substr(env, equal - env + 1, ft_strlen(equal) - 1);
		ms->div[2] = NULL;
	}
	if ((equal && (!ms->div[0] || !ms->div[1])) || (!equal && !ms->div[0]))
		put_error_exit(NULL);
}

void	put_error_export_unset_for_argument_exists(t_ms *ms, char *s)
{
	ft_putstr_fd("\x1b[32mminishell: \x1b[m", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(ms->current_list->new_str, 2);
	ft_putendl_fd("': not a valid identifier", 2);
}
