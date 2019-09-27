/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cw.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <hklein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 17:09:10 by hklein            #+#    #+#             */
/*   Updated: 2019/05/09 17:04:21 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CW_H
# define CW_H

# include "../op/op.h"
# include "../libft/libft.h"
# include <ncurses.h>
# include <string.h>

# define MIN_WIN_W_ 250
# define MIN_WIN_H_ 68
# define VS_BORDER_COLOR_ 1
# define VS_MAX_SPEED_ 100000
# define VS_MIN_SPEED_ 100
# define VS_INIT_SPEED_ 20000
# define VS_DECAL_ 3
# define VS_WITDH_BD_ 41
# define COLOR_LIGHTGREEN 14
# define COLOR_LIGHTBLUE 15
# define COLOR_LIGHTRED 16
# define COLOR_LIGHTYELLOW 17

typedef struct s_cw	t_cw;

typedef struct		s_player
{
	int				nb_player;
	char			*file;
	int				fd;
	unsigned char	name[128];
	unsigned char	comment[2048];
	unsigned char	exec_size[4];
	int				exec_size_int;
	int				last_live_cycle;
	int				current_ctd_lives;
	int				color;
	struct s_player *next;
}					t_player;

typedef struct		s_proc
{
	int				regs[REG_NUMBER];
	char			cf;
	unsigned int	pc;
	short			alive;
	int				instr_exec_cycle;
	t_op			*instruction;
	int				args_size[3];
	t_player		*parent_player;
	struct s_cw		*cw;
	struct s_proc	*next;
	int				id;
}					t_proc;

typedef struct		s_game
{
	int				cycle;
	int				nb_process;
	int				nb_live;
	int				ctd_checkups;
	int				ctd;
	int				checks;
	int				max_checkups;
	t_player		*winner;
}					t_game;

typedef struct		s_vs
{
	int				row;
	int				col;
	int				starty;
	int				startx;
	int				speed;
	int				pause;
	WINDOW			*logo_win;
	WINDOW			*live_bd_current;
	WINDOW			*live_bd_prec;
	WINDOW			*main_win;
	WINDOW			*live_win;
	WINDOW			*grid_win;
	t_player		*live_signal[5];
}					t_vs;

struct				s_cw
{
	int				opt_dump;
	int				opt_dump_type;
	int				opt_a;
	int				opt_v;
	int				arg;
	int				nb_players;
	t_proc			*procs;
	t_player		*players;
	unsigned char	arena[MEM_SIZE][2];
	t_game			*game;
	t_vs			*vs;
	t_cw			*saved_cycles_prec;
	t_cw			*saved_cycles_next;
	int				nb_proc;
};

t_cw				*init_cw(void);
t_proc				*init_proc(t_cw *cw);
t_player			*init_player(void);
t_game				*init_game(t_cw *cw);

int					generate_players(t_cw *cw, char **av);
int					parse_opt(t_cw *cw, char **av);
int					check_nbs_players(int nb_players, t_cw *cw);
int					emulate_fight(t_cw *cw);
int					dump_arena(t_cw *cw);
void				dump_memory(unsigned char (*mem)[2], size_t len, int mode);
int					load_proc(t_player *tmp_player, t_cw *cw);
void				fill_arena
						(t_cw *cw, unsigned char *tmp, int pos, size_t len);
int					execute_instr(t_proc *proc);
void				ft_live(t_proc *proc);
void				ft_ld(t_proc *proc, int lg);
void				ft_ldi(t_proc *proc, int lg);
void				ft_st(t_proc *proc);
void				ft_sti(t_proc *proc);
void				end_instance_opt(t_cw *cw);
void				ft_op(t_proc *proc, int opcode);
void				ft_aff(t_proc *proc);
void				ft_zjmp(t_proc *proc);
int					ft_fork(t_proc *proc, int lg);

int					instance_fight(t_cw *cw);
int					size_of_instruction(t_proc *proc);
int					load_players_procs(t_cw *cw);
int					get_value_from_memory
						(unsigned int pos, int size, t_proc *proc);
int					create_proc(t_player *tmp_player, t_cw *cw);
t_cw				*save_cycle(t_cw *cw);
void				free_procs(t_cw *cw);
void				free_players(t_cw *cw);
int					count_procs(t_cw *cw);
void				free_cw_list(t_cw *cw);
int					cw_vs(t_vs *vs, t_cw *cw, int screen);
t_vs				*start_vs(t_cw *cw);
void				init_cw_colors(void);
WINDOW				*create_newwin(int height, int width, int sty, int stx);
void				draw_plain_border(t_vs *vs, WINDOW *win, int color);
void				draw_plain_line(t_vs *vs, int height, int len);
void				introduce_contestants(t_cw *cw);
t_vs				*init_vs(void);
void				draw_plain_col(t_vs *vs, int size, int x, int color);
void				draw_logo(t_vs *vs);
void				write_alive(t_proc *tmp_proc, t_player *tmp_player);
void				write_live_bd(t_vs *vs, t_cw *cw, int offset);
int					idx_mod(int a);
void				identify_instruction(t_cw *cw, t_proc *tmp_proc);
int					update_cw_values(t_vs *vs, t_cw **cw_beg);
int					deal_key_press(t_vs *vs, t_cw **cw_beg);
void				update_side_infos(t_vs *vs, t_cw *cw);
void				check_procs_lives(t_cw *cw);
void				reset_player_ctd_lives(t_cw *cw);
int					check_magic_nb(t_player *tmp_player);

#endif
