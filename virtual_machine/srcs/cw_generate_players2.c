/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_generate_players2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <hklein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 17:48:47 by hklein            #+#    #+#             */
/*   Updated: 2019/05/11 16:04:10 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

int		check_nbs_players(int nb_players, t_cw *cw)
{
	t_player	*tmp;
	t_player	*tmp2;
	char		*err[2];

	err[0] = "There are too many players\n";
	err[1] = "The same player number has been given to several players\n";
	if (nb_players > MAX_PLAYERS)
		return (ft_disp_error(err[0], 1));
	tmp = cw->players;
	while (tmp)
	{
		tmp2 = cw->players;
		while (tmp2)
		{
			if (tmp != tmp2 && tmp->nb_player == tmp2->nb_player)
				return (ft_disp_error(err[1], 1));
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
	cw->nb_players = nb_players;
	return (0);
}

int		check_magic_nb(t_player *tmp_player)
{
	unsigned char	hd_str[4];
	unsigned int	hd;
	int				ret;

	ft_bzero(hd_str, 4);
	ret = read(tmp_player->fd, hd_str, 4);
	if (ret <= 0)
		return (ft_disp_error("File is invalid or empty\n", 1));
	hd = (unsigned int)((hd_str[0] << 24) | (hd_str[1] << 16) | (hd_str[2] << 8)
			| (hd_str[3] << 0));
	return (hd == 15369203 ? 0 : ft_disp_error("Wrong file header\n", 1));
}
