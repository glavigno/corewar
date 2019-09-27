/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/13 16:42:55 by hklein            #+#    #+#             */
/*   Updated: 2019/02/09 14:41:53 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft.h"
# include <stdarg.h>
# define BUF_SIZE 1024

typedef struct			s_stock
{
	char				end_str[BUF_SIZE];
	size_t				flsh;
	size_t				s_i;
	int					op_sp;
	int					op_pl;
	int					op_ha;
	int					op_ze;
	int					op_mi;
	char				t;
	size_t				w;
	size_t				p;
	int					pr_x;
	int					si;
	int					offset;
	va_list				ap;
	char				*var_s;
	wchar_t				*var_s_u;
	char				var_c;
	wchar_t				var_c_u;
	long long			var_i;
	size_t				var_f_p;
	unsigned long long	var_ui;
	long double			var_f;
	size_t				len_res;
	size_t				len_end;
	int					col;
	int					*n;
}						t_stock;

int						ft_printf(const char *format, ...);
t_stock					*init_stock(void);
void					reset_stock(t_stock *s);
int						check_option(char *format_mod, t_stock *s);
int						set_res(t_stock *s);
int						get_var(t_stock *s);
size_t					wr_str(char c, size_t len, size_t ind, t_stock *s);
size_t					ft_lltoa_base_pf(long long v, int b, t_stock *s);
size_t					ft_utoa_base_pf(unsigned long long v,
		unsigned int b, t_stock *s);
size_t					ft_unsigned_len(unsigned long long x,
		unsigned int b, char type);
void					check_max_wp(t_stock *s);
int						format_res_num(t_stock *s);
int						format_res_str_c_mod(t_stock *s);
size_t					format_str_c_mod(t_stock *s);
size_t					s_ver(t_stock *stock, int v);
size_t					concat_var(t_stock *s);
void					format_floats(t_stock *s);
int						format_unicode(t_stock *s);
int						format_color(char *format_mod, t_stock *s);

#endif
