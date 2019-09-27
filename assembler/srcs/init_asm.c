/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_asm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <hklein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:25:31 by arumpler          #+#    #+#             */
/*   Updated: 2019/05/11 15:53:46 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

t_header	*init_header(void)
{
	t_header *tmp;

	if (!(tmp = (t_header*)malloc(sizeof(t_header))))
		return (NULL);
	ft_memset(tmp, 0, sizeof(t_header));
	return (tmp);
}

t_asm		*init_asm(void)
{
	t_asm *tmp;

	if (!(tmp = (t_asm*)malloc(sizeof(t_asm))))
		return (NULL);
	ft_memset(tmp, 0, sizeof(t_asm));
	if (!(tmp->header = init_header()))
	{
		free(tmp);
		return (NULL);
	}
	return (tmp);
}
