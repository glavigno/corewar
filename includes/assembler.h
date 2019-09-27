/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assembler.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <hklein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 14:24:02 by glavigno          #+#    #+#             */
/*   Updated: 2019/05/11 15:54:47 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASSEMBLER_H
# define ASSEMBLER_H

# include "../libft/libft.h"
# include "../op/op.h"
# include <stdio.h>

# define LABEL			16
# define INSTRUCTION	32
# define REGISTER 		1
# define INDIRECT 		4
# define DIRECT 		2
# define DIRECT_LABEL	10
# define INDIRECT_LABEL	12

typedef char			t_token_type;

typedef struct			s_token
{
	t_token_type		type;
	char				*value;
	size_t				position;
	struct s_token		*next;
}						t_tokens;

typedef struct			s_asm
{
	t_tokens			*tokens;
	t_header			*header;
	int					comment;
	int					name;
	unsigned char		*bytes;
	int					instruction_pos;
	unsigned int		champion_size;
	char				*new_filename;
}						t_asm;

t_asm					*init_asm();
int						lexer(int fd, t_asm *asmb);
int						ft_command(char *line, t_asm *asmb, int is_name);
int						ft_label(char *line, t_asm *asmb);
int						ft_instruction(char *line, t_asm *asmb);

int						parser(t_asm *asmb);
int						ft_checks(t_asm *asmb);
int						parse_instruction(t_tokens **buf, t_asm *asmb);
t_op					*identify_op(char *instruction_name);
unsigned char			enc_byte(t_tokens *token);
int						get_label_position(t_tokens *token, char *value);

int						find_first(char *str, char c, char d);
int						add_token(t_token_type type, char *value, t_asm *asmb);

int						is_label(char *line);
int						is_instruction(char *str, t_asm *asmb);
int						is_indirect_label(char *line);
int						is_argument(char *str, t_asm *asmb);
int						is_not_indirect_argument(char *str, t_asm *asmb);

int						check_arg(t_op *op, t_tokens *buf);
int						bytes_to_write(t_tokens *buf, t_op *op);
void					write_arg(t_asm *asmb, t_tokens *buf, t_op *op);
void					write_label_arg(t_asm *asmb, t_tokens *buf, t_op *op);
void					write_bytes(t_asm *asmb, t_tokens **buf, t_op *op);
unsigned int			big_endian(unsigned int x);

int						free_all(t_asm *asmb, int ret);
int						free_tab(char **tab);

#endif
