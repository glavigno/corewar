/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_init_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <hklein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 18:51:55 by hklein            #+#    #+#             */
/*   Updated: 2019/05/11 16:04:17 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

t_vs			*init_vs(void)
{
	t_vs		*vs;

	if (!(vs = (t_vs*)malloc(sizeof(t_vs))))
		return (NULL);
	ft_memset(vs, 0, sizeof(t_vs));
	vs->speed = VS_INIT_SPEED_;
	return (vs);
}

t_player		*init_player(void)
{
	t_player	*player;

	if (!(player = (t_player*)malloc(sizeof(t_player))))
		return (NULL);
	ft_memset(player, 0, sizeof(t_player));
	return (player);
}

t_proc			*init_proc(t_cw *cw)
{
	t_proc		*proc;

	if (!(proc = (t_proc*)malloc(sizeof(t_proc))))
		return (NULL);
	ft_memset(proc, 0, sizeof(t_proc));
	proc->alive = 1;
	proc->cw = cw;
	proc->id = cw->nb_proc++;
	return (proc);
}

t_cw			*init_cw(void)
{
	t_cw		*cw;
	int			i;

	i = 0;
	if (!(cw = (t_cw*)malloc(sizeof(t_cw))))
		return (NULL);
	ft_memset(cw, 0, sizeof(t_cw));
	while (i < MEM_SIZE)
		ft_memset(cw->arena[i++], 0, 2);
	cw->arg = 1;
	cw->nb_proc = 1;
	return (cw);
}

t_game			*init_game(t_cw *cw)
{
	t_game		*game;

	if (!(game = (t_game*)malloc(sizeof(t_game))))
		return (NULL);
	ft_memset(game, 0, sizeof(t_game));
	game->nb_process = count_procs(cw);
	game->ctd = CYCLE_TO_DIE;
	return (game);
}
