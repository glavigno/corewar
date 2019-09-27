/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_label.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <hklein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:22:34 by arumpler          #+#    #+#             */
/*   Updated: 2019/05/11 15:53:46 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int			ft_label(char *line, t_asm *asmb)
{
	int		index;
	int		i;
	char	*value;

	index = find_first(line, LABEL_CHAR, LABEL_CHAR);
	if (!(value = ft_strsub(line, 0, index)))
		return (1);
	if (add_token(LABEL, value, asmb))
	{
		free(value);
		return (1);
	}
	free(value);
	i = index + 1;
	while (line[i])
	{
		if (line[i] != 32)
		{
			ft_instruction(&line[i], asmb);
			return (0);
		}
		i++;
	}
	return (0);
}
