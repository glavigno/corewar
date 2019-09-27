/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_instruction.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <hklein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:42:33 by arumpler          #+#    #+#             */
/*   Updated: 2019/05/11 15:53:46 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int			ft_instruction(char *line, t_asm *asmb)
{
	char	**tab;
	char	*tmp;
	int		i;

	tab = NULL;
	if (!(i = is_instruction(line, asmb)))
	{
		ft_putstr_fd("Error: invalid instruction\n", 2);
		return (1);
	}
	if (line[i])
		if (!(tab = ft_strsplit(&line[i], SEPARATOR_CHAR)))
			return (1);
	i = -1;
	while (tab[++i])
	{
		tmp = tab[i];
		if (!(tab[i] = ft_strtrim(tab[i])))
			return (free_tab(tab));
		free(tmp);
		if (!is_argument(tab[i], asmb))
			return (free_tab(tab));
	}
	free_tab(tab);
	return (0);
}
