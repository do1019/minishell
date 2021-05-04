/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 02:24:28 by dogata            #+#    #+#             */
/*   Updated: 2021/04/16 05:01:24 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int chr)
{
	size_t	count;

	count = ft_strlen(str);
	count = count + 1;
	while (count != 0)
	{
		if (*(unsigned char *)str == (unsigned char)chr)
			return ((char *)str);
		str++;
		count--;
	}
	return (NULL);
}
