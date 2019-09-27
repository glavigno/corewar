/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_format_unicode.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <hklein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 17:34:05 by hklein            #+#    #+#             */
/*   Updated: 2019/05/02 14:05:34 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		wc_size(wchar_t c)
{
	if (c >= 0 && c <= 0x7f)
		return (1);
	else if (c >= 0x80 && c <= 0x7FF)
		return (2);
	else if (c >= 0x800 && c <= 0x3fff)
		return (3);
	else if (c >= 0x4000 && c <= 0x1fffff)
		return (4);
	return (0);
}

size_t	ze_for_len(size_t size)
{
	if (size == 1)
		return (7);
	if (size == 2)
		return (11);
	if (size == 3)
		return (16);
	if (size == 4)
		return (21);
	return (0);
}

void	bin_to_hex(char **bin, t_stock *s)
{
	unsigned char	h;
	int				i;
	int				p;

	p = 7;
	i = 0;
	h = 0x0;
	while (i < 8)
		h += ((*bin)[i++] - '0') * ft_int_pow(2, p--);
	ft_strdel(bin);
	wr_str(h, 1, 0, s);
}

char	*bin_str(size_t count, size_t size)
{
	if (count > 0)
		return (ft_strdup("10      "));
	if (size == 1)
		return (ft_strdup("0       "));
	if (size == 2)
		return (ft_strdup("110     "));
	if (size == 3)
		return (ft_strdup("1110    "));
	if (size == 4)
		return (ft_strdup("11110   "));
	return (0);
}

int		format_unicode(t_stock *s)
{
	int			size;
	size_t		len;
	size_t		i;
	char		*bit;

	if (!(bit = ft_itoa_base(s->var_c_u, 2)))
		return (1);
	size = wc_size(s->var_c_u);
	s->var_i = -1;
	len = ft_strlen(bit);
	s->var_f_p = 0;
	while (++s->var_i < size)
	{
		if (!(s->var_s = bin_str(s->var_i, size)))
			return (1);
		i = (!s->var_i && size > 1 ? size + 1 : size);
		i = (s->var_i ? 2 : i);
		while (i < 8 && ((int)(ze_for_len(size) - len++) > 0))
			s->var_s[i++] = '0';
		while (i < 8)
			s->var_s[i++] = bit[s->var_f_p++];
		bin_to_hex(&s->var_s, s);
	}
	ft_strdel(&bit);
	return (0);
}
