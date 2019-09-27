/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enc_byte.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <hklein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 13:16:18 by glavigno          #+#    #+#             */
/*   Updated: 2019/05/11 16:26:02 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

unsigned char		enc_byte(t_tokens *token)
{
	unsigned char	c;
	unsigned char	pos;
	t_tokens		*buf;

	c = 0;
	pos = 7;
	buf = token;
	while (buf && buf->type & 7)
	{
		if (buf->type & T_REG || buf->type & T_IND)
			c = (1 << (pos - 1)) | c;
		if (buf->type & T_DIR || buf->type & T_IND)
			c = (1 << pos) | c;
		pos -= 2;
		buf = buf->next;
	}
	return (c);
}
