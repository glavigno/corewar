/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_free_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <hklein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 18:50:12 by hklein            #+#    #+#             */
/*   Updated: 2019/05/11 16:02:00 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

void			free_procs(t_cw *cw)
{
	t_proc		*tmp_proc;
	t_proc		*tmp_proc1;

	tmp_proc = cw->procs;
	while (tmp_proc)
	{
		tmp_proc1 = tmp_proc;
		tmp_proc = tmp_proc->next;
		free(tmp_proc1);
		tmp_proc1 = NULL;
	}
}

void			free_players(t_cw *cw)
{
	t_player	*tmp_player;
	t_player	*tmp_player1;

	tmp_player = cw->players;
	while (tmp_player)
	{
		tmp_player1 = tmp_player;
		tmp_player = tmp_player->next;
		ft_strdel(&tmp_player1->file);
		free(tmp_player1);
		tmp_player1 = NULL;
	}
}

void			free_cw_list(t_cw *cw)
{
	t_cw		*tmp_cw;
	t_cw		*tmp_cw1;

	tmp_cw = cw;
	free(tmp_cw->vs);
	while (tmp_cw)
	{
		free_procs(tmp_cw);
		free_players(tmp_cw);
		free(tmp_cw->game);
		tmp_cw1 = tmp_cw;
		tmp_cw = tmp_cw->saved_cycles_next;
		free(tmp_cw1);
	}
}
