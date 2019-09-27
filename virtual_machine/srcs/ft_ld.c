/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <hklein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 21:16:36 by arumpler          #+#    #+#             */
/*   Updated: 2019/05/11 16:11:08 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

void		ft_ld(t_proc *proc, int lg)
{
	unsigned int	pc;
	int				reg;
	int				res;

	pc = proc->pc;
	proc->pc = (proc->pc + size_of_instruction(proc)) % MEM_SIZE;
	if (lg || proc->args_size[0] == 4)
		res = get_value_from_memory(pc + 2, proc->args_size[0], proc);
	else
		res = idx_mod(get_value_from_memory(pc + 2, proc->args_size[0], proc));
	if (proc->args_size[0] == 2)
		res = get_value_from_memory(pc + res, 4, proc);
	proc->cf = (!res) ? 1 : 0;
	reg = get_value_from_memory(pc + 2 + proc->args_size[0], 1, proc);
	if (reg > 0 && reg < 17)
		proc->regs[reg - 1] = res;
}
