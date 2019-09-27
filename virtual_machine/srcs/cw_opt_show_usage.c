/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_opt_show_usage.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <hklein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 14:59:04 by hklein            #+#    #+#             */
/*   Updated: 2019/05/11 16:08:14 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

void	introduce_contestants(t_cw *cw)
{
	t_player	*tmp_player;

	tmp_player = cw->players;
	ft_printf("Introducing contestants...\n");
	while (tmp_player)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
				tmp_player->nb_player, tmp_player->exec_size_int,
				tmp_player->name, tmp_player->comment);
		tmp_player = tmp_player->next;
	}
}
