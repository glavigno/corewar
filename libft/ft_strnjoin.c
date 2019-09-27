/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/16 12:04:53 by hklein            #+#    #+#             */
/*   Updated: 2018/12/05 18:51:43 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnjoin(char const *s1, char const *s2, size_t n)
{
	char			*new_s;
	size_t			i;
	size_t			j;

	if (!s1 || !s2)
		return (NULL);
	if ((new_s = ft_strnew(n)) == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (i < ft_strlen((char*)s1) && j < n)
		new_s[j++] = s1[i++];
	i = 0;
	while (i < ft_strlen((char*)s2) && j < n)
		new_s[j++] = s2[i++];
	new_s[j] = '\0';
	return (new_s);
}
