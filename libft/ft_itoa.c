/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 00:53:09 by dogata            #+#    #+#             */
/*   Updated: 2020/12/03 17:35:13 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*convert_itoa(int div, int strlen, char *str, int mflag)
{
	int		rem;

	if (mflag)
		div = div * -1;
	while (strlen)
	{
		rem = div % 10;
		div = div / 10;
		str[strlen - 1] = rem + 48;
		strlen--;
	}
	if (mflag)
		str[strlen] = '-';
	return (str);
}

char		*ft_itoa(int n)
{
	char	*str;
	int		div;
	int		strlen;
	int		mflag;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	strlen = 0;
	mflag = 0;
	if (n < 0)
	{
		mflag = 1;
		strlen = 1;
	}
	div = n;
	while (div != 0)
	{
		div = div / 10;
		strlen++;
	}
	if (!(str = ft_calloc(strlen + 1, sizeof(char))))
		return (NULL);
	return (convert_itoa(n, strlen, str, mflag));
}
