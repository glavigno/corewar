/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 19:32:07 by hklein            #+#    #+#             */
/*   Updated: 2018/11/08 19:32:12 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void*, size_t))
{
	t_list	*tmp_node;

	tmp_node = *alst;
	while (tmp_node)
	{
		*alst = (*alst)->next;
		ft_lstdelone(&tmp_node, del);
		tmp_node = *alst;
	}
}
