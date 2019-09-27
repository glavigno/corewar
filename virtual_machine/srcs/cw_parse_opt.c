/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_parse_opt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <hklein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:02:19 by hklein            #+#    #+#             */
/*   Updated: 2019/05/11 16:08:42 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

int		parse_dump(t_cw *cw, char **av)
{
	if (av[cw->arg + 1] && ft_is_str_digit(av[cw->arg + 1]) && av[cw->arg + 2]
			&& ft_is_str_digit(av[cw->arg + 2]))
	{
		cw->opt_dump_type = ft_atoi(av[cw->arg + 1]);
		if (cw->opt_dump_type < 1 || cw->opt_dump_type > 2)
			return (1);
		cw->opt_dump = ft_atoi(av[cw->arg + 2]);
		cw->arg += 2;
	}
	else
		return (1);
	return (0);
}

int		parse_v(t_cw *cw, char **av)
{
	if (av[cw->arg + 1] && ft_is_str_digit(av[cw->arg + 1]))
	{
		cw->arg++;
		cw->opt_v = ft_atoi(av[cw->arg]);
		if (cw->opt_v > 2 || cw->opt_v < 1)
			return (1);
	}
	else
		return (1);
	return (0);
}

int		check_opt(t_cw *cw, char **av)
{
	int		i;

	i = 1;
	while (i < cw->arg && av[i][0] == '-' && ft_strcmp(av[i], "-n"))
	{
		if (!ft_strcmp(av[i], "-dump") || !ft_strcmp(av[i], "-a")
				|| !ft_strcmp(av[i], "-v"))
			i++;
		else
			return (ft_disp_error("Illegal option used\n", 1));
	}
	if (cw->opt_a)
		if (cw->opt_dump_type || cw->opt_v)
			return (ft_disp_error("Too many options used\n", 1));
	if (cw->opt_v)
		if (cw->opt_dump_type || cw->opt_a)
			return (ft_disp_error("Too many options used\n", 1));
	if (cw->opt_dump_type)
		if (cw->opt_v || cw->opt_a)
			return (ft_disp_error("Too many options used\n", 1));
	return (0);
}

int		parse_opt(t_cw *cw, char **av)
{
	while (av[cw->arg] && av[cw->arg][0] == '-' && ft_strcmp(av[cw->arg], "-n"))
	{
		if (!ft_strcmp(av[cw->arg], "-dump") && parse_dump(cw, av))
			return (ft_disp_error("Check your inputs\n", 1));
		else if (!ft_strcmp(av[cw->arg], "-a"))
			cw->opt_a = 1;
		else if (!ft_strcmp(av[cw->arg], "-v") && parse_v(cw, av))
			return (ft_disp_error("Check your inputs\n", 1));
		cw->arg++;
	}
	if (check_opt(cw, av))
		return (1);
	return (0);
}
