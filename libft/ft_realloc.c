/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 15:23:21 by hklein            #+#    #+#             */
/*   Updated: 2018/12/19 19:05:18 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	char	*new;

	if (!size && ptr)
	{
		if (!(new = (char *)malloc(1)))
			return (NULL);
		ft_memdel(&ptr);
		return (new);
	}
	if (!(new = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	new[size] = '\0';
	if (ptr)
	{
		ft_strcpy(new, ptr);
		ft_strdel(&ptr);
	}
	return (new);
}
