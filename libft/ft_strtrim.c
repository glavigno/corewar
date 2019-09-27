/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 20:24:48 by hklein            #+#    #+#             */
/*   Updated: 2018/11/15 16:14:15 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_returnblank(void)
{
	char	*s_new;

	if (!(s_new = (char*)malloc(sizeof(char))))
		return (NULL);
	ft_bzero(s_new, 1);
	return (s_new);
}

char		*ft_strtrim(char const *s)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (!s)
		return (ft_returnblank());
	if (!*s)
		return (ft_returnblank());
	while ((s[j] == ' ' || s[j] == '\n' || s[j] == '\t') && s[j] != '\0')
		j++;
	if (j == ft_strlen((char*)s))
		return (ft_returnblank());
	while (s[i] != '\0')
		i++;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t' || s[i] == '\0')
		i--;
	i++;
	return (ft_strsub(s, j, (i - j)));
}
