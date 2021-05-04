/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 20:18:18 by hikeda            #+#    #+#             */
/*   Updated: 2021/04/30 11:37:00 by hikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

long	long	check_longlong_min_max(char *str, int i, int len, int flag)
{
	unsigned long long	num;
	unsigned long long	longlong_max;

	num = 0;
	longlong_max = 9223372036854775807;
	while (str[i] != '\0' && num <= longlong_max + 1)
	{
		if (str[i] == ' ')
		{
			i++;
			continue ;
		}
		num = num * 10 + (unsigned long long)(str[i] - 48);
		i++;
	}
	if (flag == -1 && i == len && num == longlong_max + 1)
		return (0);
	else if (flag == -1 && i == len && num <= longlong_max)
		return ((long long)num * (long long)flag);
	else if (i == len && num <= longlong_max)
		return ((long long)num);
	return (-1);
}

int	ft_atoi_minishell(char *str, int i, int len, int flag)
{
	long long	num;

	len = ft_strlen(str);
	while (str[i] == ' ')
		i++;
	if (str[i] == '-')
		flag = -1;
	if (!ft_isdigit(str[i]))
		i++;
	num = check_longlong_min_max(str, i, len, flag);
	if (num == -1)
		return ((int)num);
	while (num > 255)
		num = num % 256;
	return ((int)num);
}

int	check_str(char *str, int i)
{
	while (str[i] == ' ')
		i++;
	if (!(((str[i] == '+' || str[i] == '-') && ft_isdigit(str[i + 1]))
			|| ft_isdigit(str[i])))
		return (0);
	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (ft_isdigit(str[i]) && str[i] != '\0')
	{
		if (!ft_isdigit(str[i]) && str[i] != ' ')
			return (0);
		i++;
	}
	while (str[i] == ' ' && str[i] != '\0')
		i++;
	if (str[i] == '\0')
		return (1);
	return (0);
}

int	check_exit(char *str, int i, int j, int num)
{
	if (i == 0)
		return (0);
	else if (i >= 2 && check_str(str, 0))
	{
		ft_putstr_fd("\x1b[32mminishell: \x1b[mexit: too many arguments\n", 2);
		return (1);
	}
	else if (i == 1 && check_str(str, 0))
	{
		num = ft_atoi_minishell(str, 0, 0, 1);
		while (!ft_isdigit(str[j]) && str[j] != '\0')
			j++;
		if ((num != -1) || (num == -1
				&& (str[j - 1] == '-' && str[j] == '1' && str[j + 1] == '\0'))
			|| !ft_strcmp(str + j - 1, "-4294967297"))
			return (num);
	}
	ft_putstr_fd("\x1b[32mminishell: \x1b[mexit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	return (255);
}

int	run_exit(t_ms *ms, t_args *list)
{
	t_args	*ptr;
	int		hyphen;
	int		return_num;

	if (ms->pipeline_flag != true)
		ft_putendl_fd(list->new_str, list->fd_err);
	ptr = list;
	if (list->num > 1)
		ptr = ptr->next;
	hyphen = 0;
	if (!ft_strcmp(ptr->new_str, "--"))
	{
		if (ptr->next != NULL)
			ptr = ptr->next;
		hyphen = 1;
	}
	return_num = check_exit(ptr->new_str, list->num - hyphen - 1, 0, 0);
	if (list->num - hyphen > 2 && check_str(ptr->new_str, 0))
		return (1);
	free_exit(ms, list);
	exit(return_num);
}
