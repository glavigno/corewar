/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 13:26:15 by hklein            #+#    #+#             */
/*   Updated: 2019/02/18 15:48:30 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_atol(const char *str)
{
	int			a;
	long long	nb;
	int			b;

	a = 0;
	b = 0;
	nb = 0;
	while (str[a] == ' ' || str[a] == '\f' || str[a] == '\t'
			|| str[a] == '\n' || str[a] == '\r' || str[a] == '\v')
		a++;
	if (str[a] == '-')
		b = 1;
	if (str[a] == '-' || str[a] == '+')
		a++;
	while (str[a] >= '0' && str[a] <= '9')
		nb = nb * 10 + str[a++] - '0';
	if (b == 1)
		return (-nb);
	else
		return (nb);
	return (0);
}
