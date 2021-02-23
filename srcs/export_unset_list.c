#include "../include/minishell.h"

t_env_lst	*ft_lstnew_ms(char *env, char *front, char *back)
{
	t_env_lst	*lst;

	if (!(lst = malloc(sizeof(t_env_lst))))
		put_error_exit();
	lst->env_var = ft_strdup(env);
	lst->var_name = front;
	lst->value = back;
	return (lst);
}

void		swap(t_list ***current)
{
	t_env_lst		*tmp;

	tmp = (**current)->content;
	(**current)->content = (**current)->next->content;
	(**current)->next->content = tmp;
}

void		ft_bubble_sort(t_list **current)
{
	t_env_lst	*current_content;
	t_env_lst	*next_content;

	current_content = (*current)->content;
	next_content = (*current)->next->content;
	if (ft_memcmp(current_content->var_name,
	 	next_content->var_name,
	 		ft_strlen(current_content->var_name) + 1) > 0)
		swap(&current);
	(*current) = (*current)->next;
}

void		ft_lstsort(t_list **env_lst, int lst_count)
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

void		ft_lstclear_ms(t_list **env_lst)
{
	t_list		*current;
	t_list		*next;
	t_env_lst	*current_content;

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

void		create_env_var_list(t_export *export, char **env)
{
	char **div;

	export->env_lst = NULL;
	export->tmp_lst = NULL;
	export->env_count = 0;
	while (*env != NULL)
	{
		div = div_at_equal(*env);
		if (!(export->tmp_lst = ft_lstnew(ft_lstnew_ms(*env, div[0], div[1]))))
			put_error_exit();
		ft_lstadd_back(&(export->env_lst), export->tmp_lst);
		export->env_count++;
		(void)*env++;
		free(div);
	}
}

void		add_env_var_list(t_export *export, char **args, int count)
{
	char **div;

	export->tmp_lst = NULL;

	div = div_at_equal(args[count]);
	if (!(export->tmp_lst = ft_lstnew(ft_lstnew_ms(args[count], div[0], div[1]))))
		put_error_exit();
	ft_lstadd_back(&(export->env_lst_front), export->tmp_lst);
	export->env_count++;
	free(div);
}
