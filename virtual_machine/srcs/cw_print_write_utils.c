/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_print_write_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <hklein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 02:39:28 by hugoklein         #+#    #+#             */
/*   Updated: 2019/05/11 15:37:44 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

int		idx_mod(int a)
{
	int neg;

	neg = ((a & 32768) > 0) ? 1 : 0;
	return (a % IDX_MOD - (neg * IDX_MOD));
}

void	dump_memory(unsigned char (*mem)[2], size_t len, int mode)
{
	int		i;

	i = 0;
	while (i < (int)len)
	{
		if (!mode)
		{
			if (mem[i][0] < 17)
				ft_putchar('0');
			ft_printhex((int)mem[i][0]);
			ft_putchar(' ');
		}
		if (mode)
			ft_printf("%c ", (unsigned char)mem[i][0]);
		i++;
	}
}

int		dump_arena(t_cw *cw)
{
	int		i;
	int		line_len;

	i = 0;
	line_len = ft_sqrt(MEM_SIZE) / (cw->opt_dump_type == 1 ? 2 : 1);
	while (i < MEM_SIZE)
	{
		if (!i)
			ft_printf("0x0000 : ");
		else
			ft_printf("%#.4x : ", i);
		dump_memory(&cw->arena[i], cw->opt_dump_type == 1 ? 32 : 64, 0);
		ft_putchar('\n');
		i += line_len;
	}
	return (0);
}

int		count_procs(t_cw *cw)
{
	t_proc	*proc;
	int		i;

	proc = cw->procs;
	i = 0;
	while (proc)
	{
		i++;
		proc = proc->next;
	}
	return (i);
}
