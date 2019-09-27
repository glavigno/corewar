/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 14:28:04 by hklein            #+#    #+#             */
/*   Updated: 2019/02/18 15:49:09 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		check_flag_2(char *f, t_stock *s)
{
	s->var_c = (s->t == 'N' ? f[0] : s->var_c);
	while (s->t == 'N' && s_ver(s, 7))
	{
		f++;
		s->var_c = f[0];
		s->offset++;
	}
	return (set_res(s));
}

int		check_flag(char *f, t_stock *s)
{
	s->t = (f[0] == 'd' || f[0] == 'i' || f[0] == 'D' ? 'd' : s->t);
	s->t = (f[0] == 's' ? 's' : s->t);
	s->t = (f[0] == 'c' ? 'c' : s->t);
	s->t = (f[0] == 'p' ? 'p' : s->t);
	s->t = (f[0] == '%' ? '%' : s->t);
	s->t = (f[0] == 'b' ? 'b' : s->t);
	s->t = (f[0] == 'o' || f[0] == 'O' ? 'o' : s->t);
	s->t = (f[0] == 'u' ? 'u' : s->t);
	s->t = (f[0] == 'U' ? 'U' : s->t);
	s->t = (f[0] == 'x' ? 'x' : s->t);
	s->t = (f[0] == 'X' ? 'X' : s->t);
	s->t = (f[0] == 'f' ? 'f' : s->t);
	s->t = (f[0] == 'e' ? 'e' : s->t);
	s->t = (f[0] == 'F' ? 'F' : s->t);
	s->t = (f[0] == 'C' ? 'C' : s->t);
	s->t = (f[0] == 'n' ? 'n' : s->t);
	s->t = (s->t == 'c' && s->si == 4 ? 'C' : s->t);
	s->si = (s->si < 8 && (s->t == 'f' || s->t == 'e'
				|| s->t == 'F') ? 7 : s->si);
	s->si = (s->t == 'U' || f[0] == 'D' || f[0] == 'O' ? 4 : s->si);
	s->offset += (f[0] ? 2 : 1);
	return (check_flag_2(f, s));
}

int		check_size(char *f, t_stock *s)
{
	s->si = (f[0] == 'h' && f[1] == 'h' ? 1 : s->si);
	s->si = (f[0] == 'h' && s->si != 1 ? 2 : s->si);
	s->si = (f[0] == 'l' && f[1] == 'l' ? 3 : s->si);
	s->si = (f[0] == 'l' && s->si != 3 ? 4 : s->si);
	s->si = (f[0] == 'j' ? 5 : s->si);
	s->si = (f[0] == 'z' ? 6 : s->si);
	s->si = (f[0] == 'L' ? 8 : s->si);
	s->offset += (s->si == 1 || s->si == 3 ? 2 : 0);
	s->offset += (s->si != 1 && s->si != 3 && s->si ? 1 : 0);
	f += (s->si == 1 || s->si == 3 ? 2 : 0);
	f += (s->si != 1 && s->si != 3 && s->si ? 1 : 0);
	return (check_flag(f, s));
}

int		check_width_prec(char *f, t_stock *s)
{
	int		j;

	j = -1;
	while (ft_isdigit(f[++j]))
		s->w = s->w * 10 + (f[j] - '0');
	j = (f[0] == '*' ? va_arg(s->ap, int) : j);
	s->op_mi = (f[0] == '*' && j < 0 ? 1 : s->op_mi);
	j *= (f[0] == '*' && j < 0 ? -1 : 1);
	s->w = (f[0] == '*' && j > 0 ? j : s->w);
	s->offset += (f[0] == '*' ? 1 : j);
	f += (f[0] == '*' ? 1 : j);
	if (f[0] == '.')
	{
		f++;
		j = -1;
		while (ft_isdigit(f[++j]))
			s->p = s->p * 10 + (f[j] - '0');
		j = (f[0] == '*' ? va_arg(s->ap, int) : j);
		s->pr_x = ((j == 0) || (f[0] == '0' && j == 1) ? 1 : 0);
		j *= (f[0] == '*' && j < 0 ? 0 : 1);
		s->p = (f[0] == '*' && j > 0 ? j : s->p);
		s->offset += 1 + (f[0] == '*' ? 1 : j);
		f += (f[0] == '*' ? 1 : j);
	}
	return (check_size(f, s));
}

int		check_option(char *f, t_stock *s)
{
	while (*f == '-' || *f == '+' || *f == '#'
			|| *f == '0' || *f == ' ')
	{
		s->op_mi = (f[0] == '-' ? 1 : s->op_mi);
		s->op_pl = (f[0] == '+' ? 1 : s->op_pl);
		s->op_ha = (f[0] == '#' ? 1 : s->op_ha);
		s->op_ze = (f[0] == '0' ? 1 : s->op_ze);
		s->op_sp = (f[0] == ' ' ? 1 : s->op_sp);
		s->offset += 1;
		f++;
	}
	if (s->op_ze && s->op_mi)
		s->op_ze = 0;
	if (s->op_pl && s->op_sp)
		s->op_sp = 0;
	return (check_width_prec(f, s));
}
