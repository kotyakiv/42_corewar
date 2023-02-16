/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 15:06:45 by ykot              #+#    #+#             */
/*   Updated: 2023/02/14 16:21:13 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/* update position of the reading pointer */
static void	pos_new_line(t_data *data)
{
	data->pos.r++;
	data->pos.c = 0;
}

static void	parse_line(t_data *data, char *line)
{
	if (data->flags.continue_read)
	{
		if (data->flags.continue_read == 1)
			continue_parse_name(data, line);
		if (data->flags.continue_read == 2)
			continue_parse_comment(data, line);
		return ;
	}
	ignore_whitespaces(data, &line);
	if (is_empty_line(line) || is_comment_line(line))
		return ;
	else if (!data->flags.continue_read && \
		(!data->flags.name || !data->flags.comment))
		parse_header(data, line);
	else if (is_label(line))
		parse_label(data, line);
	else if (is_op(line) != ISNOTOP)
		tokenization(data, line);
	else
		error(WRONG_INPUT, data, POS);
}

/* check if there is a new line in EOF */
static int	check_new_line(t_data *data, const char *file_name)
{
	int16_t	fd;
	char	buff[2];
	int		i;
	int		offset;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		error(CANT_OPEN_FILE, data, NOPOS);
	i = -1;
	lseek(fd, i, SEEK_END);
	read(fd, buff, 1);
	while (*buff == ' ' || *buff == '\t')
	{
		offset = lseek(fd, i, SEEK_END);
		read(fd, buff, 1);
		if (offset == 0)
			break ;
		--i;
	}
	close(fd);
	if (*buff == '\n')
		return (TRUE);
	return (FALSE);
}

/* open and read from file line by line */
void	parsing(t_data *data, const char *file_name)
{
	int16_t	fd;
	char	*line;
	int8_t	gnl;

	if (check_new_line(data, file_name) == 0)
		error(NO_NEW_LINE, data, NOPOS);
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		error(CANT_OPEN_FILE, data, NOPOS);
	line = NULL;
	while (TRUE)
	{
		ft_strdel(&line);
		pos_new_line(data);
		gnl = get_next_line(fd, &line);
		if (check_gnl(data, gnl, &line) == 0)
		{
			close(fd);
			return ;
		}
		parse_line(data, line);
	}
}
