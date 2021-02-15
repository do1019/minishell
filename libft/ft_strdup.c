/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 18:22:40 by dogata            #+#    #+#             */
/*   Updated: 2020/08/03 11:32:18 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	size;
	char	*dup;

	size = ft_strlen(s);
	dup = (char*)ft_calloc(size + 1, sizeof(char));
	if (dup == NULL)
		return (NULL);
	dup = ft_memcpy(dup, s, size);
	dup[size] = '\0';
	return (dup);
}
