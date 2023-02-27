/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 13:11:01 by ykot              #+#    #+#             */
/*   Updated: 2023/02/11 00:35:26 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	parse_reg(t_data *data, t_op_data *temp_op, int32_t arg_data, \
						char **line)
{
	int32_t	num;

	move_ptr(data, line, 1);
	num = ft_atoi(*line);
	temp_op->args[arg_data].data = num;
	while (**line >= '0' && **line <= '9')
		move_ptr(data, line, 1);
}

/* !!!! Improve !!!! */
static void	parse_ind(t_data *data, t_op_data *temp_op, int32_t arg_data, \
						char **line)
{
	int32_t	num;
	int32_t	i;

	if (is_nbr(*line))
	{
		num = atoi(*line);
		if (**line == '-')
			move_ptr(data, line, 1);
		while (**line >= '0' && **line <= '9')
			move_ptr(data, line, 1);
		temp_op->args[arg_data].data = num;
		return ;
	}
	move_ptr(data, line, 1);
	i = 0;
	while (is_char_in_str(*(*line + i), LABEL_CHARS))
		i++;
	temp_op->args[arg_data].label = ft_strsub(*line, 0, i);
	temp_op->args[arg_data].data = data->byte_pass;
	if (temp_op->args[arg_data].label == NULL)
		error(MALLOC_FAILED, data, NOPOS);
	move_ptr(data, line, i);
}

static void	parse_dir(t_data *data, t_op_data *temp_op, int32_t arg_data, \
						char **line)
{
	move_ptr(data, line, 1);
	parse_ind(data, temp_op, arg_data, line);
}

void	parse_token(t_data *data, t_op_data *temp_op, int32_t arg_data, \
						char **line)
{
	if (temp_op->args[arg_data].type_arg == T_REG)
		parse_reg(data, temp_op, arg_data, line);
	if (temp_op->args[arg_data].type_arg == T_DIR)
		parse_dir(data, temp_op, arg_data, line);
	if (temp_op->args[arg_data].type_arg == T_IND)
		parse_ind(data, temp_op, arg_data, line);
}
