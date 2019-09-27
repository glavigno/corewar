/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <hklein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 15:31:06 by arumpler          #+#    #+#             */
/*   Updated: 2019/05/11 16:01:54 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

int				get_value_from_memory(unsigned int pos, int size, t_proc *proc)
{
	int			nb;
	int			max_pow;

	nb = 0;
	max_pow = size - 1;
	pos = pos % MEM_SIZE;
	while (size--)
	{
		nb += proc->cw->arena[pos][0] * ft_int_pow(16 * 16, size);
		pos = (pos + 1) % MEM_SIZE;
	}
	return (nb);
}

int				check_args(int enc_byte, int i, int c)
{
	return ((enc_byte & (ft_int_pow(2, i) + ft_int_pow(2, i + 1))) >> i == c);
}

int				size_of_arguments(int enc_byte, int direct_size, t_proc *proc)
{
	int			i;
	int			size;

	i = 8;
	size = 0;
	ft_memset(proc->args_size, 0, 12);
	while (i -= 2)
	{
		if (check_args(enc_byte, i, 3))
		{
			proc->args_size[(6 - i) / 2] = 2;
			size += 2;
		}
		else if (check_args(enc_byte, i, 2))
		{
			proc->args_size[(6 - i) / 2] = 4 - (2 * direct_size);
			size += 4 - 2 * direct_size;
		}
		else if (check_args(enc_byte, i, 1))
		{
			proc->args_size[(6 - i) / 2] = 1;
			size += 1;
		}
	}
	return (size);
}

int				size_of_instruction(t_proc *proc)
{
	int			size;

	size = 1;
	if (proc->instruction->encoding_byte)
		size += 1 + size_of_arguments(proc->cw->arena[(proc->pc + 1)
				% MEM_SIZE][0], proc->instruction->direct_size, proc);
	else
		size += 4 - 2 * proc->instruction->direct_size;
	return (size);
}

int				execute_instr(t_proc *proc)
{
	if (proc->instruction->opcode == 1)
		ft_live(proc);
	else if (proc->instruction->opcode == 2 || proc->instruction->opcode == 13)
		ft_ld(proc, proc->instruction->opcode == 13 ? 1 : 0);
	else if (proc->instruction->opcode == 10 || proc->instruction->opcode == 14)
		ft_ldi(proc, proc->instruction->opcode == 14 ? 1 : 0);
	else if (proc->instruction->opcode == 3)
		ft_st(proc);
	else if (proc->instruction->opcode == 11)
		ft_sti(proc);
	else if (proc->instruction->opcode == 9)
		ft_zjmp(proc);
	else if (proc->instruction->opcode == 16)
		ft_aff(proc);
	else if (proc->instruction->opcode == 12 || proc->instruction->opcode == 15)
		return (ft_fork(proc, proc->instruction->opcode == 15 ? 1 : 0));
	else if (proc->instruction->opcode >= 4 && proc->instruction->opcode <= 8)
		ft_op(proc, proc->instruction->opcode);
	return (0);
}
