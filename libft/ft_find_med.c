/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_med.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 13:57:59 by hklein            #+#    #+#             */
/*   Updated: 2019/02/09 14:34:10 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_find_med(int *tab, int size)
{
	int		*buf;
	int		med;

	if (!(buf = ft_tabdup(tab, size)))
		return (0);
	ft_quicksort(&buf, 0, size - 1);
	if (size % 2)
		med = buf[size / 2];
	else
		med = (buf[(size / 2) - 1] + buf[size / 2]) / 2;
	return (med);
}
