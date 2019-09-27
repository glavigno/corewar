/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disassembler.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <hklein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 14:24:02 by glavigno          #+#    #+#             */
/*   Updated: 2019/05/11 15:59:00 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISASSEMBLER_H
# define DISASSEMBLER_H

# include "../libft/libft.h"
# include "../op/op.h"

# define LABEL			16
# define INSTRUCTION	32
# define REGISTER 		1
# define INDIRECT 		4
# define DIRECT 		2
# define DIRECT_LABEL	10
# define INDIRECT_LABEL	12

typedef struct			s_buf
{
	char				*str;
	struct s_buf		*next;
}						t_buf;

typedef struct			s_dis
{
	t_buf				*bufs;
	char				*new_filename;
}						t_dis;

t_dis					*init_dis(void);
int						free_all(t_dis *dis, int ret);
int						parser(int fd, t_dis *dis);
t_buf					*new_buf_by_size(int size, t_dis *dis);
int						new_buf_by_value(char *str, t_dis *dis);
char					*get_value(int fd, int size);

#endif
