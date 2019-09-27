/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_endian.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <hklein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 15:02:22 by arumpler          #+#    #+#             */
/*   Updated: 2019/05/11 16:25:57 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

unsigned int		big_endian(unsigned int x)
{
	int reverse;

	reverse = 0;
	reverse += (x & 0xff000000) / 1;
	reverse += (x & 0x00ff0000) / 0x00000100;
	reverse += (x & 0x0000ff00) * 0x00000100;
	reverse += (x & 0x000000ff) * 0x01000000;
	return (reverse);
}
