/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 10:39:52 by dogata            #+#    #+#             */
/*   Updated: 2021/04/16 05:02:27 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_atoll(const char *nptr)
{
	long long	num;
	int			mflag;

	num = 0;
	mflag = 1;
	while (*nptr == ' ' || *nptr == '\t' || *nptr == '\v' \
	|| *nptr == '\f' || *nptr == '\r' || *nptr == '\n')
		nptr++;
	if (*nptr == '-')
		mflag = -1;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	while ('0' <= *nptr && *nptr <= '9')
	{
		num += (*nptr - '0');
		nptr++;
		if ('0' <= *nptr && *nptr <= '9')
			num *= 10;
	}
	return (num * mflag);
}
