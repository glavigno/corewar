/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <hklein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 21:16:36 by arumpler          #+#    #+#             */
/*   Updated: 2019/05/11 16:10:58 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

int			fork_proc(t_proc *proc, int new_addr)
{
	t_proc *tmp;

	tmp = proc->cw->procs;
	if (create_proc(proc->parent_player, proc->cw))
		return (1);
	ft_memcpy(proc->cw->procs, proc, sizeof(t_proc));
	proc->cw->procs->next = tmp;
	proc->cw->procs->pc = new_addr;
	proc->cw->procs->instr_exec_cycle = 0;
	proc->cw->procs->alive = 1;
	proc->cw->procs->id = proc->cw->nb_proc - 1;
	identify_instruction(proc->cw, proc->cw->procs);
	return (0);
}

int			ft_fork(t_proc *proc, int lg)
{
	unsigned int	pc;
	int				new_addr;

	pc = proc->pc;
	proc->pc = (proc->pc + size_of_instruction(proc)) % MEM_SIZE;
	if (lg)
		new_addr = (pc + get_value_from_memory(pc + 1, 2, proc)) % MEM_SIZE;
	else
		new_addr = (pc
		+ idx_mod(get_value_from_memory(pc + 1, 2, proc))) % MEM_SIZE;
	return (fork_proc(proc, new_addr));
}
