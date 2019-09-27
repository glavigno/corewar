/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_instance_fight_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <hklein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 17:31:42 by hklein            #+#    #+#             */
/*   Updated: 2019/05/11 16:05:00 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

void	reset_player_ctd_lives(t_cw *cw)
{
	t_player	*tmp_player;

	tmp_player = cw->players;
	while (tmp_player)
	{
		tmp_player->current_ctd_lives = 0;
		tmp_player = tmp_player->next;
	}
	cw->game->nb_live = 0;
	cw->game->checks = 0;
}

void	check_procs_lives2(t_cw *cw, t_proc **tmp_proc, t_proc **tmp_proc1)
{
	if (cw->procs == *tmp_proc)
	{
		cw->procs = cw->procs->next;
		*tmp_proc1 = cw->procs;
	}
	else
	{
		(*tmp_proc1)->next = (*tmp_proc)->next;
		(*tmp_proc1)->alive = 1;
	}
	ft_memdel((void**)tmp_proc);
	*tmp_proc = *tmp_proc1;
}

void	check_procs_lives(t_cw *cw)
{
	t_proc	*tmp_proc;
	t_proc	*tmp_proc1;

	tmp_proc = cw->procs;
	tmp_proc1 = tmp_proc;
	while (tmp_proc)
	{
		if (!tmp_proc->alive)
		{
			check_procs_lives2(cw, &tmp_proc, &tmp_proc1);
		}
		else
		{
			tmp_proc->alive = 0;
			tmp_proc1 = tmp_proc;
			tmp_proc = tmp_proc->next;
		}
	}
	cw->game->nb_process = count_procs(cw);
}

void	end_instance_opt(t_cw *cw)
{
	if (cw->opt_v)
		cw_vs(cw->vs, cw, 0);
	else
	{
		ft_printf("Contestant %d, \"%s\", has won !\n"
				, cw->game->winner->nb_player, cw->game->winner->name);
	}
}
