/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <hklein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 17:02:30 by hklein            #+#    #+#             */
/*   Updated: 2019/05/11 16:07:28 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

int		show_usage(char **av)
{
	ft_printf("Usage: %s [ -a -dump N N -v N -n N ] ", av[0]);
	ft_printf("<champion1.cor> <...>\n");
	ft_printf("# VERBOSE OPTIONS ######################\n");
	ft_printf("	-dump [1/2] N : dumps memory state at Nth cycle and ");
	ft_printf("stops execution of the program\n");
	ft_printf("	       1/2 : choose hex dump type (32 or 64)\n");
	ft_printf("# PROGRAM OPTIONS ###################\n");
	ft_printf("	-a : outputs the result of aff instruction in the console\n");
	ft_printf("	-n N : assigns a specific number to the following player\n");
	ft_printf("# VISUALIZER ##########################\n");
	ft_printf("	-v [1/2] : launches the virtual machine ncurses visualizer\n");
	ft_printf("	    1/2 : choose wether to save precedent cycles or not\n");
	return (1);
}

int		free_quit(t_cw *cw, int quit)
{
	if (cw)
		free_cw_list(cw);
	return (quit);
}

int		main(int ac, char **av)
{
	t_cw	*cw;

	if (ac == 1)
		return (show_usage(av));
	if (!(cw = init_cw()))
		return (free_quit(cw, 1));
	if (parse_opt(cw, av))
		return (free_quit(cw, 1));
	if (generate_players(cw, av))
		return (free_quit(cw, 1));
	if (load_players_procs(cw))
		return (free_quit(cw, 1));
	if (instance_fight(cw))
		return (free_quit(cw, 1));
	return (free_quit(cw, 0));
}
