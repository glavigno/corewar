/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quicksort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 14:00:20 by hklein            #+#    #+#             */
/*   Updated: 2019/02/09 14:31:12 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		partition_qs(int **tab, int low, int high)
{
	int		i;
	int		j;
	int		pi;

	i = low - 1;
	j = low;
	pi = (*tab)[high];
	while (j < high)
	{
		if ((*tab)[j] <= pi)
		{
			i++;
			ft_intswap(&(*tab)[i], &(*tab)[j]);
		}
		j++;
	}
	ft_intswap(&(*tab)[high], &(*tab)[i + 1]);
	return (i + 1);
}

void	ft_quicksort(int **tab, int low, int high)
{
	int		pi;

	if (low < high)
	{
		pi = partition_qs(tab, low, high);
		ft_quicksort(tab, low, pi - 1);
		ft_quicksort(tab, pi + 1, high);
	}
}
