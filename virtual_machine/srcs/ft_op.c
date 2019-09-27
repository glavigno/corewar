/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_op.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <hklein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 17:19:15 by arumpler          #+#    #+#             */
/*   Updated: 2019/05/11 16:24:27 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

int			ft_add_sub(t_proc *proc, int opcode)
{
	unsigned int	pc;
	int				reg[2];
	int				res;
	int				check_reg;

	pc = proc->pc;
	proc->pc = (proc->pc + size_of_instruction(proc)) % MEM_SIZE;
	check_reg = get_value_from_memory(pc + 2, 1, proc);
	if (check_reg > 0 && check_reg < 17)
		reg[0] = proc->regs[check_reg - 1];
	check_reg = get_value_from_memory(pc + 3, 1, proc);
	if (check_reg > 0 && check_reg < 17)
		reg[1] = proc->regs[check_reg - 1];
	res = opcode == 4 ? reg[0] + reg[1] : reg[0] - reg[1];
	check_reg = get_value_from_memory(pc + 4, 1, proc);
	if (check_reg > 0 && check_reg < 17)
		proc->regs[check_reg - 1] = res;
	return (!res ? 1 : 0);
}

void		get_values_bin_op_2(int *val, t_proc *proc, int pc)
{
	int		check_reg;

	if (proc->args_size[1] == 1)
	{
		check_reg = get_value_from_memory(pc + 2 + proc->args_size[0], 1, proc);
		if (check_reg > 0 && check_reg < 17)
			val[1] = proc->regs[check_reg - 1];
	}
	else if (proc->args_size[0] == 2)
		val[1] = get_value_from_memory(pc + idx_mod(get_value_from_memory(pc
						+ 2 + proc->args_size[0], proc->args_size[1],
						proc)), 4, proc);
	else
		val[1] = get_value_from_memory(pc + 2
				+ proc->args_size[0], proc->args_size[1], proc);
}

void		get_values_bin_op(int *val, t_proc *proc, int pc)
{
	int		check_reg;

	if (proc->args_size[0] == 1)
	{
		check_reg = get_value_from_memory(pc + 2, 1, proc);
		if (check_reg > 0 && check_reg < 17)
			val[0] = proc->regs[check_reg - 1];
	}
	else if (proc->args_size[0] == 2)
		val[0] = get_value_from_memory(pc + idx_mod(get_value_from_memory(pc
						+ 2, proc->args_size[0], proc)), 4, proc);
	else
		val[0] = get_value_from_memory(pc + 2, proc->args_size[0], proc);
	get_values_bin_op_2(val, proc, pc);
}

int			ft_bin_op(t_proc *proc, int opcode)
{
	unsigned int	pc;
	int				val[2];
	int				size;
	int				res;
	int				check_reg;

	val[0] = 0;
	val[1] = 0;
	pc = proc->pc;
	proc->pc = (proc->pc + size_of_instruction(proc)) % MEM_SIZE;
	size = proc->args_size[0] + proc->args_size[1];
	get_values_bin_op(val, proc, pc);
	if (opcode == 6)
		res = val[0] & val[1];
	else if (opcode == 7)
		res = val[0] | val[1];
	else
		res = val[0] ^ val[1];
	check_reg = get_value_from_memory(pc + 2 + size, 1, proc);
	if (check_reg > 0 && check_reg < 17)
		proc->regs[check_reg - 1] = res;
	return (!res ? 1 : 0);
}

void		ft_op(t_proc *proc, int opcode)
{
	int		ret;

	if (opcode == 4 || opcode == 5)
		ret = ft_add_sub(proc, opcode);
	else
		ret = ft_bin_op(proc, opcode);
	proc->cf = (ret) ? 1 : 0;
}
