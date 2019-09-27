/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw_vs_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <hklein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 18:03:45 by hklein            #+#    #+#             */
/*   Updated: 2019/05/11 16:52:07 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cw.h"

void	init_cw_colors(void)
{
	init_color(COLOR_MAGENTA, 500, 500, 500);
	init_color(COLOR_WHITE, 1000, 1000, 1000);
	init_pair(1, COLOR_MAGENTA, COLOR_MAGENTA);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_RED, COLOR_BLACK);
	init_pair(5, COLOR_YELLOW, COLOR_BLACK);
	init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(7, COLOR_WHITE, COLOR_BLACK);
	init_pair(8, COLOR_BLACK, COLOR_GREEN);
	init_pair(9, COLOR_BLACK, COLOR_BLUE);
	init_pair(10, COLOR_BLACK, COLOR_RED);
	init_pair(11, COLOR_BLACK, COLOR_YELLOW);
	init_pair(12, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(13, COLOR_MAGENTA, COLOR_BLACK);
	init_color(COLOR_LIGHTGREEN, 0, 1000, 0);
	init_color(COLOR_LIGHTBLUE, 0, 0, 1000);
	init_pair(14, COLOR_LIGHTGREEN, COLOR_BLACK);
	init_pair(15, COLOR_LIGHTBLUE, COLOR_BLACK);
	init_pair(16, COLOR_LIGHTRED, COLOR_BLACK);
	init_pair(17, COLOR_LIGHTYELLOW, COLOR_BLACK);
	init_pair(18, COLOR_WHITE, COLOR_BLACK);
}

void	draw_grid(t_vs *vs)
{
	wattron(vs->grid_win, COLOR_PAIR(6));
	mvwprintw(vs->grid_win, 0, 1, "    _  _  _  _  _  _  _  _  _  _  _  _  _");
	mvwprintw(vs->grid_win, 1, 1, "   // // // // // // // // // // // // //");
	mvwprintw(vs->grid_win, 2, 1, "  // // // // // // // // // // // // //");
	mvwprintw(vs->grid_win, 3, 1, "  `  `  `  `  `  `  `  ` `  `  `   `  `");
	mvwprintw(vs->grid_win, 4, 1, "    _  _  _  _  _  _  _  _  _  _  _  _  _");
	mvwprintw(vs->grid_win, 5, 1, "   // // // // // // // // // // // // //");
	mvwprintw(vs->grid_win, 6, 1, "  // // // // // // // // // // // // //");
	mvwprintw(vs->grid_win, 7, 1, "  `  `  `  `  `  `  `  ` `  `  `   `  `");
	wattroff(vs->grid_win, COLOR_PAIR(6));
}

void	draw_logo(t_vs *vs)
{
	wattron(vs->logo_win, COLOR_PAIR(3));
	mvwprintw(vs->logo_win, 1, 1, "   _________");
	mvwprintw(vs->logo_win, 2, 1, "  / _______/");
	mvwprintw(vs->logo_win, 3, 1, " / /  / __ \\/");
	mvwprintw(vs->logo_win, 4, 1, "/ /__/ /_/ /");
	mvwprintw(vs->logo_win, 5, 1, "\\___/\\____/_");
	wattron(vs->logo_win, COLOR_PAIR(7));
	mvwprintw(vs->logo_win, 2, 14, "  ______ _     _");
	mvwprintw(vs->logo_win, 3, 14, " __ _ \\ | /| /");
	mvwprintw(vs->logo_win, 4, 13, " /   __/ |/ |/");
	mvwprintw(vs->logo_win, 5, 13, "/ \\___/|__/|__");
	wattron(vs->logo_win, COLOR_PAIR(4));
	mvwprintw(vs->logo_win, 2, 30, "____ ______");
	mvwprintw(vs->logo_win, 3, 28, "  __ `/ ___/");
	mvwprintw(vs->logo_win, 4, 27, "  /_/ / /");
	mvwprintw(vs->logo_win, 5, 27, "\\__,_/_/");
	wattroff(vs->logo_win, COLOR_PAIR(4));
	draw_grid(vs);
}
