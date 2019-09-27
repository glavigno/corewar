/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <hklein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 16:19:08 by glavigno          #+#    #+#             */
/*   Updated: 2019/05/11 16:47:01 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disassembler.h"

void	free_bufs(t_buf *buf)
{
	t_buf	*tmp;
	t_buf	*tmp0;

	(void)buf;
	tmp = NULL;
	tmp0 = buf;
	while (tmp0)
	{
		tmp = tmp0;
		tmp0 = tmp0->next;
		if (tmp->str)
			free(tmp->str);
		tmp->str = NULL;
		free(tmp);
	}
}

int		free_all(t_dis *dis, int ret)
{
	if (dis->bufs)
	{
		free_bufs(dis->bufs);
		dis->bufs = NULL;
	}
	if (dis->new_filename && ft_strlen(dis->new_filename))
	{
		free(dis->new_filename);
		dis->new_filename = NULL;
	}
	free(dis);
	dis = NULL;
	return (ret);
}
