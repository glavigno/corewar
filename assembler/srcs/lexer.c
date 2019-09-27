/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hklein <hklein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:28:28 by arumpler          #+#    #+#             */
/*   Updated: 2019/05/11 16:42:43 by hklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "assembler.h"

int		find_first(char *str, char c, char d)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c || str[i] == d)
			return (i);
		i++;
	}
	return (-1);
}

char	*clean_line(char *raw_line)
{
	char	*tmp;
	char	*tmp2;
	int		index;

	index = find_first(raw_line, COMMENT_CHAR, ';');
	if (!(tmp = ft_strsub(raw_line, 0, index >= 0
					? index : ft_strlen(raw_line))))
		return (NULL);
	if (!(tmp2 = ft_strtrim(tmp)))
	{
		free(tmp);
		return (NULL);
	}
	free(tmp);
	index = 0;
	while (tmp2[index])
	{
		if (tmp2[index] >= 9 && tmp2[index] <= 13)
			tmp2[index] = 32;
		index++;
	}
	return (tmp2);
}

int		ft_tokenize(char *raw_line, t_asm *asmb)
{
	int		ret;
	char	*line;

	ret = 0;
	if (!(line = clean_line(raw_line)))
		return (1);
	if (!line[0])
	{
		free(line);
		return (0);
	}
	if (!ft_strncmp(line, COMMENT_CMD_STRING, 8))
		ret = ft_command(line + 8, asmb, 0);
	else if (!ft_strncmp(line, NAME_CMD_STRING, 5))
		ret = ft_command(line + 5, asmb, 1);
	else if (is_label(line))
		ret = ft_label(line, asmb);
	else
		ret = ft_instruction(line, asmb);
	free(line);
	return (ret);
}

int		free_lines(char *first, char *second)
{
	free(first);
	first = NULL;
	free(second);
	second = NULL;
	return (1);
}

int		lexer(int fd, t_asm *asmb)
{
	char *line;
	char *trim_line;

	while (get_next_line(fd, &line) > 0)
	{
		if (!(trim_line = ft_strtrim(line)))
		{
			free(line);
			return (1);
		}
		if (trim_line[0])
			if (ft_tokenize(line, asmb))
				return (free_lines(trim_line, line));
		free_lines(trim_line, line);
	}
	if (asmb->name != 1)
		return (ft_disp_error("Error: missing name\n", 1));
	if (asmb->comment != 1)
		return (ft_disp_error("Error: missing comment\n", 1));
	return (0);
}
