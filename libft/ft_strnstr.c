/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 20:23:33 by hklein            #+#    #+#             */
/*   Updated: 2018/11/15 10:48:14 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!*needle)
		return (&((char*)haystack)[i]);
	while (haystack[i] != '\0' && i < len)
	{
		if (needle[0] == haystack[i])
		{
			j = 0;
			while (needle[j] == haystack[i + j] && needle[j] != '\0' && i < len)
			{
				j++;
				if (needle[j] == '\0')
					return (&((char*)haystack)[i]);
				if (i + j == len)
					return (NULL);
			}
		}
		i++;
	}
	return (0);
}
