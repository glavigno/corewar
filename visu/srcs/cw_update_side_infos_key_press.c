/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_update_side_infos_key_press.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <hklein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 17:02:46 by hklein            #+#    #+#             */
/*   Updated: 2019/05/11 16:51:14 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

void	update_players_values(t_vs *vs, t_cw *cw)
{
	int			offset;
	t_player	*tmp_player;

	offset = 0;
	tmp_player = cw->players;
	while (tmp_player)
	{
		mvprintw(vs->starty + VS_DECAL_ + 11 + offset, vs->startx + 202,
				"Player %d : ", tmp_player->nb_player);
		attron(COLOR_PAIR(tmp_player->color));
		printw("%.25s", tmp_player->name);
		attroff(COLOR_PAIR(tmp_player->color));
		mvprintw(vs->starty + VS_DECAL_ + 12 + offset, vs->startx + 204,
				"Last live : %-10d", tmp_player->last_live_cycle);
		mvprintw(vs->starty + VS_DECAL_ + 13 + offset, vs->startx + 204,
				"Lives in current period : %-10d",
				tmp_player->current_ctd_lives);
		offset += 4;
		tmp_player = tmp_player->next;
	}
}

void	update_side_infos(t_vs *vs, t_cw *cw)
{
	attron(COLOR_PAIR(7));
	mvprintw(vs->starty + VS_DECAL_ + 1, vs->startx + 202,
			"Cycles/second/limit : %d", CYCLE_DELTA);
	mvprintw(vs->starty + VS_DECAL_ + 3, vs->startx + 202,
			"Cycles to die : %7d", cw->game->ctd >= 0 ? cw->game->ctd : 0);
	mvprintw(vs->starty + VS_DECAL_ + 5, vs->startx + 202,
			"Cycle: %7d", cw->game->cycle);
	mvprintw(vs->starty + VS_DECAL_ + 7, vs->startx + 202,
			"Speed: %3.0f%%", (((float)1 - (float)((float)vs->speed
						/ (float)(VS_MAX_SPEED_ - VS_MIN_SPEED_)))) * 100);
	mvprintw(vs->starty + VS_DECAL_ + 9, vs->startx + 202,
			"Processes: %d", count_procs(cw));
	update_players_values(vs, cw);
	attroff(COLOR_PAIR(7));
}

int		deal_key_press_pause(t_vs *vs, t_cw **cw_beg, int c)
{
	if (vs->pause || c == 32 || c == 260)
	{
		if (!vs->pause && (c == 32 || c == 260))
			vs->pause = 1;
		else if (c == 260 && (*cw_beg)->saved_cycles_prec)
			*cw_beg = (*cw_beg)->saved_cycles_prec;
		else if (vs->pause == 2 && !((*cw_beg)->saved_cycles_next))
			vs->pause = 0;
		else if ((vs->pause == 2 || c == 261) && (*cw_beg)->saved_cycles_next)
			*cw_beg = (*cw_beg)->saved_cycles_next;
		else if (c == 32 && !((*cw_beg)->saved_cycles_next))
		{
			vs->pause = 0;
			timeout(0);
			return (0);
		}
		else if (c == 32 && (*cw_beg)->saved_cycles_next)
			vs->pause = 2;
		return (2);
	}
	return (0);
}

int		deal_key_press(t_vs *vs, t_cw **cw_beg)
{
	int			c;

	c = 0;
	if (vs->pause == 1)
		timeout(-1);
	else if (vs->pause == 2)
		timeout(0);
	c = getch();
	if (c == 27)
		return (1);
	if (c == 258)
	{
		if (vs->speed + 100 < VS_MAX_SPEED_)
			vs->speed += 100;
	}
	if (c == 259)
	{
		if (vs->speed - VS_MIN_SPEED_ >= 100)
			vs->speed -= 100;
	}
	c = deal_key_press_pause(vs, cw_beg, c);
	mvprintw(vs->starty + VS_DECAL_ - 1, vs->startx + 202,
			vs->pause == 1 ? "Paused" : "       ");
	usleep(vs->speed);
	return (c);
}
