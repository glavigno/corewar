/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <hklein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:43:41 by arumpler          #+#    #+#             */
/*   Updated: 2019/05/11 16:42:59 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int			check_file_extension(t_asm *asmb, char *str)
{
	if (ft_strlen(str) < 3 || ft_strcmp(".s", &str[ft_strlen(str) - 2]))
		return (ft_disp_error("Error: wrong extension file\n", 1));
	if (!(asmb->new_filename = (char*)malloc(ft_strlen(str) + 3)))
		return (1);
	ft_strncpy(asmb->new_filename, str, ft_strlen(str) - 1);
	ft_strcpy(asmb->new_filename + ft_strlen(str) - 1, "cor");
	return (0);
}

int			main(int argc, char **argv)
{
	int		fd;
	t_asm	*asmb;

	if (!(asmb = init_asm()) || argc < 2)
		return (free_all(asmb, 1));
	if (check_file_extension(asmb, argv[argc - 1]))
		return (free_all(asmb, 1));
	if ((fd = open(argv[argc - 1], O_RDWR)) < 0)
		return (free_all(asmb, 1));
	if (lexer(fd, asmb))
		return (free_all(asmb, 1));
	close(fd);
	if (parser(asmb))
		return (free_all(asmb, 1));
	if ((fd = open(asmb->new_filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR
					| S_IWUSR | S_IRGRP | S_IROTH)) == -1)
		return (free_all(asmb, ft_disp_error("error: open\n", 1)));
	write(fd, asmb->header, sizeof(t_header));
	write(fd, asmb->bytes, asmb->champion_size);
	close(fd);
	return (free_all(asmb, 0));
}
