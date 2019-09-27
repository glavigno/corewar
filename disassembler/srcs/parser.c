/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <hklein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 10:46:37 by arumpler          #+#    #+#             */
/*   Updated: 2019/05/11 16:48:06 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disassembler.h"

int		parse_header(int fd, t_dis *dis)
{
	t_buf *buf;

	if (new_buf_by_value(".name \"", dis))
		return (1);
	if (!(buf = new_buf_by_size(128, dis)))
		return (1);
	lseek(fd, 4, SEEK_CUR);
	read(fd, buf->str, 128);
	if (new_buf_by_value("\"\n.comment \"", dis))
		return (1);
	if (!(buf = new_buf_by_size(2048, dis)))
		return (1);
	lseek(fd, 8, SEEK_CUR);
	read(fd, buf->str, 2048);
	lseek(fd, 4, SEEK_CUR);
	if (new_buf_by_value("\"\n\n", dis))
		return (1);
	return (0);
}

int		create_arg_buf(int type, int dir, int fd, t_dis *dis)
{
	char *str;

	if (type & 1)
	{
		if (new_buf_by_value(" r", dis) || !(str = get_value(fd, 1)))
			return (1);
	}
	else if (type & 2)
	{
		if (new_buf_by_value(" %", dis)
				|| !(str = get_value(fd, 4 - (2 * dir))))
			return (1);
	}
	else
	{
		if (new_buf_by_value(" ", dis) || !(str = get_value(fd, 2)))
			return (1);
	}
	if (new_buf_by_value(str, dis))
		return (1);
	free(str);
	return (0);
}

int		parse_with_enc_byte(int fd, unsigned char ins, t_dis *dis)
{
	int				a;
	int				dec;
	unsigned char	enc;

	a = 192;
	dec = 6;
	read(fd, &enc, 1);
	while (a > 1)
	{
		if ((enc & a) >> dec > 0 && a < 192)
			new_buf_by_value(",", dis);
		if ((enc & a) >> dec == 1)
			if (create_arg_buf(REGISTER, 0, fd, dis))
				return (1);
		if ((enc & a) >> dec == 2)
			if (create_arg_buf(DIRECT, g_op[ins - 1].direct_size, fd, dis))
				return (1);
		if ((enc & a) >> dec == 3)
			if (create_arg_buf(INDIRECT, 0, fd, dis))
				return (1);
		a /= 4;
		dec -= 2;
	}
	return (0);
}

int		parse_instructions(int fd, t_dis *dis)
{
	unsigned char	ins;

	while (read(fd, &ins, 1))
	{
		if (new_buf_by_value(g_op[ins - 1].name, dis))
			return (1);
		if (g_op[ins - 1].encoding_byte)
			parse_with_enc_byte(fd, ins, dis);
		else if (create_arg_buf(g_op[ins - 1].params[0],
			g_op[ins - 1].direct_size, fd, dis))
			return (1);
		if (new_buf_by_value("\n", dis))
			return (1);
	}
	return (0);
}

int		parser(int fd, t_dis *dis)
{
	if (parse_header(fd, dis))
		return (1);
	if (parse_instructions(fd, dis))
		return (1);
	return (0);
}
