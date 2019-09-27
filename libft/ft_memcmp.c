/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 19:43:14 by hklein            #+#    #+#             */
/*   Updated: 2018/11/09 14:22:14 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned int	i;
	unsigned char	a;
	unsigned char	b;

	if ((int)n <= 0)
		return (0);
	i = 0;
	while (((unsigned char*)s1)[i] == ((unsigned char*)s2)[i] && i < (n - 1))
		i++;
	a = ((unsigned char*)s1)[i];
	b = ((unsigned char*)s2)[i];
	return (a - b);
}
