/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_colors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 18:29:09 by hklein            #+#    #+#             */
/*   Updated: 2019/02/18 15:05:00 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	color_offset(t_stock *s)
{
	s->offset = (s->col == 31 || s->col == 0 ? 5 : s->offset);
	s->offset = (s->col == 34 || s->col == 36 ? 6 : s->offset);
	s->offset = (s->col == 32 ? 7 : s->offset);
	s->offset = (s->col == 33 ? 8 : s->offset);
	s->offset = (s->col == 35 ? 9 : s->offset);
}

int		format_color(char *format_mod, t_stock *s)
{
	if (!ft_strncmp(format_mod, "red}", 4))
		s->col = 31;
	else if (!ft_strncmp(format_mod, "green}", 6))
		s->col = 32;
	else if (!ft_strncmp(format_mod, "yellow}", 7))
		s->col = 33;
	else if (!ft_strncmp(format_mod, "blue}", 5))
		s->col = 34;
	else if (!ft_strncmp(format_mod, "magenta}", 8))
		s->col = 35;
	else if (!ft_strncmp(format_mod, "cyan}", 5))
		s->col = 36;
	else if (!ft_strncmp(format_mod, "eoc}", 4))
		s->col = 0;
	else
		return (0);
	wr_str('\033', 1, 0, s);
	wr_str('[', 1, 0, s);
	ft_lltoa_base_pf(s->col, 10, s);
	wr_str('m', 1, 0, s);
	color_offset(s);
	return (1);
}
