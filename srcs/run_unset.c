/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 15:10:09 by dogata            #+#    #+#             */
/*   Updated: 2021/04/29 00:27:45 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static bool	is_unset_target(t_ms *ms, char *arg)
{
	int			arg_len;
	t_env_list	*current_content;

	arg_len = ft_strlen(arg);
	current_content = ms->env_lst->content;
	if (!ft_memcmp(arg, current_content->var_name, arg_len + 1))
		return (true);
	return (false);
}

static void	advance_list_next(t_ms *ms, t_args *list)
{
	ms->env_lst = ms->env_lst->next;
	ms->current_list = list;
	ms->current_list = ms->current_list->next;
}

static void	check_duplicate(t_ms *ms, int args_count, int *count)
{
	while (args_count--)
	{
		if (is_unset_target(ms, ms->current_list->new_str))
		{
			(*count)++;
			ms->duplicate_flag = true;
			return ;
		}
		ms->current_list = ms->current_list->next;
	}
}

static void	check_duplicate_and_delete_env_var(t_ms *ms,
											t_args *list, char **env)
{
	int	i;
	int	tmp_env_count;

	i = 0;
	tmp_env_count = 0;
	while (i < ms->env_var_count)
	{
		check_duplicate(ms, ms->export_unset_args_count, &i);
		if (ms->duplicate_flag)
			ms->duplicate_flag = false;
		else
		{
			ms->tmp_env[tmp_env_count++] = ft_strdup(env[i++]);
			if (ms->tmp_env[tmp_env_count - 1] == NULL)
				put_error_exit(NULL);
		}
		advance_list_next(ms, list);
	}
}

int	run_unset(t_ms *ms, t_args *list, char **args)
{
	extern char	**environ;

	ms->exit_code = EXIT_SUCCESS;
	if (args[1] != NULL)
	{
		prepare_export_unset_for_argument_exists(ms, list);
		create_env_var_list(ms, environ);
		count_args_and_allocate_tmp_env_memory(ms, list);
		ms->env_lst_front = ms->env_lst;
		is_valid_unset_argument(ms, list);
		check_duplicate_and_delete_env_var(ms, list, environ);
		free_td_array(&environ, 0);
		environ = ms->tmp_env;
		ft_lstclear_ms(&(ms->env_lst_front));
	}
	return (ms->exit_code);
}
