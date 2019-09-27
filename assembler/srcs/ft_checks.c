/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <hklein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 19:00:22 by glavigno          #+#    #+#             */
/*   Updated: 2019/05/11 16:26:29 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int		check_label_duplicate(t_tokens *tokens)
{
	t_tokens	*buf;
	t_tokens	*buf2;

	buf = tokens;
	while (buf)
	{
		if (buf->type == LABEL)
		{
			buf2 = buf->next;
			while (buf2 && buf2->next)
			{
				if (buf2->type == LABEL
						&& !(ft_strcmp(buf->value, buf2->value)))
					return (1);
				buf2 = buf2->next;
			}
		}
		buf = buf->next;
	}
	return (0);
}

int		get_token_size(t_tokens *buf, t_op *op)
{
	if (buf->type & T_REG || (buf->type == INSTRUCTION && !op->encoding_byte))
		return (1);
	else if ((buf->type & T_DIR && op->direct_size) || buf->type & T_IND
			|| buf->type == INDIRECT_LABEL || buf->type == INSTRUCTION)
		return (2);
	else if (buf->type & T_DIR)
		return (4);
	else
		return (0);
}

int		check_file_size(t_tokens *token, t_asm *asmb)
{
	t_tokens	*buf;
	int			size;
	t_op		*op;

	size = 0;
	buf = token;
	while (buf)
	{
		if (buf->type == INSTRUCTION)
			op = identify_op(buf->value);
		buf->position = size;
		size += get_token_size(buf, op);
		buf = buf->next;
	}
	if ((unsigned long)size > (CHAMP_MAX_SIZE - sizeof(t_header) - 8))
		return (1);
	asmb->champion_size = size;
	asmb->header->prog_size = big_endian(size);
	asmb->header->magic = big_endian(COREWAR_EXEC_MAGIC);
	return (0);
}

int		check_label_call(t_tokens *token)
{
	t_tokens *buf;

	buf = token;
	while (buf)
	{
		if (buf->type & 8 && get_label_position(token, buf->value) == -1)
			return (1);
		buf = buf->next;
	}
	return (0);
}

int		ft_checks(t_asm *asmb)
{
	if (check_label_duplicate(asmb->tokens))
		return (ft_disp_error("Error: label duplicate detected\n", 1));
	if (check_file_size(asmb->tokens, asmb))
		return (ft_disp_error("Error: champion's size is too big\n", 1));
	if (check_label_call(asmb->tokens))
		return (ft_disp_error(
		"Error: label called as an arg does not exist\n", 1));
		return (0);
}
