/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 15:09:56 by dogata            #+#    #+#             */
/*   Updated: 2021/04/28 21:24:29 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	run_export_for_argument_exists(t_ms *ms, t_args *list)
{
	extern char	**environ;
	int			i;

	prepare_export_unset_for_argument_exists(ms, list);
	create_env_var_list(ms, environ);
	count_args_and_allocate_tmp_env_memory(ms, list);
	duplicate_env_to_tmp_env(ms, environ, &i);
	ms->env_lst_front = ms->env_lst;
	while (ms->export_unset_args_count--)
	{
		if (is_valid_export_argument(ms, ms->current_list->new_str) == ERROR)
		{
			ms->exit_code = ERROR_BUILTINS;
			put_error_export_unset_for_argument_exists(ms, "export");
			ms->current_list = ms->current_list->next;
			continue ;
		}
		check_duplicate_and_add_env_var(ms, &i);
		add_env_var_list(ms, ms->converted_new_str);
		ms->current_list = ms->current_list->next;
	}
	free_td_array(&environ, 0);
	environ = ms->tmp_env;
	ft_lstclear_ms(&(ms->env_lst_front));
}

static void	display_all_env_var(t_ms *ms)
{
	while (ms->env_var_count--)
	{
		ms->current_content = ms->env_lst->content;
		if (!ft_memcmp(ms->current_content->var_name, "_", 1))
		{
			ms->env_lst = ms->env_lst->next;
			continue ;
		}
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(ms->current_content->var_name, 1);
		if (ms->current_content->value)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(ms->current_content->value, 1);
			ft_putendl_fd("\"", 1);
		}
		else
			ft_putendl_fd("", 1);
		ms->env_lst = ms->env_lst->next;
	}
}

int	run_export(t_ms *ms, t_args *list, char **args)
{
	extern char	**environ;

	ms->exit_code = EXIT_SUCCESS;
	if (args[1] == NULL)
	{
		create_env_var_list(ms, environ);
		ft_lstsort(&(ms->env_lst), ms->env_var_count);
		ms->env_lst_front = ms->env_lst;
		display_all_env_var(ms);
		ft_lstclear_ms(&(ms->env_lst_front));
	}
	else
		run_export_for_argument_exists(ms, list);
	return (ms->exit_code);
}
