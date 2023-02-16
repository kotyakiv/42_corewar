/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 15:56:38 by ykot              #+#    #+#             */
/*   Updated: 2023/02/16 11:22:42 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	continue_parse_name(t_data *data, char *line)
{
	u_int32_t	i;
	u_int32_t	len;

	ft_strncpy(data->header.prog_name + data->flags.read_bytes, "\n", 1);
	data->flags.read_bytes++;
	i = 0;
	while (line[i] && line[i] != '"')
		++i;
	len = data->flags.read_bytes;
	if (PROG_NAME_LENGTH < len + i)
		error(NAME_TOO_LONG, data, POS);
	ft_strncpy(data->header.prog_name + data->flags.read_bytes, line, i);
	if (line[i] == '\0')
		data->flags.read_bytes += i;
	if (line[i] == '"')
	{
		data->flags.name = TRUE;
		extra_characters(data, line + i + 1);
		data->flags.continue_read = 0;
		data->flags.read_bytes = 0;
	}
}

void	continue_parse_comment(t_data *data, char *line)
{
	u_int32_t	i;
	u_int32_t	len;

	ft_strncpy(data->header.comment + data->flags.read_bytes, "\n", 1);
	data->flags.read_bytes++;
	i = 0;
	while (line[i] && line[i] != '"')
		++i;
	len = data->flags.read_bytes;
	if (COMMENT_LENGTH < len + i)
		error(COMMENT_TOO_LONG, data, POS);
	ft_strncpy(data->header.comment + data->flags.read_bytes, line, i);
	if (line[i] == '\0')
		data->flags.read_bytes += i;
	if (line[i] == '"')
	{
		data->flags.comment = TRUE;
		extra_characters(data, line + i + 1);
		data->flags.continue_read = 0;
		data->flags.read_bytes = 0;
	}
}

static void	parse_comment(t_data *data, char *line, u_int32_t start_pos)
{
	u_int32_t	i;

	i = 0;
	move_ptr(data, &line, start_pos);
	ignore_whitespaces(data, &line);
	if (*line != '"')
		error(MISSING_QUOTE, data, POS);
	move_ptr(data, &line, 1);
	while (line[i] && line[i] != '"')
		++i;
	if (COMMENT_LENGTH < i)
		error(NAME_TOO_LONG, data, POS);
	ft_strncpy(data->header.comment, line, i);
	if (line[i] == '"')
	{
		data->flags.comment = TRUE;
		extra_characters(data, line + i + 1);
		return ;
	}
	data->flags.read_bytes += i;
	data->flags.continue_read = 2;
}

static void	parse_name(t_data *data, char *line, u_int32_t start_pos)
{
	u_int32_t	i;

	i = 0;
	move_ptr(data, &line, start_pos);
	ignore_whitespaces(data, &line);
	if (*line != '"')
		error(MISSING_QUOTE, data, POS);
	move_ptr(data, &line, 1);
	while (line[i] && line[i] != '"')
		++i;
	if (PROG_NAME_LENGTH < i)
		error(NAME_TOO_LONG, data, POS);
	ft_strncpy(data->header.prog_name, line, i);
	if (line[i] == '"')
	{
		data->flags.name = TRUE;
		extra_characters(data, line + i + 1);
		return ;
	}
	data->flags.read_bytes += i;
	data->flags.continue_read = 1;
}

void	parse_header(t_data *data, char *line)
{
	if (ft_strncmp(line, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)) == 0)
	{
		if (data->flags.name)
			error(NAME_ALREADY_EXISTS, data, POS);
		parse_name(data, line, ft_strlen(NAME_CMD_STRING));
	}	
	else if (ft_strncmp(line, COMMENT_CMD_STRING, \
				ft_strlen(COMMENT_CMD_STRING)) == 0)
	{
		if (data->flags.comment)
			error(COMMENT_ALREADY_EXISTS, data, POS);
		parse_comment(data, line, ft_strlen(COMMENT_CMD_STRING));
	}
	else if (!data->flags.name)
		error(STILL_NO_NAME, data, NOPOS);
	else if (!data->flags.comment)
		error(STILL_NO_COMMENT, data, NOPOS);
}
