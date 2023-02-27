/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_add_sub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 16:02:55 by bkandemi          #+#    #+#             */
/*   Updated: 2023/02/19 12:56:31 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/* 04 */
int	op_add(t_vm *vm, unsigned char *arena, t_carriage *the_car)
{
	t_op_args	op_args;
	int			value1;
	int			value2;

	get_types_size(arena, the_car, &op_args);
	if (op_args.types[0] == T_REG && \
	op_args.types[1] == T_REG && op_args.types[2] == T_REG)
	{
		if (get_oparg_values(arena, the_car, &op_args))
		{
			value1 = the_car->registers[op_args.values[0] - 1];
			value2 = the_car->registers[op_args.values[1] - 1];
			the_car->registers[op_args.values[2] - 1] = value1 + value2;
			set_carry(the_car, value1 + value2);
			if (vm->args.verbose & 4)
			{
				ft_printf("P%5d | add r%d r%d r%d\n", the_car->id, \
				op_args.values[0], op_args.values[1], op_args.values[2]);
			}
		}
	}
	return (op_args.size[0] + op_args.size[1] + op_args.size[2] + 2);
}

/* 05 */
int	op_sub(t_vm *vm, unsigned char *arena, t_carriage *the_car)
{
	t_op_args	op_args;
	int			value1;
	int			value2;

	get_types_size(arena, the_car, &op_args);
	if (op_args.types[0] == T_REG && \
	op_args.types[1] == T_REG && op_args.types[2] == T_REG)
	{
		if (get_oparg_values(arena, the_car, &op_args))
		{
			value1 = the_car->registers[op_args.values[0] - 1];
			value2 = the_car->registers[op_args.values[1] - 1];
			the_car->registers[op_args.values[2] - 1] = value1 - value2;
			set_carry(the_car, value1 - value2);
			if (vm->args.verbose & 4)
				ft_printf("P%5d | sub r%d r%d r%d\n", the_car->id, \
					op_args.values[0], op_args.values[1], op_args.values[2]);
		}
	}
	return (op_args.size[0] + op_args.size[1] + op_args.size[2] + 2);
}
