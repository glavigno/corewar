/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_dis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <hklein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:25:31 by arumpler          #+#    #+#             */
/*   Updated: 2019/05/11 16:47:21 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disassembler.h"

int			new_buf_by_value(char *value, t_dis *dis)
{
	t_buf	*buf;
	t_buf	*tmp;
	char	*str;

	buf = dis->bufs;
	while (buf && buf->next)
		buf = buf->next;
	if (!(tmp = (t_buf*)malloc(sizeof(t_buf))))
		return (1);
	ft_memset(tmp, 0, sizeof(t_buf));
	if (!(str = ft_strnew(ft_strlen(value) + 1)))
	{
		free(tmp);
		return (1);
	}
	ft_strcpy(str, value);
	tmp->str = str;
	buf->next = tmp;
	return (0);
}

t_buf		*new_buf_by_size(int size, t_dis *dis)
{
	t_buf	*buf;
	t_buf	*tmp;
	char	*str;

	buf = dis->bufs;
	while (buf && buf->next)
		buf = buf->next;
	if (!(tmp = (t_buf*)malloc(sizeof(t_buf))))
		return (NULL);
	ft_memset(tmp, 0, sizeof(t_buf));
	if (!(str = ft_strnew(size)))
	{
		free(tmp);
		return (NULL);
	}
	tmp->str = str;
	buf->next = tmp;
	return (tmp);
}

t_dis		*init_dis(void)
{
	t_dis	*tmp;
	t_buf	*buf;
	char	*str;

	if (!(tmp = (t_dis*)malloc(sizeof(t_dis))))
		return (NULL);
	ft_memset(tmp, 0, sizeof(t_dis));
	if (!(buf = (t_buf*)malloc(sizeof(t_buf))))
	{
		free(tmp);
		return (NULL);
	}
	ft_memset(tmp, 0, sizeof(t_buf));
	if (!(str = ft_strnew(0)))
	{
		free(tmp);
		free(buf);
		return (NULL);
	}
	buf->str = str;
	buf->next = NULL;
	tmp->bufs = buf;
	return (tmp);
}
