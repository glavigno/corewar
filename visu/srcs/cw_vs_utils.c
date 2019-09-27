/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_vs_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <hklein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 17:33:25 by hklein            #+#    #+#             */
/*   Updated: 2019/05/11 16:51:54 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

void	draw_plain_line(t_vs *vs, int height, int len)
{
	int	i;

	i = 0;
	while (++i < len)
		mvaddch(vs->starty + height, vs->startx + i, ' ');
	refresh();
}

void	draw_plain_col(t_vs *vs, int size, int x, int color)
{
	int	i;

	i = 0;
	attron(COLOR_PAIR(color));
	while (++i < size)
		mvaddch(vs->starty + i, x, ' ');
	attroff(COLOR_PAIR(color));
}

void	draw_plain_border(t_vs *vs, WINDOW *win, int color)
{
	int	i;
	int	row;
	int	col;

	i = 0;
	getmaxyx(win, row, col);
	attron(COLOR_PAIR(color));
	while (i < row)
	{
		if (!i || i == row - 1)
			draw_plain_line(vs, i, col);
		else
		{
			mvaddch(vs->starty + i, vs->startx + 1, ' ');
			mvaddch(vs->starty + i, vs->startx + col - 1, ' ');
		}
		i++;
	}
	attroff(COLOR_PAIR(color));
}

WINDOW	*create_newwin(int height, int width, int sty, int stx)
{
	WINDOW *local_win;

	local_win = newwin(height, width, sty, stx);
	return (local_win);
}
