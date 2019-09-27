/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <hklein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 14:17:10 by glavigno          #+#    #+#             */
/*   Updated: 2019/05/11 16:44:38 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int		check_arg(t_op *op, t_tokens *buf)
{
	int i;

	i = 0;
	while (i < op->nb_params)
	{
		if (!buf || !(buf->type & op->params[i]))
			return (ft_disp_error(
						"Error: wrong operation's arguments' types\n", 1));
			i++;
		buf = buf->next;
	}
	if (buf && (buf->type != LABEL && buf->type != INSTRUCTION))
		return (ft_disp_error("Error: too many arguments\n", 1));
	return (0);
}

int		bytes_to_write(t_tokens *buf, t_op *op)
{
	if (buf->type & T_REG)
		return (1);
	else if ((buf->type & T_DIR && op->direct_size) || buf->type & T_IND)
		return (2);
	else
		return (4);
}

void	write_arg(t_asm *asmb, t_tokens *buf, t_op *op)
{
	int nb_bytes;
	int value;

	value = ft_atoi(buf->value);
	nb_bytes = bytes_to_write(buf, op);
	while (--nb_bytes >= 0)
		asmb->bytes[buf->position++] = (value >> (8 * nb_bytes)) & 0xff;
}

void	write_label_arg(t_asm *asmb, t_tokens *buf, t_op *op)
{
	int nb_bytes;
	int value;

	if (buf->type & 2 && !op->direct_size)
		nb_bytes = 4;
	else
		nb_bytes = 2;
	value = get_label_position(asmb->tokens, buf->value)
		- asmb->instruction_pos;
	while (--nb_bytes >= 0)
		asmb->bytes[buf->position++] = (value >> (8 * nb_bytes)) & 0xff;
}

void	write_bytes(t_asm *asmb, t_tokens **buf, t_op *op)
{
	while (*buf && (*buf)->type & 7)
	{
		if ((*buf)->type & 8)
			write_label_arg(asmb, *buf, op);
		else
			write_arg(asmb, *buf, op);
		if (!(*buf)->next)
			break ;
		*buf = (*buf)->next;
	}
}
