/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_export_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 21:07:26 by dogata            #+#    #+#             */
/*   Updated: 2021/04/25 00:24:40 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*convert_new_str(char *new_str)
{
	int		i;
	int		j;
	char	*return_str;

	i = 0;
	j = 0;
	return_str = malloc(sizeof(char) * (ft_strlen(new_str) * 2));
	if (return_str == NULL)
		put_error_exit(NULL);
	while (new_str[i])
	{
		if (new_str[i] == '\"' || new_str[i] == '$' || \
										new_str[i] == '`' || new_str[i] == '\\')
		{
			return_str[j++] = '\\';
			return_str[j] = new_str[i];
		}
		else
			return_str[j] = new_str[i];
		i++;
		j++;
	}
	return_str[j] = '\0';
	return (return_str);
}

char	*convert_new_str_for_escape_sequence(char *new_str)
{
	char	*return_str;

	if (ft_strchr(new_str, '\\') || ft_strchr(new_str, '\"') || \
						ft_strchr(new_str, '$') || ft_strchr(new_str, '`'))
		return_str = convert_new_str(new_str);
	else
	{
		return_str = ft_strdup(new_str);
		if (return_str == NULL)
			put_error_exit(NULL);
	}
	return (return_str);
}
