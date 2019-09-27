/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_format_var.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 18:38:27 by hklein            #+#    #+#             */
/*   Updated: 2019/02/04 10:52:31 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	format_str_c_mod(t_stock *s)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (s->t == 'c' || s->t == '%')
		wr_str((s->t == 'c' ? s->var_c : '%'), 1, 0, s);
	else if (s->t == 's')
	{
		s->var_s = (s->t == 's' && s->var_s == NULL ? "(null)" : s->var_s);
		i = (s->pr_x || (s->p && s->p < s->len_res) ? s->p : s->len_res);
		j = 0;
		while (j < i)
			wr_str(s->var_s[j++], 1, 0, s);
	}
	else if (s->t == 'C')
	{
		if (format_unicode(s))
			return (1);
	}
	else if (s->t == 'N')
	{
		if (s->var_c != 0 && !s_ver(s, 7))
			wr_str(s->var_c, 1, 0, s);
	}
	return (0);
}

int		format_res_str_c_mod(t_stock *s)
{
	if (s->w > s->len_res || (s->p && s->w > s->p) || (s->pr_x && s->w))
		s->w = s->w - ((s->p || s->pr_x) && s_ver(s, 4) ? s->p : s->len_res);
	else
		s->w = 0;
	if (!s->op_mi && s->w)
		wr_str((s->op_ze ? '0' : ' '), s->w, 0, s);
	if (concat_var(s))
		return (1);
	if (s->op_mi && s->w)
		wr_str(' ', s->w, 0, s);
	return (0);
}

int		format_res_num(t_stock *s)
{
	check_max_wp(s);
	if (!s->op_mi && !s->op_ze && s->w)
		wr_str(' ', s->w, 0, s);
	if (s_ver(s, 1))
		wr_str((s->op_pl ? '+' : ' '), 1, 0, s);
	if (s_ver(s, 3))
		wr_str('-', 1, 0, s);
	if (s_ver(s, 2) || s_ver(s, 5))
	{
		wr_str('0', 1, 0, s);
		wr_str((s->t == 'x' || s->t == 'p' ? 'x' : 'X'),
			(s_ver(s, 5) ? 0 : 1), 0, s);
	}
	if (s->op_ze)
		wr_str((s->op_ze ? '0' : ' '), s->w, 0, s);
	if (s->p)
		wr_str('0', s->p, 0, s);
	if (s_ver(s, 6))
		concat_var(s);
	if (s->pr_x && s->w && s->t != 'f' && s->var_ui == 0 && s->var_i == 0)
		wr_str(' ', 1, 0, s);
	if (s->op_mi && s->w)
		wr_str(' ', s->w, 0, s);
	return (0);
}
