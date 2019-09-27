/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_set_res.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 17:01:30 by hklein            #+#    #+#             */
/*   Updated: 2019/02/08 17:54:24 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	concat_var(t_stock *s)
{
	if (s->t == 'd')
		return (ft_lltoa_base_pf(s->var_i, 10, s));
	if (s->t == 'b')
		return (ft_lltoa_base_pf(s->var_i, 2, s));
	if (s->t == 's' || s->t == 'c' || s->t == '%' || s->t == 'C' || s->t == 'N')
		return (format_str_c_mod(s));
	if (s->t == 'p')
		return (ft_utoa_base_pf(s->var_ui, 16, s));
	if (s->t == 'o')
		return (ft_utoa_base_pf(s->var_ui, 8, s));
	if (s->t == 'u' || s->t == 'U')
		return (ft_utoa_base_pf(s->var_ui, 10, s));
	if (s->t == 'x' || s->t == 'X')
		return (ft_utoa_base_pf(s->var_ui, 16, s));
	if (s->t == 'f' || s->t == 'e' || s->t == 'F')
		format_floats(s);
	return (0);
}

size_t	s_ver(t_stock *s, int v)
{
	size_t	i;

	i = 0;
	if (v == 1)
		i = ((s->t == 'd' && s->var_i >= 0) || ((s->t == 'f' || s->t == 'F')
				&& s->var_f >= 0) ? s->op_pl + s->op_sp : 0);
	if (v == 2)
		i = ((s->t == 'p' || ((s->t == 'x' || s->t == 'X')
				&& s->op_ha)) ? 2 : 0);
	if (v == 3)
		i = ((s->t == 'd' && s->var_i < 0) || ((s->t == 'f' || s->t == 'F')
				&& s->var_f < 0) ? 1 : 0);
	if (v == 4)
		i = (s->t == 's' && s->p < s->len_res ? 1 : 0);
	if (v == 5)
		i = (s->t == 'o' && s->op_ha && ((s->pr_x && !s->var_ui)
				|| s->var_ui) ? 1 : 0);
	if (v == 6)
		i = (s->pr_x && s->var_i == 0 && s->t != 'f' && s->t != 'e'
				&& s->t != 'F' && s->var_ui == 0 ? 0 : 1);
	if (v == 7)
		i = (s->var_c == 'l' || s->var_c == 'h' || s->var_c == 'z' ? 1 : 0);
	return (i);
}

int		set_res(t_stock *s)
{
	if (get_var(s))
		return (1);
	if (s->t == 's' || s->t == 'c' || s->t == '%' || s->t == 'C' || s->t == 'N')
	{
		if (format_res_str_c_mod(s))
			return (1);
	}
	else if (s->t != 'n')
	{
		if (format_res_num(s))
			return (1);
	}
	return (0);
}
