/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 15:14:28 by bkandemi          #+#    #+#             */
/*   Updated: 2023/02/19 12:56:51 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/* 13 */
int	op_lld(t_vm *vm, unsigned char *arena, t_carriage *the_car)
{
	t_op_args	op_args;
	int			position;
	int			ret;

	get_types_size(arena, the_car, &op_args);
	if (op_args.types[0] != T_REG
		&& op_args.types[1] == T_REG && !op_args.types[2])
	{
		get_oparg_values(arena, the_car, &op_args);
		ret = op_args.values[0];
		if (op_args.types[0] == T_IND)
		{
			position = t_ind_position(the_car, op_args.values[0]);
			ret = (int16_t)bytes_to_int2(arena, position, 2);
		}
		the_car->registers[op_args.values[1] - 1] = ret;
		set_carry(the_car, ret);
		if (vm->args.verbose & 4)
			ft_printf("P%5d | lld %d r%d\n", \
			the_car->id, ret, op_args.values[1]);
	}
	return (op_args.size[0] + op_args.size[1] + 2);
}

static void	print_lldi(t_carriage *the_car,
					t_op_args *op_args,
					int32_t ret,
					int change)
{
	ft_printf("P%5d | lldi %d %d r%d\n", \
	the_car->id, ret, op_args->values[1], op_args->values[2]);
	ft_printf("       | -> load from %d + %d = %d (with pc %d)\n", \
	ret, op_args->values[1], change, the_car->position + change);
}

static void	set_lldi_values(t_op_args *op_args,
							unsigned char *arena,
							t_carriage *the_car,
							t_vm *vm)
{
	int			change;
	int			position;
	int32_t		ret;

	ret = op_args->values[0];
	if (op_args->types[0] == T_REG)
		ret = the_car->registers[op_args->values[0] - 1];
	if (op_args->types[0] == T_IND)
	{
		position = t_ind_position(the_car, op_args->values[0]);
		ret = (int32_t)bytes_to_int2(arena, position, 4);
	}
	if (op_args->types[1] == T_REG)
		op_args->values[1] = the_car->registers[op_args->values[1] - 1];
	change = ret + op_args->values[1];
	position = new_position(the_car->position, change);
	the_car->registers[op_args->values[2] - 1] = \
	bytes_to_int2(arena, position, 4);
	set_carry(the_car, the_car->registers[op_args->values[2] - 1]);
	if (vm->args.verbose & 4)
		print_lldi(the_car, op_args, ret, change);
}

/* 14 */
int	op_lldi(t_vm *vm, unsigned char *arena, t_carriage *the_car)
{
	t_op_args	op_args;

	get_types_size(arena, the_car, &op_args);
	{
		if (op_args.types[0] && \
		op_args.types[1] != T_IND && op_args.types[2] == T_REG)
		{
			if (get_oparg_values(arena, the_car, &op_args))
				set_lldi_values(&op_args, arena, the_car, vm);
		}
	}
	return (op_args.size[0] + op_args.size[1] + op_args.size[2] + 2);
}
