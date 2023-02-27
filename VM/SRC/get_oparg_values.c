/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_oparg_values.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:00:27 by bkandemi          #+#    #+#             */
/*   Updated: 2023/02/19 12:56:20 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	get_values(int value, t_op_args *op_args, int i)
{
	if (op_args->types[i] == T_REG)
	{
		if (value < 1 || value > 16)
			return (0);
		op_args->values[i] = (int8_t)value;
	}
	if (op_args->types[i] == T_DIR)
	{
		if (op_args->size_tdir == 2)
			op_args->values[i] = (int16_t)value;
		else
			op_args->values[i] = (int32_t)value;
	}
	if (op_args->types[i] == T_IND)
		op_args->values[i] = (int16_t)value;
	return (1);
}

int	get_oparg_values(unsigned char *arena,
					t_carriage *the_car,
					t_op_args *op_args)
{
	int		i;
	int		start;
	int		value;

	start = (the_car->position + 2) % MEM_SIZE;
	i = 0;
	while (i < op_args->arg_count)
	{
		value = bytes_to_int2(arena, start, op_args->size[i]);
		if (!get_values(value, op_args, i))
			return (0);
		start = (start + op_args->size[i]) % MEM_SIZE;
		i++;
	}
	return (1);
}
