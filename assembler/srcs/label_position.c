/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_position.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <hklein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 11:22:29 by arumpler          #+#    #+#             */
/*   Updated: 2019/05/11 15:53:46 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int		get_label_position(t_tokens *token, char *value)
{
	t_tokens *buf;

	buf = token;
	while (buf)
	{
		if (buf->type == LABEL && !ft_strcmp(value, buf->value))
			return (buf->position);
		buf = buf->next;
	}
	return (-1);
}
