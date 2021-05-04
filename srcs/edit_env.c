/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 04:06:44 by dogata            #+#    #+#             */
/*   Updated: 2021/04/28 21:24:08 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strjoin_clip_equal(char *s1, char *s2)
{
	char	*tmp;
	char	*return_str;

	tmp = ft_strjoin(s1, "=");
	if (tmp == NULL)
		put_error_exit(NULL);
	return_str = ft_strjoin(tmp, s2);
	if (return_str == NULL)
		put_error_exit(NULL);
	free_od_array(&tmp, 0);
	return (return_str);
}

static	char	**allocate_memory_to_new_environ(int allocate_num)
{
	char	**new_environ;

	new_environ = malloc(sizeof(char *) * (allocate_num + 1));
	if (new_environ == NULL)
		put_error_exit(NULL);
	return (new_environ);
}

void	edit_environ(t_ms *ms, char *target_key, char *new_value)
{
	extern char	**environ;
	int			i;

	ms->new_environ = allocate_memory_to_new_environ(count_array(environ));
	i = -1;
	while (environ[++i] != NULL)
	{
		div_at_equal(ms, environ[i]);
		if (!ft_strncmp(ms->div[0], target_key, ft_strlen(target_key) + 1))
			ms->new_environ[i] = ft_strjoin_clip_equal(target_key, new_value);
		else
			ms->new_environ[i] = ft_strdup(environ[i]);
		if (ms->new_environ[i] == NULL)
			put_error_exit(NULL);
		free_td_array(&ms->div, 0);
	}
	ms->new_environ[i] = NULL;
	if (ms->edit_env_flag == true)
		free_td_array(&environ, 0);
	environ = ms->new_environ;
	ms->edit_env_flag = true;
}
