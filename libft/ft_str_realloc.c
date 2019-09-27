/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_realloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 19:07:27 by hklein            #+#    #+#             */
/*   Updated: 2018/12/19 19:09:36 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str_realloc(char *ptr, size_t size)
{
	char	*new;

	if (!size && ptr)
	{
		if (!(new = (char *)malloc(1)))
			return (NULL);
		new[0] = '\0';
		ft_strdel(&ptr);
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
