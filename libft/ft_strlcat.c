/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 20:14:09 by hklein            #+#    #+#             */
/*   Updated: 2018/11/15 12:13:30 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dstlen;
	size_t	i;

	dstlen = ft_strlen((char*)dst);
	if (dstsize < dstlen)
		return (ft_strlen((char*)src) + dstsize);
	i = 0;
	while (dstlen < (dstsize - 1) && src[i])
		dst[dstlen++] = src[i++];
	dst[dstlen] = '\0';
	while (src[i++])
		++dstlen;
	return (dstlen);
}
