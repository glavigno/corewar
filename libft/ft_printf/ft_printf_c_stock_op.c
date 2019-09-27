/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_t_stock_op.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 20:00:09 by hklein            #+#    #+#             */
/*   Updated: 2019/01/30 17:36:32 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		reset_stock(t_stock *s)
{
	s->op_sp = 0;
	s->op_pl = 0;
	s->op_ha = 0;
	s->op_ze = 0;
	s->op_mi = 0;
	s->t = 'N';
	s->w = 0;
	s->p = 0;
	s->si = 0;
	s->offset = 0;
	s->var_i = 0;
	s->var_ui = 0;
	s->len_res = 0;
	s->pr_x = 0;
	s->var_c = 0;
	s->var_c_u = 0;
	s->var_f = 0;
	s->var_f_p = 0;
	s->var_s = NULL;
	s->var_s_u = NULL;
}

t_stock		*init_stock(void)
{
	t_stock		*s;

	if (!(s = (t_stock*)malloc(sizeof(t_stock))))
		return (NULL);
	reset_stock(s);
	ft_bzero(s->end_str, BUF_SIZE);
	s->col = 0;
	s->s_i = 0;
	s->len_end = 0;
	s->flsh = 0;
	return (s);
}
