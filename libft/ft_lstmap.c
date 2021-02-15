/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dogata <dogata@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 19:11:27 by dogata            #+#    #+#             */
/*   Updated: 2020/07/13 13:41:08 by dogata           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *new_lst;
	t_list *top_lst;

	if (!lst || !f)
		return (NULL);
	if (!(new_lst = ft_lstnew(f(lst->content))))
		return (NULL);
	top_lst = new_lst;
	while (lst->next != NULL)
	{
		lst = lst->next;
		if (!(new_lst->next = ft_lstnew(f(lst->content))))
		{
			ft_lstclear(&top_lst, del);
			return (NULL);
		}
		new_lst = new_lst->next;
	}
	return (top_lst);
}
