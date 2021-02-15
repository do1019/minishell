/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 12:15:51 by dogata            #+#    #+#             */
/*   Updated: 2021/02/15 21:03:40 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(char *s1, char *s2)
{
	int count;

	count = 0;
	while ((s1[count] == s2[count]) && (s1[count] != '\0'))
		count++;
	if ((s1[count] == '\0') && (s2[count] == '\0'))
		return (0);
	return (s1[count] - s2[count]);
}
