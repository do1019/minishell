#include "../include/minishell.h"

void	init_list(str_list *list, int num)
{
	list->element = num;
	list->quote_flag = 0;
	list->quote_num = 0;
	list->env_flag = 0;
	list->redirect_flag = 0;
	list->old_str = NULL;
	list->new_str = NULL;
	list->pre_str = NULL;
	list->nex_str = NULL;
	list->argv = NULL;
	list->next = NULL;
}

void	duplicate_list(str_list *list, int num)
{
	str_list	*new_list;

	if (!(new_list = (str_list *)malloc(sizeof(str_list))))
		return ;
	init_list(new_list, num);
	list->next = new_list;
}

void	create_list(str_list *list, int argc)
{
	str_list	*current_list;
	int			i;

	current_list = list;
	i = 1;
	while (i < argc)
	{
		duplicate_list(current_list, i);
		current_list = current_list->next;
		i++;
	}
}
