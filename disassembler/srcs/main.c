/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <hklein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 10:11:30 by arumpler          #+#    #+#             */
/*   Updated: 2019/05/11 16:47:37 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disassembler.h"

int			check_file_extension(t_dis *dis, char *str)
{
	if (ft_strlen(str) < 4 || ft_strcmp(".cor", &str[ft_strlen(str) - 4]))
		return (ft_disp_error("Error: wrong extension file\n", 1));
	if (!(dis->new_filename = (char*)malloc(ft_strlen(str) + 3)))
		return (1);
	ft_strncpy(dis->new_filename, str, ft_strlen(str) - 4);
	ft_strcpy(dis->new_filename + ft_strlen(str) - 4, "_r.s");
	return (0);
}

void		write_file(int fd, t_dis *dis)
{
	t_buf *buf;

	buf = dis->bufs;
	while (buf)
	{
		write(fd, buf->str, ft_strlen(buf->str));
		buf = buf->next;
	}
}

int			main(int argc, char **argv)
{
	int		fd;
	t_dis	*dis;

	(void)argv;
	if (argc < 2)
		return (1);
	if (!(dis = init_dis()))
		return (free_all(dis, 1));
	if (check_file_extension(dis, argv[1]))
		return (free_all(dis, 1));
	if ((fd = open(argv[argc - 1], O_RDWR)) < 0)
		return (free_all(dis, 1));
	if (parser(fd, dis))
		return (free_all(dis, 1));
	close(fd);
	if ((fd = open(dis->new_filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR
					| S_IWUSR | S_IRGRP | S_IROTH)) == -1)
		return (free_all(dis, 1));
	write_file(fd, dis);
	close(fd);
	return (free_all(dis, 0));
}
