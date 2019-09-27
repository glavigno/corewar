/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_var_op.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 18:39:35 by hklein            #+#    #+#             */
/*   Updated: 2019/02/08 17:55:01 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_unsigned_len(unsigned long long x, unsigned int b, char type)
{
	size_t	i;

	if (!b)
	{
		b = (type == 'u' || type == 'U' ? 10 : b);
		b = (type == 'o' ? 8 : b);
		b = (type == 'x' || type == 'X' || type == 'p' ? 16 : b);
		b = (type == 'b' ? 2 : b);
	}
	i = 1;
	while (x /= b)
		i++;
	return (i);
}

void	converted_to_string_pf(long long j, long long v, int b, t_stock *s)
{
	while (j >= 0)
	{
		if ((v % b) < 10)
		{
			wr_str(v % b + '0', 1, j, s);
			v = v / b;
		}
		else
		{
			wr_str(v % b - 10 + 'a', 1, j, s);
			v = v / b;
		}
		j--;
	}
}

size_t	ft_lltoa_base_pf(long long v, int b, t_stock *s)
{
	size_t	j;

	if (v == -9223372036854775807 - 1 && b == 10)
	{
		j = ft_lltoa_base_pf(-922337203, b, s);
		return (j + ft_lltoa_base_pf(6854775808, b, s));
	}
	v *= (v < 0 && b == 10 ? -1 : 1);
	j = ft_int_len(v);
	converted_to_string_pf(j - 1, v, b, s);
	s->s_i += j - 1;
	return (j);
}

size_t	ft_utoa_base_pf(unsigned long long v, unsigned int b, t_stock *s)
{
	size_t	j;
	int		i;

	j = ft_unsigned_len(v, 0, s->t) - 1;
	i = (int)j;
	while (i >= 0)
	{
		if ((v % b) < 10)
		{
			wr_str(v % b + '0', 1, i, s);
			v = v / b;
		}
		else
		{
			wr_str((s->t == 'X' ? v % b - 10 + 'A' : v % b - 10
				+ 'a'), 1, i, s);
			v = v / b;
		}
		i--;
	}
	s->s_i += j;
	return (j);
}
