/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:10:58 by ykot              #+#    #+#             */
/*   Updated: 2023/02/14 15:49:12 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

u_int8_t	is_op(char *line)
{
	u_int8_t	i;
	u_int32_t	j;

	j = 0;
	while (line[j] && line[j] != '\t' && line[j] != ' ' && \
			line[j] != '%' && line[j] != ':' && line[j] != LABEL_CHAR)
		++j;
	if (line[j] == '\0' || line[j] == LABEL_CHAR)
		return (ISNOTOP);
	i = 0;
	while (i < 16)
	{
		if (ft_strncmp(line, g_optab[i].name, j) == 0)
			return (i + 1);
		++i;
	}
	return (ISNOTOP);
}

static void	is_right_type(t_data *data, t_op_data *temp_op, int8_t arg_num)
{
	if (temp_op->args[arg_num].type_arg & \
		g_optab[temp_op->num_op - 1].typeofarg[arg_num])
		return ;
	error(WRONG_ARG_TYPE, data, POS);
}

void	read_tokens(t_data *data, char **tokens, t_op_data *temp_op)
{
	u_int32_t	i;
	char		*temp;

	if (data->flags.sep + 1 != g_optab[temp_op->num_op - 1].num_arg)
		error(WRONG_NB_OF_ARGS, data, POS);
	i = 0;
	while (i < g_optab[temp_op->num_op - 1].num_arg)
	{
		if (!tokens[i])
			error(EMP_ARG, data, POS);
		temp = tokens[i];
		ignore_whitespaces(data, &temp);
		temp_op->args[i].type_arg = check_op_args(data, temp);
		is_right_type(data, temp_op, i);
		parse_token(data, temp_op, i, &temp);
		ignore_whitespaces(data, &temp);
		if (*temp != '\0' && i != g_optab[temp_op->num_op - 1].num_arg - 1)
			error(EXTRA_CHARS, data, POS);
		if (i == g_optab[temp_op->num_op - 1].num_arg - 1)
			extra_characters(data, temp);
		++i;
	}
}
