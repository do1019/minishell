/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 05:16:32 by dogata            #+#    #+#             */
/*   Updated: 2020/07/14 16:27:36 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digit(int n)
{
	size_t digit;

	digit = 0;
	while (n)
	{
		n /= 10;
		digit++;
	}
	return (digit);
}

void		ft_putnbr_fd(int n, int fd)
{
	char	nbr[11];
	int		rem;
	int		digit;

	if (n == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else if (n == 0)
		ft_putstr_fd("0", fd);
	else
	{
		if (n < 0)
		{
			ft_putchar_fd('-', fd);
			n *= -1;
		}
		digit = count_digit(n);
		nbr[digit] = '\0';
		while (digit)
		{
			rem = n % 10;
			nbr[--digit] = rem + 48;
			n /= 10;
		}
		ft_putstr_fd(nbr, fd);
	}
}
