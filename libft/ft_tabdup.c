/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 15:46:38 by hklein            #+#    #+#             */
/*   Updated: 2019/01/28 15:53:30 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		*ft_tabdup(int *tab, int size)
{
	int		*buf;
	int		i;

	i = -1;
	if (!(buf = (int*)malloc(sizeof(int) * size)))
		return (0);
	while (i++ < size)
		buf[i] = tab[i];
	return (buf);
}
