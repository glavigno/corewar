/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_var_op_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 16:40:08 by hklein            #+#    #+#             */
/*   Updated: 2019/02/08 17:57:53 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	check_max_wp_2(t_stock *s)
{
	s->len_res -= (s->t == 'd' && s->var_i < 0 ? 1 : 0);
	s->op_ha = ((s->t == 'x' || s->t == 'X') && s->op_ha
					&& !s->var_ui ? 0 : s->op_ha);
	s->op_ze = (s->op_ze && (s->p || s->pr_x) ? 0 : s->op_ze);
	s->len_res += ((s->t == 'o' || s->t == 'O') && s->var_ui
					&& s->p && s->op_ha ? 1 : 0);
	s->p = (s->p && s->p > s->len_res ? s->p - s->len_res : 0);
	s->len_res += s->p + s_ver(s, 1) + s_ver(s, 2) + s_ver(s, 3) + s_ver(s, 5);
	s->w = (s->w && s->w > s->len_res ? s->w - s->len_res : 0);
}

void	check_max_wp(t_stock *s)
{
	if (s->t == 'd' && s->var_i >= 0)
	{
		s->var_i = (s->si == 1 && s->var_i > 127 ? (char)s->var_i : s->var_i);
		s->var_i = (s->si == 2
						&& s->var_i > 32767 ? (short)s->var_i : s->var_i);
		s->len_res = ft_int_len(s->var_i);
	}
	else if (s->t == 'd' && s->var_i < 0)
	{
		s->var_i = (s->si == 1
						&& s->var_i < -128 ? (char)s->var_i : s->var_i);
		s->var_i = (s->si == 2
						&& s->var_i < -32768 ? (short)s->var_i : s->var_i);
		s->len_res = ft_int_len(s->var_i);
	}
	if (s->var_ui)
	{
		s->var_ui = (s->si == 1 && s->var_ui > 255 ? (unsigned char)s->var_ui
						: s->var_ui);
		s->var_ui = (s->si == 2 && s->var_ui > 65535 ? (unsigned short)s->var_ui
						: s->var_ui);
		s->len_res = ft_unsigned_len(s->var_ui, 0, s->t);
	}
	check_max_wp_2(s);
}
