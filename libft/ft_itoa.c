/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 18:50:10 by hklein            #+#    #+#             */
/*   Updated: 2018/11/14 18:08:00 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_count(int n)
{
	int		i;

	if (n < 0)
	{
		i = 2;
		n *= -1;
	}
	else
		i = 1;
	if (n == 0)
		return (2);
	else
	{
		while (n > 0)
		{
			n = n / 10;
			i++;
		}
	}
	return (i);
}

char			*ft_itoa(int n)
{
	int		i;
	int		neg;
	char	*str;

	neg = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	i = ft_count(n);
	if (n < 0)
	{
		n *= -1;
		neg = 1;
	}
	if (!(str = (char*)malloc(sizeof(char) * i)))
		return (NULL);
	str[--i] = '\0';
	while (i--)
	{
		str[i] = n % 10 + '0';
		n /= 10;
	}
	if (neg == 1)
		str[0] = '-';
	return (str);
}
