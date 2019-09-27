/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ldi.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <hklein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 21:16:36 by arumpler          #+#    #+#             */
/*   Updated: 2019/05/11 16:19:23 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

int			first_val(t_proc *proc, int pc, int lg)
{
	unsigned int	val;
	int				check_reg;

	val = 0;
	if (proc->args_size[0] == 1)
	{
		check_reg = get_value_from_memory(pc + 2, 1, proc);
		if (check_reg > 0 && check_reg < 17)
			val = proc->regs[check_reg - 1];
	}
	else if (get_value_from_memory(pc + 1, 1, proc) & 64)
		val = get_value_from_memory(pc
				+ idx_mod(get_value_from_memory(pc + 2, 2, proc)), 4, proc);
	else
	{
		val = (!lg) ? idx_mod(get_value_from_memory(pc + 2, 2, proc))
			: get_value_from_memory(pc + 2, 2, proc);
	}
	return (val);
}

int			second_val(t_proc *proc, int pc, int lg)
{
	unsigned int	val;
	int				check_reg;

	val = 0;
	if (proc->args_size[1] == 1)
	{
		check_reg = get_value_from_memory(pc + 2 + proc->args_size[0], 1, proc);
		if (check_reg > 0 && check_reg < 17)
			val = proc->regs[check_reg - 1];
	}
	else
		val = (!lg) ? idx_mod(get_value_from_memory(pc + 2
					+ proc->args_size[0], 2, proc)) : get_value_from_memory(pc
					+ 2 + proc->args_size[0], 2, proc);
	return (val);
}

void		ft_ldi(t_proc *proc, int lg)
{
	unsigned int	pc;
	int				reg;
	int				val;

	pc = proc->pc;
	proc->pc = (proc->pc + size_of_instruction(proc)) % MEM_SIZE;
	val = first_val(proc, pc, lg) + second_val(proc, pc, lg);
	val = get_value_from_memory(pc + val, 4, proc);
	proc->cf = (!val) ? 1 : 0;
	reg = get_value_from_memory(pc
			+ 2 + proc->args_size[0] + proc->args_size[1], 1, proc);
	if (reg > 0 && reg < 17)
		proc->regs[reg - 1] = val;
}
