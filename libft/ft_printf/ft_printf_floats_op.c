/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_floats_op.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 18:32:32 by hklein            #+#    #+#             */
/*   Updated: 2019/02/04 19:13:08 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	format_floats_2(t_stock *s, size_t i, long long fra)
{
	(!s->pr_x ? wr_str('.', 1, 0, s) : s->pr_x);
	(!s->pr_x ? wr_str('0', s->var_f_p - ft_int_len(fra), 0, s) : s->pr_x);
	(!s->pr_x ? ft_lltoa_base_pf(fra, 10, s) : s->pr_x);
	(s->t == 'e' ? wr_str('e', 1, 0, s) : s->t);
	(s->t == 'e' ? wr_str('+', 1, 0, s) : s->t);
	(s->t == 'e' && i - 1 < 10 ? wr_str('0', 1, 0, s) : s->t);
	(s->t == 'e' ? ft_lltoa_base_pf((int)i - 1, 10, s) : s->t);
}

void	format_floats(t_stock *s)
{
	long long	dec;
	long long	fra;
	size_t		i;
	size_t		j;

	j = 1;
	i = 0;
	s->var_f *= (s->var_f < 0 ? -1 : 1);
	s->var_f_p = (!s->var_f_p ? 6 : s->var_f_p);
	if (s->t == 'e')
	{
		if ((i = ft_int_len((long long)s->var_f)) > 1)
		{
			while (j++ < i)
				s->var_f /= 10;
		}
	}
	dec = (long long)s->var_f;
	fra = (s->var_f - dec) * ft_int_pow(10, s->var_f_p + 1);
	fra = (fra % 10 > 4 ? fra + 10 - (fra % 10) : fra - (fra % 10));
	fra /= 10;
	dec += (s->pr_x && ((s->var_f - dec) * 10) > 4 ? 1 : 0);
	ft_lltoa_base_pf(dec, 10, s);
	format_floats_2(s, i, fra);
}
