/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <hklein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 16:19:08 by glavigno          #+#    #+#             */
/*   Updated: 2019/05/11 16:26:07 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int		free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
	return (1);
}

void	free_tokens(t_tokens *tokens)
{
	t_tokens	*tmp;

	tmp = NULL;
	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		if (tmp->value)
			free(tmp->value);
		tmp->value = NULL;
		free(tmp);
	}
}

int		free_all(t_asm *asmb, int ret)
{
	if (asmb->tokens)
	{
		free_tokens(asmb->tokens);
		asmb->tokens = NULL;
	}
	if (asmb->header)
	{
		free(asmb->header);
		asmb->header = NULL;
	}
	if (asmb->bytes)
	{
		free(asmb->bytes);
		asmb->bytes = NULL;
	}
	if (asmb->new_filename)
	{
		free(asmb->new_filename);
		asmb->new_filename = NULL;
	}
	free(asmb);
	asmb = NULL;
	return (ret);
}
