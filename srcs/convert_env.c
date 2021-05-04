/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 18:09:54 by hikeda            #+#    #+#             */
/*   Updated: 2021/04/18 20:06:18 by hikeda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	convert_env(t_ms *ms, char *environ, int e_posi, int env_strlen)
{
	int		i;
	int		j;
	int		ptr_len;
	char	*ptr;

	ptr = ms->new_line;
	ptr_len = ms->nlp + ft_strlen(ms->line + e_posi - 1) + ft_strlen(environ)
		- ((env_strlen + 1) * 2) + 1;
	ms->new_line = (char *)malloc(sizeof(char) * (ptr_len + 1));
	if (ms->new_line == NULL)
		put_error_exit(NULL);
	i = -1;
	while (++i < ms->nlp)
		ms->new_line[i] = ptr[i];
	j = -1;
	while (environ[env_strlen + ++j + 1] != '\0')
		ms->new_line[i + j] = environ[env_strlen + j + 1];
	ms->lp += env_strlen;
	ms->nlp += ft_strlen(environ) - env_strlen - 1;
	free(ptr);
}
