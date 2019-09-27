/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_save_cycle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <hklein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 17:29:18 by hklein            #+#    #+#             */
/*   Updated: 2019/05/11 16:10:33 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

t_cw		*free_error_save(t_cw *next_cycle)
{
	if (next_cycle->procs)
		free_procs(next_cycle);
	if (next_cycle->procs)
		free_players(next_cycle);
	if (next_cycle->game)
	{
		free(next_cycle->game);
		next_cycle->game = NULL;
	}
	next_cycle = NULL;
	return (NULL);
}

int			duplicate_players(t_cw *cw, t_cw *next_cycle)
{
	t_player	*tmp_player;
	t_player	*tmp_player2;

	tmp_player = cw->players;
	if (!(next_cycle->players = init_player()))
		return (1);
	next_cycle->players = ft_memcpy(next_cycle->players,
			tmp_player, sizeof(t_player));
	tmp_player2 = next_cycle->players;
	if (!(tmp_player2->file = ft_strdup(tmp_player->file)))
		return (1);
	tmp_player = tmp_player->next;
	while (tmp_player)
	{
		if (!(tmp_player2->next = init_player()))
			return (1);
		tmp_player2->next = ft_memcpy(tmp_player2->next,
				tmp_player, sizeof(t_player));
		if (!(tmp_player2->next->file = ft_strdup(tmp_player->file)))
			return (1);
		tmp_player = tmp_player->next;
		tmp_player2 = tmp_player2->next;
	}
	return (0);
}

t_player	*find_new_parent(t_cw *next_cycle, t_proc *tmp_proc)
{
	t_player	*tmp_player;

	tmp_player = next_cycle->players;
	while (tmp_player)
	{
		if (tmp_proc->parent_player->nb_player == tmp_player->nb_player)
			return (tmp_player);
		tmp_player = tmp_player->next;
	}
	return (NULL);
}

int			duplicate_procs(t_cw *cw, t_cw *next_cycle)
{
	t_proc	*tmp_proc;
	t_proc	*tmp_proc2;

	tmp_proc = cw->procs;
	if (!(next_cycle->procs = init_proc(next_cycle)))
		return (1);
	next_cycle->procs = ft_memcpy(next_cycle->procs,
			tmp_proc, sizeof(t_proc));
	tmp_proc2 = next_cycle->procs;
	tmp_proc2->cw = next_cycle;
	tmp_proc = tmp_proc->next;
	while (tmp_proc)
	{
		if (!(tmp_proc2->next = init_proc(next_cycle)))
			return (1);
		tmp_proc2->next = ft_memcpy(tmp_proc2->next,
				tmp_proc, sizeof(t_proc));
		tmp_proc = tmp_proc->next;
		tmp_proc2 = tmp_proc2->next;
		tmp_proc2->cw = next_cycle;
		tmp_proc2->parent_player = find_new_parent(next_cycle, tmp_proc2);
	}
	return (0);
}

t_cw		*save_cycle(t_cw *cw)
{
	t_cw	*next_cycle;

	if (!(next_cycle = init_cw()))
		return (NULL);
	next_cycle = ft_memcpy(next_cycle, cw, sizeof(t_cw));
	next_cycle->procs = 0;
	next_cycle->players = 0;
	next_cycle->game = 0;
	if (duplicate_players(cw, next_cycle))
		return (free_error_save(next_cycle));
	if (duplicate_procs(cw, next_cycle))
		return (free_error_save(next_cycle));
	if (!(next_cycle->game = init_game(next_cycle)))
		return (free_error_save(next_cycle));
	next_cycle->game = ft_memcpy(next_cycle->game, cw->game, sizeof(t_game));
	cw->saved_cycles_next = next_cycle;
	next_cycle->saved_cycles_prec = cw;
	return (next_cycle);
}
