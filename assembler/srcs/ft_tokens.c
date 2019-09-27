/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokens.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <hklein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:24:25 by arumpler          #+#    #+#             */
/*   Updated: 2019/05/11 15:53:46 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int			add_token(t_token_type type, char *value, t_asm *asmb)
{
	t_tokens *tmp;
	t_tokens *buf;

	if (!(tmp = (t_tokens*)malloc(sizeof(t_tokens))))
		return (1);
	ft_memset(tmp, 0, sizeof(t_tokens));
	tmp->type = type;
	if (!(tmp->value = ft_strdup(value)))
	{
		free(tmp);
		return (1);
	}
	if (!asmb->tokens)
		asmb->tokens = tmp;
	else
	{
		buf = asmb->tokens;
		while (buf->next)
			buf = buf->next;
		buf->next = tmp;
	}
	return (0);
}
