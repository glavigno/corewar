/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <hklein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 14:12:14 by arumpler          #+#    #+#             */
/*   Updated: 2019/05/11 16:46:33 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int		parser(t_asm *asmb)
{
	t_tokens	*buf;

	if (ft_checks(asmb))
		return (1);
	if (!(asmb->bytes = (unsigned char*)malloc(asmb->champion_size + 1)))
		return (1);
	ft_bzero(asmb->bytes, asmb->champion_size + 1);
	buf = asmb->tokens;
	while (buf->next)
	{
		if (buf->type != LABEL && buf->type != INSTRUCTION)
			return (ft_disp_error(
						"Error: Wrong initial command (no label nor instr.)\n",
						1));
			asmb->instruction_pos = buf->position;
		if (buf->type == INSTRUCTION)
			if (parse_instruction(&buf, asmb))
				return (1);
		if (buf && buf->next && buf->type == LABEL)
			buf = buf->next;
	}
	return (0);
}
