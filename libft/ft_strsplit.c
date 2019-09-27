/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 10:33:28 by hklein            #+#    #+#             */
/*   Updated: 2019/02/25 19:37:31 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		separator(char c, char a)
{
	if (c == a)
		return (1);
	if (c == '\0')
		return (1);
	else
		return (0);
}

static int		ft_nbwords(char const *s, char c)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (s[i] != '\0')
	{
		if (!(separator(s[i], c)))
		{
			nb++;
			while (!(separator(s[i], c)))
				i++;
		}
		else
			i++;
	}
	return (nb);
}

static int		ft_malloc_fill(char **s_end, char const *s, char c, int nbwords)
{
	int	tmpsize;
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (!(separator(s[i], c)))
		{
			tmpsize = 0;
			nbwords++;
			while (!(separator(s[i++], c)))
				tmpsize++;
			if (!(s_end[nbwords] = (char*)malloc(sizeof(char) * (tmpsize + 1))))
				return (0);
			i = i - tmpsize - 1;
			tmpsize = 0;
			while (!(separator(s[i], c)))
				s_end[nbwords][tmpsize++] = s[i++];
			s_end[nbwords][tmpsize] = '\0';
		}
		else
			i++;
	}
	return (nbwords);
}

char			**ft_strsplit(char const *s, char c)
{
	int		nbwords;
	char	**s_end;

	if (!s)
		return (0);
	nbwords = ft_nbwords(s, c);
	if (!(s_end = (char**)malloc(sizeof(char*) * (nbwords + 1))))
		return (0);
	nbwords = -1;
	nbwords = ft_malloc_fill(s_end, s, c, nbwords);
	s_end[nbwords + 1] = NULL;
	return (s_end);
}
