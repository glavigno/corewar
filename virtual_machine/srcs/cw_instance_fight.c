/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_instance_fight.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <hklein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/16 17:15:12 by hklein            #+#    #+#             */
/*   Updated: 2019/05/11 16:04:44 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

int		is_running(t_cw *cw)
{
	if (cw->game->checks == cw->game->ctd)
	{
		if (!cw->game->nb_live)
			return (0);
		check_procs_lives(cw);
		if (cw->game->nb_live >= NBR_LIVE)
		{
			cw->game->ctd -= CYCLE_DELTA;
			cw->game->max_checkups = 0;
		}
		else
		{
			if (cw->game->max_checkups < MAX_CHECKS)
				cw->game->max_checkups++;
			else if (cw->game->max_checkups == MAX_CHECKS)
			{
				cw->game->max_checkups = 0;
				cw->game->ctd -= CYCLE_DELTA;
			}
		}
		reset_player_ctd_lives(cw);
	}
	cw->game->checks++;
	return ((cw->game->ctd <= 0) ? 0 : 1);
}

void	identify_instruction(t_cw *cw, t_proc *tmp_proc)
{
	if (cw->arena[tmp_proc->pc][0] > 0 && cw->arena[tmp_proc->pc][0] < 17)
	{
		tmp_proc->instruction = &g_op[cw->arena[tmp_proc->pc][0] - 1];
		tmp_proc->instr_exec_cycle = cw->game->cycle
			+ tmp_proc->instruction->nb_cycles;
	}
	else
		tmp_proc->pc++;
}

void	set_winner(t_cw *cw)
{
	t_player	*tmp_player;
	int			last_live;
	int			j;

	tmp_player = cw->players;
	last_live = 0;
	j = 0;
	cw->game->cycle++;
	while (tmp_player)
	{
		if (!j && tmp_player->last_live_cycle > last_live)
			last_live = tmp_player->last_live_cycle;
		if (j && last_live == tmp_player->last_live_cycle)
		{
			cw->game->winner = tmp_player;
			break ;
		}
		tmp_player = tmp_player->next;
		if (!j && !tmp_player)
		{
			tmp_player = cw->players;
			j++;
		}
	}
}

int		run_cycle(t_cw *cw)
{
	t_proc	*tmp_proc;

	tmp_proc = cw->procs;
	while (tmp_proc)
	{
		if (cw->game->cycle
			&& tmp_proc->instr_exec_cycle == cw->game->cycle)
		{
			if (execute_instr(tmp_proc))
				return (ft_disp_error("Error while running game\n", 1));
			tmp_proc->instr_exec_cycle = 0;
		}
		if (!tmp_proc->instr_exec_cycle)
			identify_instruction(cw, tmp_proc);
		tmp_proc->pc = tmp_proc->pc % MEM_SIZE;
		tmp_proc = tmp_proc->next;
	}
	return (0);
}

int		instance_fight(t_cw *cw)
{
	if (!(cw->game = init_game(cw)))
		return (ft_disp_error("Error while initializing game infos\n", 1));
	if (!cw->opt_v && !cw->opt_dump_type)
		introduce_contestants(cw);
	while (is_running(cw))
	{
		if (run_cycle(cw))
			return (1);
		if (cw->opt_v)
		{
			if (cw_vs(cw->vs, cw, 1))
				return (0);
			if (cw->opt_v == 2 && !(cw = save_cycle(cw)))
				return (ft_disp_error("Error while running game\n", 1));
		}
		if (cw->opt_dump_type && cw->game->cycle == cw->opt_dump)
			return (dump_arena(cw));
		cw->game->cycle++;
	}
	set_winner(cw);
	end_instance_opt(cw);
	return (0);
}
