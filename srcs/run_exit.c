#include "../include/minishell.h"

int		run_exit(str_list *list)
{
	printf("%s\n", list->new_str);
	return (0);
}
