/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 18:40:24 by dogata            #+#    #+#             */
/*   Updated: 2020/07/17 16:47:37 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_array(char const *s, char c)
{
	int		flag;
	int		array;

	flag = 0;
	array = 0;
	while (*s != '\0')
	{
		while (*s == c && *s != '\0')
		{
			flag = 0;
			s++;
		}
		while (*s != c && *s != '\0')
		{
			if (!flag)
				flag = 1;
			s++;
		}
		if (flag)
			array++;
		flag = 0;
	}
	return (array);
}

static char	**free_memory(char **ans)
{
	int		array;

	array = 0;
	while (ans[array])
	{
		free(ans[array]);
		array++;
	}
	free(ans);
	return (NULL);
}

static char	*convert_to_null_character(char *s, char c, char *dest)
{
	int		count;

	count = 0;
	while (*s)
	{
		if (*s == c)
			dest[count] = '\0';
		else
			dest[count] = *s;
		s++;
		count++;
	}
	dest[count] = '\0';
	return (dest);
}

static char	**do_split(char const *s, char c, int array, int slen)
{
	char	**ans;
	char	*nulls;
	char	*tmp;
	int		count;

	count = array;
	if (!(ans = (char **)ft_calloc(array + 1, sizeof(char *))))
		return (NULL);
	array = 0;
	if (!(nulls = (char *)ft_calloc(slen + 1, sizeof(char))))
		return (free_memory(ans));
	nulls = convert_to_null_character((char *)s, c, nulls);
	tmp = nulls;
	while (count--)
	{
		while (*nulls == '\0')
			nulls++;
		if (!(ans[array++] = ft_substr(nulls, 0, ft_strlen(nulls))))
			return (free_memory(ans));
		while (*nulls != '\0')
			nulls++;
	}
	free(tmp);
	return (ans);
}

char		**ft_split(char const *s, char c)
{
	char	**ans;
	int		array;
	int		slen;

	if (!s)
		return (NULL);
	array = count_array(s, c);
	slen = ft_strlen(s);
	if (!(ans = do_split(s, c, array, slen)))
		return (NULL);
	ans[array] = NULL;
	return (ans);
}
