/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 18:49:37 by hklein            #+#    #+#             */
/*   Updated: 2019/02/18 15:48:20 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		a;
	int		nb;
	int		b;

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
