# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: glavigno <glavigno@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/28 19:46:56 by glavigno          #+#    #+#              #
#    Updated: 2019/06/03 11:44:39 by glavigno         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = compile

$(NAME): libft asm corewar

all: $(NAME)

libft:
	@make -C libft

asm:
	@make -C assembler

corewar:
	@make -C virtual_machine

disassembler:
	@make -C disassembler

norme:
	@norminette libft
	@norminette assembler/src
	@norminette assembler/include
	@norminette virtual_machine/srcs
	@norminette includes
	@norminette disassembler/src
	@norminette disassembler/include
	@norminette visu/srcs
	@norminette op

clean:
	@make clean -C libft
	@make clean -C assembler && make clean -C virtual_machine

fclean:
	@make fclean -C libft
	@make fclean -C assembler && make fclean -C virtual_machine

re: fclean all

.PHONY: all libft asm corewar disassembler norme clean fclean re
