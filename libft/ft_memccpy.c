/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 14:18:41 by dogata            #+#    #+#             */
/*   Updated: 2020/07/14 01:27:06 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char		*dest2;
	const unsigned char	*src2;
	unsigned char		cmp;

	dest2 = dest;
	src2 = src;
	cmp = c;
	while (n != 0)
	{
		if (*src2 == cmp)
		{
			*dest2 = *src2;
			dest2++;
			return (dest2);
		}
		*dest2 = *src2;
		dest2++;
		src2++;
		n--;
	}
	return (NULL);
}
