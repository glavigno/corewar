/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 11:54:28 by hklein            #+#    #+#             */
/*   Updated: 2019/03/13 17:22:43 by glavigno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		get_return(char **line)
{
	if ((**line))
		return (1);
	else if (!(*line))
		return (-1);
	else
	{
		ft_strdel(line);
		return (0);
	}
}

static int		join_line(char **line, char *tmp)
{
	(*line) = ft_strnjoinf((*line), tmp, 1,
			(ft_strchr(tmp, '\n') - tmp));
	if (!*line)
		return (1);
	else
		return (0);
}

int				get_next_line(const int fd, char **line)
{
	static char		fdstock[OPEN_MAX][BUFF_SIZE + 1];
	char			*tmp;
	int				ret;

	tmp = fdstock[fd];
	if (!line || fd < 0 || BUFF_SIZE < 1 || read(fd, NULL, 0) < 0)
		return (-1);
	if (!((*line) = ft_strnew(0)))
		return (-1);
	while (1)
	{
		if (ft_strchr(tmp, '\n'))
		{
			if (join_line(line, tmp))
				return (-1);
			ft_strncpy(tmp, &tmp[ft_strchr(tmp, '\n') - tmp + 1],
					BUFF_SIZE - (ft_strchr(tmp, '\n') - tmp));
			return (1);
		}
		(*line) = ft_strnjoinf((*line), tmp, 1, BUFF_SIZE);
		ret = read(fd, fdstock[fd], BUFF_SIZE);
		tmp[ret] = '\0';
		if (ret == 0 || !*line)
			return (get_return(line));
	}
}
