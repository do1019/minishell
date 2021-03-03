/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 16:35:16 by dogata            #+#    #+#             */
/*   Updated: 2020/07/14 00:15:37 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int chr)
{
	size_t len;

	len = ft_strlen(str);
	while ((len + 1) != 0)
	{
		if ((unsigned char)str[len] == (unsigned char)chr)
		{
			return ((char*)str + len);
		}
		len--;
	}
	return (NULL);
}
