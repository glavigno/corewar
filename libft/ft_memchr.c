/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 19:42:59 by hklein            #+#    #+#             */
/*   Updated: 2018/11/15 10:30:42 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	a;
	unsigned char	*b;

	i = 0;
	a = (unsigned char)c;
	b = (unsigned char*)s;
	while (i < n)
	{
		if (b[i] == a)
			return (&b[i]);
		i++;
	}
	return (0);
}
