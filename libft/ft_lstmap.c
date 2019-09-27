/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 17:19:21 by hklein            #+#    #+#             */
/*   Updated: 2018/11/09 12:24:51 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*end;

	if (lst && f)
	{
		if (!(new = f(ft_lstnew(lst->content, lst->content_size))))
			return (NULL);
		end = new;
		lst = lst->next;
		while (lst)
		{
			if (!(new->next = f(ft_lstnew(lst->content, lst->content_size))))
				return (NULL);
			lst = lst->next;
			new = new->next;
		}
		return (end);
	}
	else
		return (NULL);
}
