/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_get_var.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 16:58:34 by hklein            #+#    #+#             */
/*   Updated: 2019/02/08 17:52:05 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		get_signed(t_stock *s)
{
	if (s->si < 3)
		s->var_i = va_arg(s->ap, int);
	else if (s->si == 3 || s->si == 6)
		s->var_i = va_arg(s->ap, long long);
	else if (s->si == 4)
		s->var_i = va_arg(s->ap, long);
	else if (s->si == 5)
		s->var_i = va_arg(s->ap, intmax_t);
	else if (s->si == 7)
		s->var_f = va_arg(s->ap, double);
	else if (s->si == 8)
		s->var_f = va_arg(s->ap, long double);
	s->len_res = (s->si < 7 ? ft_int_len(s->var_i) : s->len_res);
	if (s->si > 6)
		s->len_res = ft_int_len((long long)s->var_f)
			+ (!s->pr_x && !s->p ? 7 : 0) + (!s->pr_x && s->p ? s->p + 1 : 0);
	s->var_f_p = s->p;
	s->p = (s->t == 'f' || s->t == 'F' || s->t == 'e' ? 0 : s->p);
	return (0);
}

int		get_unsigned(t_stock *s)
{
	if (s->si < 3)
		s->var_ui = va_arg(s->ap, unsigned int);
	else if (s->si == 3)
		s->var_ui = va_arg(s->ap, unsigned long long);
	else if (s->si == 4)
		s->var_ui = va_arg(s->ap, unsigned long);
	else if (s->si == 5)
		s->var_ui = va_arg(s->ap, uintmax_t);
	else if (s->si == 6)
		s->var_ui = va_arg(s->ap, size_t);
	s->len_res = ft_unsigned_len(s->var_ui, 0, s->t);
	return (0);
}

int		get_char_string(t_stock *s, int i)
{
	if (i == 1)
	{
		s->var_c = va_arg(s->ap, int);
		s->len_res = 1;
	}
	else if (i == 2)
	{
		s->var_s = va_arg(s->ap, char*);
		s->len_res = (s->var_s == NULL ? 6 : ft_strlen(s->var_s));
	}
	else if (i == 3)
	{
		s->var_c_u = va_arg(s->ap, wchar_t);
		s->len_res = 4;
	}
	return (0);
}

int		get_ptr(t_stock *s)
{
	if (s->t == 'n')
	{
		s->n = va_arg(s->ap, int*);
		(*s->n) = (int)s->len_end;
	}
	else if (s->si < 3)
		s->var_ui = va_arg(s->ap, unsigned long long);
	else if (s->si == 3)
		s->var_ui = va_arg(s->ap, unsigned long long);
	else if (s->si == 4)
		s->var_ui = va_arg(s->ap, unsigned long);
	s->len_res = ft_unsigned_len(s->var_ui, 16, s->t);
	return (0);
}

int		get_var(t_stock *s)
{
	if (s->t == 'd' || s->t == 'f' || s->t == 'e' || s->t == 'F')
		return (get_signed(s));
	if (s->t == 'o' || s->t == 'u' || s->t == 'x'
			|| s->t == 'X' || s->t == 'U' || s->t == 'b')
		return (get_unsigned(s));
	if (s->t == 'c')
		return (get_char_string(s, 1));
	if (s->t == 's')
		return (get_char_string(s, 2));
	if (s->t == 'C')
		return (get_char_string(s, 3));
	if (s->t == 'p' || s->t == 'n')
		return (get_ptr(s));
	if (s->t == '%')
	{
		s->len_res = 1;
		return (0);
	}
	if (s->t == 'N')
		s->len_res = 1;
	return (0);
}
