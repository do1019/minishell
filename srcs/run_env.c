/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 18:07:11 by hikeda            #+#    #+#             */
/*   Updated: 2021/04/28 21:20:26 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	run_env(t_args *list)
{
	extern char	**environ;
	char		*rt;
	bool		check_flag;
	int			i;

	check_flag = false;
	i = -1;
	while (environ[++i] != NULL)
	{
		if (ft_strchr(environ[i], '='))
		{
			if (ft_memcmp(environ[i], "OLDPWD=", 8) && !check_flag)
			{
				check_flag = true;
				rt = getenv("PWD");
				if (rt == NULL)
					continue ;
				if (!ft_memcmp(rt, "", 1))
					continue ;
			}
			write(list->fd_out, environ[i], ft_strlen(environ[i]));
			write(list->fd_out, "\n", 1);
		}
	}
	return (0);
}
