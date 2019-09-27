/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 15:33:05 by hklein            #+#    #+#             */
/*   Updated: 2018/11/27 18:35:24 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinf(char *s1, char *s2, size_t rm)
{
	char			*new_s;
	unsigned int	i;
	unsigned int	j;

	if ((int)rm < 0 || (int)rm > 3)
		return (NULL);
	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	if ((new_s = ft_strnew(i + j)) == NULL)
		return (NULL);
	ft_strcpy(new_s, s1);
	ft_strcat(new_s, s2);
	if (rm == 1 || rm == 3)
		ft_strdel(&s1);
	if (rm == 2 || rm == 3)
		ft_strdel(&s2);
	return (new_s);
}
