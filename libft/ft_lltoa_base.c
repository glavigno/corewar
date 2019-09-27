/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 10:22:13 by hklein            #+#    #+#             */
/*   Updated: 2019/01/24 21:56:48 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	converted_to_string(char **s, int j, long long value, int base)
{
	(*s)[j--] = '\0';
	while (j >= 0)
	{
		if ((value % base) < 10)
		{
			(*s)[j] = value % base + '0';
			value = value / base;
		}
		else
		{
			(*s)[j] = value % base - 10 + 'a';
			value = value / base;
		}
		j--;
	}
}

char		*ft_lltoa_base(long long value, int base)
{
	long long	buf;
	int			j;
	int			neg;
	char		*s;

	if (value == -9223372036854775807 - 1 && base == 10)
		return (ft_strdup("-9223372036854775808"));
	neg = 0;
	j = 2;
	if (value < 0 && base == 10)
	{
		neg = 1;
		j++;
		value *= -1;
	}
	if (value < 0 && base != 10)
		value *= -1;
	buf = value;
	while (buf /= base)
		j++;
	if (!(s = (char*)malloc(sizeof(char) * j--)))
		return (NULL);
	converted_to_string(&s, j, value, base);
	(neg == 1 ? s[0] = '-' : s[0]);
	return (s);
}
