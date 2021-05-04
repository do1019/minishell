/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 19:11:27 by dogata            #+#    #+#             */
/*   Updated: 2021/04/16 05:08:51 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*top_lst;

	if (!lst || !f)
		return (NULL);
	new_lst = ft_lstnew(f(lst->content));
	if (new_lst == NULL)
		return (NULL);
	top_lst = new_lst;
	while (lst->next != NULL)
	{
		lst = lst->next;
		new_lst->next = ft_lstnew(f(lst->content));
		if (new_lst->next == NULL)
		{
			ft_lstclear(&top_lst, del);
			return (NULL);
		}
		new_lst = new_lst->next;
	}
	return (top_lst);
}
