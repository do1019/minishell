/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 20:18:12 by dogata            #+#    #+#             */
/*   Updated: 2020/07/13 12:01:54 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sstr;
	size_t	slen;
	size_t	sslen;

	if (s == NULL)
		return (NULL);
	slen = ft_strlen(s);
	if (slen < start)
		return (ft_strdup(""));
	if ((slen - start) <= len)
		sslen = slen - start;
	else
		sslen = len;
	sstr = (char *)ft_calloc(sslen + 1, sizeof(char));
	if (sstr == NULL)
		return (NULL);
	sstr = ft_memmove(sstr, s + start, sslen);
	sstr[sslen] = '\0';
	return (sstr);
}
