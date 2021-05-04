/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_free_env_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 15:12:48 by dogata            #+#    #+#             */
/*   Updated: 2021/04/20 19:44:15 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_lstclear_ms(t_list **env_lst)
{
	t_list		*current;
	t_list		*next;
	t_env_list	*current_content;

	if (!env_lst)
		return ;
	current = *env_lst;
	while (current != NULL)
	{
		current_content = current->content;
		next = current->next;
		free(current_content->env_var);
		free(current_content->var_name);
		free(current_content->value);
		free(current_content);
		free(current);
		current = next;
	}
	*env_lst = NULL;
}

t_env_list	*ft_lstnew_ms(char *env, char *front, char *back)
{
	t_env_list	*list;

	list = malloc(sizeof(t_env_list));
	if (list == NULL)
		put_error_exit(NULL);
	list->env_var = ft_strdup(env);
	list->var_name = front;
	list->value = back;
	return (list);
}

void	create_env_var_list(t_ms *ms, char **env)
{
	ms->env_lst = NULL;
	ms->tmp_lst = NULL;
	ms->env_var_count = 0;
	while (*env != NULL)
	{
		div_at_equal(ms, *env);
		ms->tmp_lst = ft_lstnew(ft_lstnew_ms(*env, ms->div[0], ms->div[1]));
		if (ms->tmp_lst == NULL)
			put_error_exit(NULL);
		ft_lstadd_back(&(ms->env_lst), ms->tmp_lst);
		ms->env_var_count++;
		(void)*env++;
		free(ms->div);
	}
}

void	add_env_var_list(t_ms *ms, char *arg)
{
	ms->tmp_lst = NULL;
	div_at_equal(ms, arg);
	ms->tmp_lst = ft_lstnew(ft_lstnew_ms(arg, ms->div[0], ms->div[1]));
	if (ms->tmp_lst == NULL)
		put_error_exit(NULL);
	ft_lstadd_back(&(ms->env_lst_front), ms->tmp_lst);
	ms->env_var_count++;
	free(ms->div);
	free_od_array(&ms->converted_new_str, 0);
}
