/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 03:35:45 by dogata            #+#    #+#             */
/*   Updated: 2020/07/13 12:02:29 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*cstr;
	size_t	s1len;
	size_t	s2len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	cstr = (char *)ft_calloc(s1len + s2len + 1, sizeof(char));
	if (cstr == NULL)
		return (NULL);
	ft_memcpy(cstr, s1, s1len);
	ft_strlcat(cstr, s2, s1len + s2len + 1);
	return (cstr);
}
