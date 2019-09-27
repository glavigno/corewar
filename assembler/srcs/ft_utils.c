/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <hklein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 12:06:05 by glavigno          #+#    #+#             */
/*   Updated: 2019/05/11 16:41:55 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int		is_label(char *line)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (!ft_strchr(LABEL_CHARS, line[i]))
		{
			if (line[i] == LABEL_CHAR)
				return (1);
			return (0);
		}
		i++;
	}
	return (0);
}

int		is_instruction(char *str, t_asm *asmb)
{
	int i;

	i = REG_NUMBER;
	while (--i >= 0)
	{
		if (ft_strncmp(g_op[i].name, str, ft_strlen(g_op[i].name)) == 0)
		{
			add_token(INSTRUCTION, g_op[i].name, asmb);
			return (ft_strlen(g_op[i].name));
		}
	}
	return (0);
}

int		is_indirect_label(char *line)
{
	int i;

	i = -1;
	while (line[++i])
		if (!ft_strchr(LABEL_CHARS, line[i]))
			return (0);
	return (1);
}

int		is_not_indirect_argument(char *str, t_asm *asmb)
{
	if (str[0] == DIRECT_CHAR)
	{
		if (str[1] == LABEL_CHAR)
			add_token(DIRECT_LABEL, str + 2, asmb);
		else if (ft_is_str_digit(str + 1)
				|| (str[1] == '-' && ft_is_str_digit(str + 2)))
			add_token(DIRECT, str + 1, asmb);
		else
			return (ft_disp_error("Error: invalid argument\n", 0));
	}
	else if (str[0] == 'r')
	{
		if (ft_is_str_digit(str + 1) && ft_atoi(str + 1) > 0
				&& ft_atoi(str + 1) <= REG_NUMBER)
			add_token(REGISTER, str + 1, asmb);
		else
			return (ft_disp_error("Error: invalid argument\n", 0));
	}
	return (1);
}

int		is_argument(char *str, t_asm *asmb)
{
	if (str[0] == DIRECT_CHAR || str[0] == 'r')
	{
		if (!is_not_indirect_argument(str, asmb))
			return (0);
	}
	else if (str[0] == LABEL_CHAR && is_indirect_label(str + 1))
		add_token(INDIRECT_LABEL, str + 1, asmb);
	else if (ft_is_str_digit(str)
			|| (str[0] == '-' && ft_is_str_digit(str + 1)))
		add_token(INDIRECT, str, asmb);
	else
		return (ft_disp_error("Error: invalid argument\n", 0));
	return (1);
}
