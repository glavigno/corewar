/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_update_cw_values.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <hklein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 17:48:59 by hklein            #+#    #+#             */
/*   Updated: 2019/05/11 16:50:02 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

void	write_pcs(t_vs *vs, t_cw *cw)
{
	t_proc	*tmp_proc;
	int		x;
	int		y;

	tmp_proc = cw->procs;
	while (tmp_proc)
	{
		y = tmp_proc->pc / ft_sqrt(MEM_SIZE);
		x = (tmp_proc->pc % ft_sqrt(MEM_SIZE)) * 3;
		attron(COLOR_PAIR(cw->arena[tmp_proc->pc][1]
					? cw->arena[tmp_proc->pc][1] + 6 : 12));
		mvprintw(vs->starty + y + 2, vs->startx + x + 4, "%.2x"
				, cw->arena[tmp_proc->pc][0]);
		attron(COLOR_PAIR(cw->arena[tmp_proc->pc][1]
					? cw->arena[tmp_proc->pc][1] + 6 : 12));
		tmp_proc = tmp_proc->next;
	}
	attroff(COLOR_PAIR(1));
}

void	add_to_live_tab(t_proc *tmp_proc, t_player *tmp_player)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		tmp_proc->cw->vs->live_signal[i + 1] = tmp_proc->cw->vs->live_signal[i];
		i++;
	}
	tmp_proc->cw->vs->live_signal[0] = tmp_player;
}

void	write_alive(t_proc *tmp_proc, t_player *tmp_player)
{
	t_player	**tab;
	int			i;

	i = 0;
	tab = tmp_proc->cw->vs->live_signal;
	add_to_live_tab(tmp_proc, tmp_player);
	while (tmp_proc->cw->vs->live_signal[i] && i < 5)
	{
		wattron(tmp_proc->cw->vs->live_win, COLOR_PAIR(7));
		mvwprintw(tmp_proc->cw->vs->live_win, 1 + i, 2, "player ");
		wattron(tmp_proc->cw->vs->live_win, COLOR_PAIR(tab[i]->color));
		wprintw(tmp_proc->cw->vs->live_win, "%d", tab[i]->nb_player);
		wattron(tmp_proc->cw->vs->live_win, COLOR_PAIR(7));
		wprintw(tmp_proc->cw->vs->live_win, " is alive");
		wattroff(tmp_proc->cw->vs->live_win, COLOR_PAIR(7));
		i++;
	}
	wrefresh(tmp_proc->cw->vs->live_win);
}

void	update_arena(t_vs *vs, t_cw *cw)
{
	int	i;
	int	j;
	int	tab_ind;
	int	line_len;
	int	col;

	i = 0;
	j = 0;
	col = 6;
	tab_ind = 0;
	line_len = ft_sqrt(MEM_SIZE);
	while (tab_ind < MEM_SIZE)
	{
		attron(COLOR_PAIR(cw->arena[tab_ind][1] ? cw->arena[tab_ind][1] : 6));
		mvprintw(vs->starty + j + 2, vs->startx + (i % line_len * 3) + 4
				, "%.2x ", cw->arena[tab_ind][0]);
		attroff(COLOR_PAIR(cw->arena[tab_ind][1] ? cw->arena[tab_ind][1] : 6));
		tab_ind++;
		if (tab_ind && !(tab_ind % line_len))
			j++;
		i++;
	}
}

int		update_cw_values(t_vs *vs, t_cw **cw_beg)
{
	update_arena(vs, *cw_beg);
	write_pcs(vs, *cw_beg);
	update_side_infos(vs, *cw_beg);
	move(0, 0);
	refresh();
	return (deal_key_press(vs, cw_beg));
}
