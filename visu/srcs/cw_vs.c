/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_vs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <hklein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 17:32:09 by hklein            #+#    #+#             */
/*   Updated: 2019/05/11 16:51:45 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

void	set_players_color(t_cw *cw)
{
	int			nb;
	t_player	*tmp_player;

	tmp_player = cw->players;
	nb = 2;
	while (tmp_player)
	{
		tmp_player->color = nb++;
		tmp_player = tmp_player->next;
	}
}

void	start_vs_2(t_cw *cw, t_vs *vs)
{
	vs->starty = (LINES - MIN_WIN_H_) / 2;
	vs->startx = (COLS - MIN_WIN_W_) / 2;
	start_color();
	printw("Press ESC to exit");
	init_cw_colors();
	vs->main_win = create_newwin(MIN_WIN_H_, MIN_WIN_W_, vs->starty
			, vs->startx);
	draw_plain_border(vs, vs->main_win, VS_BORDER_COLOR_);
	draw_plain_col(vs, 67, vs->startx + 198, VS_BORDER_COLOR_);
	vs->logo_win = create_newwin(7, 45, vs->starty + 49, vs->startx + 203);
	vs->grid_win = create_newwin(10, 45, vs->starty + 57, vs->startx + 201);
	draw_logo(vs);
	set_players_color(cw);
	vs->live_win = create_newwin(7, 41, vs->starty + 40, vs->startx + 203);
	box(vs->live_win, 0, 0);
	wrefresh(vs->live_win);
	wrefresh(vs->grid_win);
	wrefresh(vs->logo_win);
}

t_vs	*start_vs(t_cw *cw)
{
	t_vs	*vs;

	if (!(vs = init_vs()))
		return (NULL);
	initscr();
	cbreak();
	timeout(0);
	keypad(stdscr, TRUE);
	getmaxyx(stdscr, vs->row, vs->col);
	if (vs->row < MIN_WIN_H_ || vs->col < MIN_WIN_W_)
	{
		mvprintw(vs->row / 2, (vs->col / 2) - 22
				, "Please resize your window up and/or zoom out");
		mvprintw(vs->row / 2 + 1, (vs->col / 2) - 11
				, "Type any key to exit");
		refresh();
		getchar();
		free(vs);
		endwin();
		return (NULL);
	}
	else
		start_vs_2(cw, vs);
	return (vs);
}

int		cw_vs(t_vs *vs, t_cw *cw, int screen)
{
	int		c;

	if (screen)
	{
		while ((c = update_cw_values(vs, &cw)))
		{
			if (c == 1)
			{
				endwin();
				return (1);
			}
		}
	}
	else
	{
		update_cw_values(vs, &cw);
		mvprintw(vs->starty + 38, vs->startx + 204, "Player %d (%s) has won !",
				cw->game->winner->nb_player, cw->game->winner->name);
		move(0, 0);
		c = 0;
		while (c != 27)
			c = getch();
		endwin();
	}
	return (0);
}
