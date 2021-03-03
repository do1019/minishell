#include "../include/minishell.h"

void	create_argv(t_ms *ms, str_list *list, str_list *redirect_list, int redirect_num)
{
	str_list	*current_list;
	int			i;

	current_list = list;
	if (!(redirect_list->argv = (char **)malloc(sizeof(char *) * (redirect_num))))
		return ;
	i = -1;
	while (++i < redirect_num)
		redirect_list->argv[i] = NULL;
	i = -1;
	while (++i < redirect_num - 1)
	{
		redirect_list->argv[i] = ft_strdup(current_list->new_str);
		current_list = current_list->next;
	}
	ms->redirect_flag = true;
}

void    create_pre_nex_str(str_list *list)
{
	str_list    *current_list;
	str_list    *next_list;

	current_list = list;
	next_list = list->next;
	while (next_list != NULL)
	{
		current_list->nex_str=next_list->new_str;
		next_list->pre_str = current_list->new_str;
		current_list = current_list->next;
		next_list = next_list->next;
	}
}

void	convert_str(str_list *list, char c)
{
	int		i;
	int		j;
	char	*ptr;

	i = -1;
	j = 0;
	while (list->old_str[++i] != '\0')
	{
		if (list->old_str[i] != c)
			j++;
	}
	list->quote_num = i - j;
	if (!(ptr = (char *)malloc(sizeof(char) * (j + 1))))
		return ;
	i = -1;
	j = 0;
	while (list->old_str[++i] != '\0')
	{
		if (list->old_str[i] != c)
			ptr[j++] = list->old_str[i];
	}
	ptr[j] = '\0';
	list->new_str = ptr;
}

void	check_args(str_list *list, char *args)
{
	if (args[0] == '\'' && args[ft_strlen(args) - 1] == '\'')
		list->quote_flag = 1;
	else if (args[0] == '\"' && args[ft_strlen(args) - 1]== '\"')
		list->quote_flag = 2;
	else if (args[0] == '>' && args[1] == '\0')
		list->redirect_flag = 1;
	else if (args[0] == '>' && args[1] == '>' && args[2] == '\0')
		list->redirect_flag = 2;
	else if (args[0] == '<' && args[1] == '\0')
		list->redirect_flag = 3;
	list->old_str = args;
	if (list->quote_flag == 1)
		convert_str(list, '\'');
	else if (list->quote_flag == 2)
		convert_str(list, '\"');
	else
		convert_str(list, '\0');
	if (list->quote_flag != 1)
		prepare_check_env(list);
	//printf("old_str : %s, new_str : %s, pre_str : %s, nex_str : %s\nelement : %d, q_flag : %d, q_num : %d, e_flag : %d, re_flag : %d\n\n", list->old_str, list->new_str, list->pre_str, list->nex_str, list->element, list->quote_flag, list->quote_num, list->env_flag, list->redirect_flag);
}

void	parse_args(t_ms *ms, str_list *list, char **args)
{
	str_list	*current_list;
	int			argc;
	int			i;

	argc = 0;
	while (args[argc])
		argc++;
	init_list(list, 0);
	create_list(list, argc);
	current_list = list;
	i = -1;
	while (++i < argc)
	{
		check_args(current_list, args[i]);
		current_list = current_list->next;
	}
	create_pre_nex_str(list);
	current_list = list;
	while (current_list != NULL)
	{
		if (current_list->redirect_flag != 0)
			create_argv(ms, list, current_list, current_list->element + 1);
		/*if (current_list->redirect_flag == 1 || current_list->redirect_flag == 2)
			run_input_redirect(current_list);
		else if (current_list->redirect_flag == 3)
			run_output_redirect(current_list);*/
		current_list = current_list->next;
	}
}
