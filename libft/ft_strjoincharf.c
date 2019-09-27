/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinchar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 15:24:47 by hklein            #+#    #+#             */
/*   Updated: 2018/12/21 13:43:30 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoincharf(char *s1, char c)
{
	size_t	len;

	len = ft_strlen(s1);
	s1 = ft_str_realloc(s1, (len + 1));
	s1[len] = c;
	return (s1);
}
