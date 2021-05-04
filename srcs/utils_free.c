/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 15:10:57 by dogata            #+#    #+#             */
/*   Updated: 2021/04/28 20:33:12 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	free_od_array(char **array, int rt)
{
	if (array)
	{
		free(*array);
		*array = NULL;
	}
	return (rt);
}

int	free_td_array(char ***array, int rt)
{
	char	**tmp;

	if (*array)
	{
		tmp = *array;
		while (**array != NULL)
		{
			free(**array);
			**array = NULL;
			(*array)++;
		}
		free(tmp);
		tmp = NULL;
	}
	return (rt);
}
