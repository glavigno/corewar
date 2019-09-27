/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 20:23:42 by hklein            #+#    #+#             */
/*   Updated: 2018/11/22 12:22:34 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int		i;
	int		j;

	i = 0;
	if (!*needle)
		return (&((char*)haystack)[i]);
	while (haystack[i] != '\0')
	{
		if (needle[0] == haystack[i])
		{
			j = 0;
			while (needle[j] == haystack[i + j] && needle[j] != '\0')
				j++;
			if (needle[j] == '\0')
				return (&((char*)haystack)[i]);
		}
		i++;
	}
	return (0);
}
