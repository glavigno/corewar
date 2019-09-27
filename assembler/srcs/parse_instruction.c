/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_instruction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <hklein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 19:04:18 by glavigno          #+#    #+#             */
/*   Updated: 2019/05/11 16:43:10 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int		parse_instruction(t_tokens **buf, t_asm *asmb)
{
	t_op	*op;

	op = identify_op((*buf)->value);
	if (check_arg(op, (*buf)->next))
		return (1);
	asmb->bytes[(*buf)->position] = op->opcode;
	if (op->encoding_byte)
		asmb->bytes[(*buf)->position + 1] = enc_byte((*buf)->next);
	*buf = (*buf)->next;
	write_bytes(asmb, buf, op);
	return (0);
}
