/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 19:10:04 by hklein            #+#    #+#             */
/*   Updated: 2019/01/24 21:59:55 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	converted_to_string(char **str, int j, unsigned long long int value,
		unsigned int base)
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
			(*str)[j] = value % base - 10 + 'a';
			value = value / base;
		}
		j--;
	}
}

char		*ft_utoa_base(unsigned long long int value, unsigned int base)
{
	unsigned long long int		buf;
	int							j;
	char						*str;

	j = 2;
	buf = value;
	while (buf /= base)
		j++;
	if (!(str = (char*)malloc(sizeof(char) * j--)))
		return (NULL);
	converted_to_string(&str, j, value, base);
	return (str);
}
