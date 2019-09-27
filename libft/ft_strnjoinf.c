/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoinf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 18:39:44 by hklein            #+#    #+#             */
/*   Updated: 2018/12/05 19:45:31 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnjoinf(char *s1, char *s2, size_t rm, size_t len)
{
	char			*new_s;

	if ((int)rm < 0 || (int)rm > 3)
		return (NULL);
	if (!s1 || !s2)
		return (NULL);
	if ((new_s = ft_strnew(ft_strlen(s1) + ft_strlen(s2))) == NULL)
		return (NULL);
	ft_strcpy(new_s, s1);
	ft_strncat(new_s, s2, len);
	if (rm == 1 || rm == 3)
		ft_strdel(&s1);
	if (rm == 2 || rm == 3)
		ft_strdel(&s2);
	return (new_s);
}
