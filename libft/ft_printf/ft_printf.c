/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 10:18:36 by hklein            #+#    #+#             */
/*   Updated: 2019/01/30 20:47:13 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	wr_str(char c, size_t len, size_t ind, t_stock *s)
{
	size_t	i;

	i = 0;
	while (ind + s->s_i < BUF_SIZE && i < len)
	{
		s->end_str[s->s_i + ind] = c;
		s->s_i += (ind ? 0 : 1);
		s->len_end++;
		i++;
	}
	if (ind + s->s_i >= BUF_SIZE)
	{
		write(1, s->end_str, BUF_SIZE);
		ft_bzero(s->end_str, BUF_SIZE);
		s->s_i = 0;
		s->flsh++;
		wr_str(c, len - i, ind, s);
	}
	return (i);
}

int		parseformat(const char *format, t_stock *s)
{
	int		i;

	i = 0;
	while (format[i])
	{
		if (format[i] == '{')
		{
			if (format_color((char*)&format[i + 1], s))
				i += s->offset;
			else
				wr_str(format[i++], 1, 0, s);
			reset_stock(s);
		}
		else if (format[i] == '%')
		{
			if (check_option((char*)&format[i + 1], s))
				return (1);
			i += s->offset;
			reset_stock(s);
		}
		else
			wr_str(format[i++], (*format ? 1 : 0), 0, s);
	}
	return (0);
}

int		ft_printf(const char *format, ...)
{
	t_stock		*s;
	size_t		l_e;

	s = init_stock();
	if (s == NULL)
	{
		free(s);
		return (-1);
	}
	va_start(s->ap, format);
	if (parseformat(format, s))
	{
		free(s);
		return (-1);
	}
	if (s->col)
		format_color("eoc}", s);
	write(1, s->end_str, s->len_end - (s->flsh * BUF_SIZE));
	va_end(s->ap);
	l_e = s->len_end;
	free(s);
	return (l_e);
}
