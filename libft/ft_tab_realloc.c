/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_realloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 16:09:54 by hklein            #+#    #+#             */
/*   Updated: 2018/12/08 16:11:55 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_tab_realloc(char **tab, size_t size)
{
	char	**new;
	int		i;

	if (!tab)
	{
		if (!(new = (char**)malloc(sizeof(char*) * (size + 1))))
			return (NULL);
		free(tab);
		new[0] = NULL;
		new[1] = NULL;
		return (new);
	}
	if (!(new = (char**)malloc(sizeof(char*) * size + 1)))
		return (NULL);
	new[size] = NULL;
	i = -1;
	if (tab)
	{
		while (tab[++i])
			new[i] = ft_strdup(tab[i]);
		free(tab);
	}
	return (new);
}
