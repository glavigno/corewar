# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hklein <hklein@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/12 11:29:30 by glavigno          #+#    #+#              #
#    Updated: 2019/05/11 15:51:48 by hklein           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar

# *************************************************************** FILES && LIB #

SRC_FILES = cw_load_players_procs.c cw_exec.c cw_generate_players.c \
			cw_generate_players2.c cw_init_struct.c cw_instance_fight.c \
			cw_main.c cw_parse_opt.c cw_print_write_utils.c ft_live.c \
			../../op/op.c cw_save_cycle.c cw_free_struct.c ft_ld.c ft_ldi.c \
			ft_st.c ft_aff.c ft_op.c ft_zjmp.c ft_fork.c ../../visu/srcs/cw_vs.c\
			../../visu/srcs/cw_vs_utils.c cw_opt_show_usage.c \
			../../visu/srcs/cw_vs_utils_2.c \
			../../visu/srcs/cw_update_cw_values.c \
			../../visu/srcs/cw_update_side_infos_key_press.c\
			cw_instance_fight_2.c

OBJ_FILES = $(SRC_FILES:.c=.o)
LIB_NAME = libft.a

# ************************************************************** COLORS DEFINE #

GR = \033[7;49;32m
BL= \033[7;49;34m
YL = \033[7;49;33m
RD = \033[7;49;31m
UGR = \033[4;49;32m
UBL = \033[4;49;34m
UYL = \033[4;49;33m
URD = \033[4;49;31m
E = \033[0m

# ************************************************ FILES, HEADERS && LIB PATHS #

SRC_PATH = srcs
OBJ_PATH = obj
LIB_PATH = ../libft
HDR_PATH = ../includes

SRC = $(addprefix $(SRC_PATH)/,$(SRC_FILES))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_FILES))
LIB = $(addprefix $(LIB_PATH)/,$(LIB_NAME))

# ***************************************************** C COMPILATION && FLAGS #

CC = gcc
CFLAGS = -Werror -Wall -Wextra

# ************************************************************* MAKEFILE RULES #

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $@ $(OBJ) $(LIB) -lncurses
	@echo "$(GR)   SUCCESS  > $(E)   $(UGR)$(NAME) executable is ready$(E)"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(HDR_PATH)
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) $(CFLAGS) -c $< -o $@ -I ../includes 
	@echo "$(BL)   COMPILE  > $(E)   $(UBL)$<$(E)"

clean:
	@rm -f $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	@echo "$(YL)   CLEAN    > $(E)   $(UYL).o files deleted$(E)"
	@echo "$(YL)   CLEAN    > $(E)   $(UYL)clean completed$(E)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RD)   FCLEAN   > $(E)   $(URD)$(NAME) executable deleted$(E)"
	@echo "$(RD)   FCLEAN   > $(E)   $(URD)fclean completed$(E)"

re: fclean all

.PHONY: all clean fclean re
