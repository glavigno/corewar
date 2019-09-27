/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_generate_players.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <hklein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 12:17:01 by hklein            #+#    #+#             */
/*   Updated: 2019/05/11 16:03:40 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

int				is_nb_taken(int nb, t_cw *cw)
{
	t_player	*tmp_player;

	tmp_player = cw->players;
	while (tmp_player)
	{
		if (tmp_player->nb_player == nb)
			return (1);
		tmp_player = tmp_player->next;
	}
	return (0);
}

int				check_number(t_cw *cw, char **av, t_player *tmp_player)
{
	static int	nb = 1;

	if (!ft_strcmp(av[cw->arg], "-n"))
	{
		if (av[cw->arg + 1] && ft_is_str_digit(av[cw->arg + 1]))
		{
			tmp_player->nb_player = ft_atoi(av[cw->arg + 1]);
			cw->arg += 2;
		}
		else
			return (ft_disp_error("Check your inputs\n", 1));
	}
	else
	{
		while (is_nb_taken(nb, cw))
			nb++;
		tmp_player->nb_player = nb++;
	}
	return (0);
}

void			add_to_cw(t_cw *cw, t_player *tmp_player)
{
	static t_player	*last_player;

	if (!cw->players)
	{
		cw->players = tmp_player;
		last_player = cw->players;
	}
	else
	{
		last_player->next = tmp_player;
		last_player = tmp_player;
	}
}

int				set_champ(t_cw *cw, char **av, t_player *tmp_player)
{
	if (ft_strlen(av[cw->arg]) < 5
			|| ft_strcmp(&av[cw->arg][ft_strlen(av[cw->arg]) - 4], ".cor"))
		return (ft_disp_error("File extension and/or name invalid\n", 1));
	if (!(tmp_player->file = ft_strdup(av[cw->arg])))
		return (ft_disp_error("Error while initializing game\n", 1));
	tmp_player->fd = open(tmp_player->file, O_RDONLY);
	if (tmp_player->fd == -1)
		return (ft_disp_error("File doesn't exist or is invalid\n", 1));
	if (check_magic_nb(tmp_player))
		return (1);
	read(tmp_player->fd, tmp_player->name, 128);
	lseek(tmp_player->fd, 4, SEEK_CUR);
	read(tmp_player->fd, tmp_player->exec_size, 4);
	tmp_player->exec_size_int = (unsigned int)((tmp_player->exec_size[0] << 24)
			| (tmp_player->exec_size[1] << 16) | (tmp_player->exec_size[2] << 8)
			| (tmp_player->exec_size[3] << 0));
	if (tmp_player->exec_size_int > CHAMP_MAX_SIZE)
		return (ft_disp_error("Champion is too big\n", 1));
	read(tmp_player->fd, tmp_player->comment, 2048);
	lseek(tmp_player->fd, 4, SEEK_CUR);
	return (0);
}

int				generate_players(t_cw *cw, char **av)
{
	t_player	*tmp_player;
	int			nb_players;

	nb_players = 0;
	if (!av[cw->arg])
		return (ft_disp_error("Check your inputs\n", 1));
	while (av[cw->arg])
	{
		if (!(tmp_player = init_player()))
			return (ft_disp_error("Error while creating player\n", 1));
		if (check_number(cw, av, tmp_player) || set_champ(cw, av, tmp_player))
		{
			if (tmp_player->file)
				ft_strdel(&tmp_player->file);
			free(tmp_player);
			return (1);
		}
		nb_players++;
		add_to_cw(cw, tmp_player);
		cw->arg++;
	}
	if (check_nbs_players(nb_players, cw))
		return (1);
	return (0);
}
