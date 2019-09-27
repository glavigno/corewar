/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <hklein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 15:58:12 by arumpler          #+#    #+#             */
/*   Updated: 2019/05/11 16:12:36 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

t_player	*player_exists(t_proc *proc)
{
	t_player	*player;
	int			nb;

	nb = get_value_from_memory(proc->pc + 1, 4, proc);
	player = proc->cw->players;
	while (player)
	{
		if (player->nb_player == nb)
		{
			player->current_ctd_lives++;
			player->last_live_cycle = proc->cw->game->cycle;
			return (player);
		}
		player = player->next;
	}
	return (NULL);
}

void		ft_live(t_proc *proc)
{
	t_player	*tmp_player;

	if ((tmp_player = player_exists(proc)))
	{
		if (proc->cw->opt_v)
			write_alive(proc, tmp_player);
		else if (!proc->cw->opt_dump_type)
			ft_printf("A process shows that player %d (%s) is alive\n",
					tmp_player->nb_player, tmp_player->name);
	}
	proc->pc = (proc->pc + size_of_instruction(proc)) % MEM_SIZE;
	proc->cw->game->nb_live++;
	proc->alive = 1;
}
