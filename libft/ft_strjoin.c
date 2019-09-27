/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 20:08:16 by hklein            #+#    #+#             */
/*   Updated: 2019/02/18 15:49:42 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*new_s;
	unsigned int	i;
	unsigned int	j;

	if (!s1 || !s2)
		return (NULL);
	if ((new_s = ft_strnew(ft_strlen((char*)s1)
		+ ft_strlen((char*)s2))) == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (i < ft_strlen((char*)s1))
		new_s[j++] = s1[i++];
	i = 0;
	while (i < ft_strlen((char*)s2))
		new_s[j++] = s2[i++];
	return (new_s);
}
