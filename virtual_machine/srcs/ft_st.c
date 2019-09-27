/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <hklein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 21:16:36 by arumpler          #+#    #+#             */
/*   Updated: 2019/05/11 16:17:29 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

void				write_arena(t_proc *proc, int start_pos, int reg)
{
	int				nb_bytes;

	nb_bytes = 4;
	while (--nb_bytes >= 0)
	{
		proc->cw->arena[start_pos
			% MEM_SIZE][0] = (reg >> (8 * nb_bytes)) & 0xff;
		proc->cw->arena[start_pos
			% MEM_SIZE][1] = (unsigned char)proc->parent_player->color;
		start_pos++;
	}
}

int					scnd_arg(t_proc *proc, int pc, int *flag)
{
	int				addr;
	int				check_reg;

	addr = 0;
	if (proc->args_size[1] == 1)
	{
		check_reg = get_value_from_memory(pc + 2 + proc->args_size[0], 1, proc);
		if (check_reg > 0 && check_reg < 17)
			addr = proc->regs[check_reg - 1];
		else
			*flag -= 1;
	}
	else
	{
		if (get_value_from_memory(pc + 1, 1, proc) & 16)
			addr = get_value_from_memory(pc + idx_mod(get_value_from_memory(pc
							+ 2 + proc->args_size[0], 2, proc)), 4, proc);
		else
			addr = get_value_from_memory(pc + 2 + proc->args_size[0], 2, proc);
	}
	return (addr);
}

int					thrd_arg(t_proc *proc, int pc, int *flag)
{
	int				addr;
	int				check_reg;

	addr = 0;
	if (proc->args_size[2] == 1)
	{
		check_reg = get_value_from_memory(pc
				+ 2 + proc->args_size[0] + proc->args_size[1], 1, proc);
		if (check_reg > 0 && check_reg < 17)
			addr = proc->regs[check_reg - 1];
		else
			*flag -= 1;
	}
	else
		addr = get_value_from_memory(pc + 2
				+ proc->args_size[0] + proc->args_size[1], 2, proc);
	return (addr);
}

void				ft_sti(t_proc *proc)
{
	unsigned int	pc;
	int				reg;
	int				addr;
	int				check_reg;
	int				flag;

	pc = proc->pc;
	proc->pc = (proc->pc + size_of_instruction(proc)) % MEM_SIZE;
	reg = 0;
	flag = 0;
	check_reg = get_value_from_memory(pc + 2, 1, proc);
	reg = (check_reg > 0 && check_reg < 17) ? proc->regs[check_reg - 1] : 0;
	addr = scnd_arg(proc, pc, &flag) + thrd_arg(proc, pc, &flag);
	if (flag == 0)
		write_arena(proc, (pc + addr) % MEM_SIZE, reg);
}

void				ft_st(t_proc *proc)
{
	unsigned int	pc;
	int				reg;
	int				check_reg;

	pc = proc->pc;
	proc->pc = (proc->pc + size_of_instruction(proc)) % MEM_SIZE;
	reg = 0;
	check_reg = get_value_from_memory(pc + 2, 1, proc);
	if (check_reg > 0 && check_reg < 17)
	{
		reg = proc->regs[check_reg - 1];
		if (proc->args_size[1] == 1)
		{
			check_reg = get_value_from_memory(pc
					+ 2 + proc->args_size[0], 1, proc);
			if (check_reg > 0 && check_reg < 17)
				proc->regs[check_reg - 1] = reg;
		}
		else
		{
			pc = (pc + idx_mod(get_value_from_memory(pc
							+ 2 + proc->args_size[0], 2, proc))) % MEM_SIZE;
			write_arena(proc, pc, reg);
		}
	}
}
