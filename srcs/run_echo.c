#include "../include/minishell.h"

int		run_echo(str_list *list)
{
	str_list	*current_list;
	int			n_flag;

	current_list = list->next;
	if (list->new_str && !ft_strcmp(current_list->new_str, "-n"))
		n_flag = 1;
	else
		n_flag = 0;
	if (n_flag)
		current_list = current_list->next;
	while (current_list != NULL)
	{
		printf("%s", current_list->new_str);
		if (current_list->next != NULL)
			printf(" ");
		current_list = current_list->next;
	}
	if (!n_flag)
		printf("\n");
	return (1);
}
