/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 00:01:53 by dogata            #+#    #+#             */
/*   Updated: 2021/02/16 00:01:55 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_free_strjoin(const char *s1, const char *s2)
{
	char	*cstr;
	size_t	s1len;
	size_t	s2len;
	int		count;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	if (!(cstr = malloc(sizeof(char) * (s1len + s2len + 1))))
	{
		free((char *)s1);
		return (NULL);
	}
	count = -1;
	while ((int)s1len > ++count)
		cstr[count] = s1[count];
	count = -1;
	while (((int)s1len + (int)s2len + 1) > ((int)s1len + ++count))
		cstr[(int)s1len + count] = s2[count];
	free((char *)s1);
	return (cstr);
}
