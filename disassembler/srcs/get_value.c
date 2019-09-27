/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_value.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <hklein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 17:24:25 by arumpler          #+#    #+#             */
/*   Updated: 2019/05/11 16:47:09 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disassembler.h"

char		*get_value(int fd, int size)
{
	int				nb;
	int				max_pow;
	unsigned char	c;

	nb = 0;
	max_pow = size - 1;
	while (size--)
	{
		read(fd, &c, 1);
		nb += c * ft_int_pow(16 * 16, size);
	}
	return (ft_itoa(nb));
}
