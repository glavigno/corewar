/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_load_players_procs.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <hklein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 18:56:15 by hklein            #+#    #+#             */
/*   Updated: 2019/05/11 16:07:22 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

int		create_proc(t_player *tmp_player, t_cw *cw)
{
	t_proc	*tmp_proc;

	if (!(tmp_proc = init_proc(cw)))
		return (1);
	tmp_proc->regs[0] = tmp_player->nb_player;
	if (!cw->procs)
		cw->procs = tmp_proc;
	else
	{
		tmp_proc->next = cw->procs;
		cw->procs = tmp_proc;
	}
	tmp_proc->parent_player = tmp_player;
	return (0);
}

int		fill_arena_start(t_cw *cw,
			unsigned char *tmp, int nb, t_player *tmp_player)
{
	int		i;
	int		pos;
	int		s;

	pos = MEM_SIZE / cw->nb_players * nb;
	s = pos;
	i = 0;
	while (i < tmp_player->exec_size_int)
	{
		cw->arena[pos][0] = tmp[i++];
		cw->arena[pos++][1] = tmp_player->color;
	}
	return (s);
}

int		read_champ_instructions(unsigned char **tmp, t_player *tmp_player)
{
	int		ret;

	ret = read(tmp_player->fd, *tmp, tmp_player->exec_size_int);
	if (ret != tmp_player->exec_size_int)
	{
		free(*tmp);
		return (ft_disp_error("Announced champion size is wrong\n", 1));
	}
	ret = read(tmp_player->fd, *tmp, 1);
	if (ret)
	{
		free(*tmp);
		return (ft_disp_error("Announced champion size is wrong\n", 1));
	}
	return (0);
}

int		load_players_procs(t_cw *cw)
{
	t_player		*tmp_player;
	unsigned char	*tmp;
	int				tmp_nb;

	tmp_player = cw->players;
	tmp_nb = 0;
	if (cw->opt_v)
		if (!(cw->vs = start_vs(cw)))
			return (ft_disp_error("Error while initializing visualizer\n", 1));
	while (tmp_player)
	{
		if (create_proc(tmp_player, cw))
			return (ft_disp_error("Error while creating process\n", 1));
		if (!(tmp = (unsigned char*)malloc(tmp_player->exec_size_int)))
			return (ft_disp_error("Error while creating process\n", 1));
		if (read_champ_instructions(&tmp, tmp_player))
			return (1);
		cw->procs->pc = fill_arena_start(cw, tmp, tmp_nb, tmp_player);
		free(tmp);
		tmp_nb++;
		tmp_player = tmp_player->next;
	}
	return (0);
}
