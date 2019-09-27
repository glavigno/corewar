/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <hklein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 19:01:59 by glavigno          #+#    #+#             */
/*   Updated: 2019/05/11 16:42:01 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

t_op	*identify_op(char *instruction_name)
{
	int i;

	i = 0;
	while (g_op[i].name)
	{
		if (!ft_strcmp(g_op[i].name, instruction_name))
			return (&g_op[i]);
		i++;
	}
	return (NULL);
}
