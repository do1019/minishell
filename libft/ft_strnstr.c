/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 14:18:01 by dogata            #+#    #+#             */
/*   Updated: 2020/07/19 17:52:12 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	llen;
	char	*first;

	llen = ft_strlen(little);
	if (llen == 0)
		return ((char*)big);
	first = ft_strchr(big, little[0]);
	while ((first != NULL) && ((first - big + llen) <= len))
	{
		if (!(ft_memcmp(first, little, llen)))
			return (first);
		else
			first = ft_strchr(first + 1, little[0]);
	}
	return (NULL);
}
