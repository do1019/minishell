/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_argv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 15:04:48 by hikeda            #+#    #+#             */
/*   Updated: 2021/04/20 20:04:23 by hikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_redirect_command(char *str, int i)
{
	if (!ft_strncmp(str + i, "1>>", 3) || !ft_strncmp(str + i, "2>>", 3))
		return (3);
	else if (!ft_strncmp(str + i, ">>", 2) || !ft_strncmp(str + i, "1>", 2)
		|| !ft_strncmp(str + i, "2>", 2))
		return (2);
	else if (!ft_strncmp(str + i, ">", 1) || !ft_strncmp(str + i, "<", 1))
		return (1);
	return (0);
}

void	create_argv4(t_args *list, t_args *ptr, int flag, int i)
{
	if (flag == 1)
	{
		list->argv[list->argc] = ft_strndup(ptr->new_str + i, 1);
		if (list->argv[list->argc++] == NULL)
			put_error_exit(NULL);
	}
	else if (flag == 2)
	{
		list->argv[list->argc] = ft_strndup(ptr->new_str + i, 2);
		if (list->argv[list->argc++] == NULL)
			put_error_exit(NULL);
	}
	else if (flag == 3)
	{
		list->argv[list->argc] = ft_strndup(ptr->new_str + i, 3);
		if (list->argv[list->argc++] == NULL)
			put_error_exit(NULL);
	}
}

void	create_argv3(t_args *list, t_args *ptr, int i, int j)
{
	int		flag;
	int		count;

	count = 0;
	while (ptr->new_str[i] != '\0')
	{
		flag = check_redirect_command(ptr->new_str, i);
		while (flag == 0 && ptr->new_str[i] != '\0')
			flag = check_redirect_command(ptr->new_str, ++i);
		if (i - count != 0)
		{
			list->argv[list->argc] = ft_strndup(ptr->new_str + j, i - j);
			if (list->argv[list->argc++] == NULL)
				put_error_exit(NULL);
		}
		if (flag > 0)
		{
			create_argv4(list, ptr, flag, i);
			i += flag;
		}
		count = i;
		j = i;
	}
}

void	create_argv2(t_args *list, t_args *ptr)
{
	int		i;
	int		count;
	int		flag;

	i = 0;
	count = 0;
	while (ptr->new_str[i] != '\0')
	{
		flag = check_redirect_command(ptr->new_str, i);
		while (flag == 0 && ptr->new_str[i] != '\0')
			flag = check_redirect_command(ptr->new_str, ++i);
		if (i - count != 0)
			list->argc++;
		if (flag > 0)
		{
			list->argc++;
			i += flag;
		}
		count = i;
	}
}

void	create_argv1(t_ms *ms, t_args *list)
{
	t_args	*ptr;

	ptr = list;
	while (ptr != NULL)
	{
		create_argv2(list, ptr);
		ptr = ptr->next;
	}
	ptr = list;
	list->argv = (char **)malloc(sizeof(char *) * (list->argc + 1));
	if (list->argv == NULL)
		put_error_exit(NULL);
	list->argc = 0;
	while (ptr != NULL)
	{
		create_argv3(list, ptr, 0, 0);
		ptr = ptr->next;
	}
	list->argv[list->argc] = NULL;
	list->red_num = ms->redirect_num;
	check_builtin_and_redirect_command(ms, list);
	if (ms->builtin_command_flag == true && list->red_err == 0)
		change_list(list, ptr, -1);
	else if (list->red_err == 0)
		change_argv(list, -1, 0, 1);
}
