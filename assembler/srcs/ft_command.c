/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <hklein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:13:19 by arumpler          #+#    #+#             */
/*   Updated: 2019/05/11 16:40:34 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int			count_quotes(char *arg)
{
	int quotes;

	quotes = 0;
	while (*arg)
	{
		if (*arg == '"')
			quotes++;
		arg++;
	}
	return (quotes == 2 ? 0 : 1);
}

void		fill_header(char *line, int is_name, t_asm *asmb)
{
	if (is_name)
	{
		asmb->name++;
		ft_strncpy(asmb->header->prog_name, line, ft_strlen(line) - 1);
	}
	else
	{
		asmb->comment++;
		ft_strncpy(asmb->header->comment, line, ft_strlen(line) - 1);
	}
}

int			disp_error_free(char *str, int ret, void *to_free)
{
	free(to_free);
	return (ft_disp_error(str, ret));
}

int			ft_command(char *line, t_asm *asmb, int is_name)
{
	char *trim_line;

	if (!(trim_line = ft_strtrim(line)))
		return (1);
	if (trim_line[0] != '"' || trim_line[ft_strlen(trim_line) - 1] != '"'
		|| count_quotes(trim_line))
		return (disp_error_free(
					"Error: no double quotes around command's argument\n",
					1, trim_line));
		if (is_name && ft_strlen(trim_line) - 2 > PROG_NAME_LENGTH)
		return (disp_error_free(
					"Error: the name is too long\n", 1, trim_line));
		if (!is_name && ft_strlen(trim_line) - 2 > COMMENT_LENGTH)
		return (disp_error_free(
					"Error: the comment is too long\n", 1, trim_line));
		if ((is_name && asmb->name) || (!is_name && asmb->comment))
		return (disp_error_free(
					"Error: there must be only one name and comment\n",
					1, trim_line));
		fill_header(trim_line + 1, is_name, asmb);
	free(trim_line);
	return (0);
}
