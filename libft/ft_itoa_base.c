/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 17:48:11 by hklein            #+#    #+#             */
/*   Updated: 2018/12/15 19:08:23 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	converted_to_string(char **str, int j, int value, int base)
{
	(*str)[j--] = '\0';
	while (j >= 0)
	{
		if ((value % base) < 10)
		{
			(*str)[j] = value % base + '0';
			value = value / base;
		}
		else
		{
			(*str)[j] = value % base - 10 + 'A';
			value = value / base;
		}
		j--;
	}
}

char	*ft_itoa_base(int value, int base)
{
	int		buf;
	int		j;
	int		neg;
	char	*str;

	neg = 0;
	j = 2;
	if (value == -2147483648 && base == 10)
		return (ft_strdup("-2147483648"));
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
	if (!(str = (char*)malloc(sizeof(char) * j--)))
		return (NULL);
	converted_to_string(&str, j, value, base);
	(neg == 1 ? str[0] = '-' : str[0]);
	return (str);
}
