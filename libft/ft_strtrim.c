/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 14:53:07 by dogata            #+#    #+#             */
/*   Updated: 2020/07/14 00:14:18 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*search(char const *str, char const *set)
{
	size_t	strcnt;
	size_t	setcnt;

	strcnt = 0;
	setcnt = 0;
	while (str[strcnt] != '\0' && set[setcnt] != '\0')
	{
		if (str[strcnt] != set[setcnt])
			setcnt++;
		else
		{
			strcnt++;
			setcnt = 0;
		}
	}
	return ((char*)str + strcnt);
}

static char	*search_first(char const *str, char const *set)
{
	char *ans;

	ans = search(str, set);
	if (*ans == '\0')
		return (NULL);
	return (ans);
}

static char	*search_last(char const *str, char const *set)
{
	char *tmp;
	char *ans;

	while (*str != '\0')
	{
		tmp = search(str, set);
		if (*tmp != '\0')
			ans = tmp;
		str++;
	}
	return (ans);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	char	*first;
	char	*last;
	char	*trmstr;
	size_t	trmstrlen;
	size_t	count;

	if (s1 == NULL)
		return (NULL);
	count = 0;
	first = search_first(s1, set);
	if (first == NULL)
		return (ft_strdup(""));
	last = search_last(s1, set);
	trmstrlen = (last - first) + 2;
	if (!(trmstr = (char *)ft_calloc(trmstrlen, sizeof(char))))
		return (NULL);
	while (trmstrlen != 1)
	{
		trmstr[count] = first[count];
		count++;
		trmstrlen--;
	}
	trmstr[count] = '\0';
	return (trmstr);
}
