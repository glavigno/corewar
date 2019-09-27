/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <hklein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 21:16:36 by arumpler          #+#    #+#             */
/*   Updated: 2019/05/11 16:20:16 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

void	ft_zjmp(t_proc *proc)
{
	int	tmp;

	tmp = proc->pc;
	if (!proc->cf)
		proc->pc = (proc->pc + 3) % MEM_SIZE;
	else
		proc->pc = (proc->pc + idx_mod(get_value_from_memory(proc->pc
						+ 1, 2, proc))) % MEM_SIZE;
}
