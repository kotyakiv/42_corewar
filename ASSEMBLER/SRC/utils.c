/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 23:12:01 by ykot              #+#    #+#             */
/*   Updated: 2023/01/31 16:53:38 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/* Check result of reading the line */
int8_t	check_gnl(t_data *data, int8_t gnl, char **line)
{
	if (gnl == 1)
		return (1);
	if (gnl == 0)
		return (0);
	ft_strdel(line);
	error(GNL_FAILED, data, POS);
	return (-1);
}

void	ignore_whitespaces(t_data *data, char **str)
{
	while (**str == ' ' || **str == '\t')
	{
		if (**str == '\t')
			data->pos.c += 4;
		else
			data->pos.c++;
		(*str)++;
	}
}

u_int8_t	is_empty_line(char *line)
{
	return (ft_strlen(line) == 0);
}

u_int8_t	is_comment_line(char *line)
{
	return (*line == COMMENT_CHAR);
}

t_bool	is_nbr(const char *str)
{
	u_int32_t	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if ((i == 1 && str[0] != '-') || i > 1)
		return (1);
	return (0);
}
