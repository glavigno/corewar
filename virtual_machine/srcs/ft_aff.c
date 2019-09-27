/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <hklein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 18:18:55 by arumpler          #+#    #+#             */
/*   Updated: 2019/05/11 16:10:40 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

void		ft_aff(t_proc *proc)
{
	int		pc;
	int		reg;
	int		check_reg;

	pc = proc->pc;
	proc->pc = (proc->pc + size_of_instruction(proc)) % MEM_SIZE;
	check_reg = get_value_from_memory(pc + 2, 1, proc);
	if (check_reg > 0 && check_reg < 17)
	{
		reg = proc->regs[check_reg - 1] % 256;
		if (proc->cw->opt_a == 1)
			ft_printf("Aff: %c\n", reg);
	}
}
