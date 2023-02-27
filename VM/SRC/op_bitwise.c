/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_bitwise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 16:30:41 by bkandemi          #+#    #+#             */
/*   Updated: 2023/02/19 12:56:39 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	set_first_val(unsigned char *arena,
						t_carriage *the_car,
						t_op_args *op_args,
						int *ret1)
{
	int	position;

	if (op_args->types[0] == T_REG)
		*ret1 = the_car->registers[op_args->values[0] - 1];
	if (op_args->types[0] == T_IND)
	{
		position = t_ind_position(the_car, op_args->values[0]);
		*ret1 = (int32_t)bytes_to_int2(arena, position, 4);
	}
}

static void	set_second_value(unsigned char *arena,
							t_carriage *the_car,
							t_op_args *op_args,
							int *ret2)
{
	int	position;

	if (op_args->types[1] == T_REG)
		*ret2 = the_car->registers[op_args->values[1] - 1];
	if (op_args->types[1] == T_IND)
	{
		position = t_ind_position(the_car, op_args->values[1]);
		*ret2 = (int32_t)bytes_to_int2(arena, position, 4);
	}
}

/* 06 */
int	op_and(t_vm *vm, unsigned char *arena, t_carriage *the_car)
{
	t_op_args	op_args;
	int			ret1;
	int			ret2;

	get_types_size(arena, the_car, &op_args);
	if (op_args.types[2] == T_REG && op_args.types[1] && op_args.types[0])
	{
		if (get_oparg_values(arena, the_car, &op_args))
		{
			ret1 = op_args.values[0];
			ret2 = op_args.values[1];
			set_first_val(arena, the_car, &op_args, &ret1);
			set_second_value(arena, the_car, &op_args, &ret2);
			set_carry(the_car, (ret1 & ret2));
			the_car->registers[op_args.values[2] - 1] = (ret1 & ret2);
			if (vm->args.verbose & 4)
				ft_printf("P%5d | and %d %d r%d\n", \
				the_car->id, ret1, ret2, op_args.values[2]);
		}
	}
	return (op_args.size[0] + op_args.size[1] + op_args.size[2] + 2);
}

/* 07 */
int	op_or(t_vm *vm, unsigned char *arena, t_carriage *the_car)
{
	t_op_args	op_args;
	int			ret1;
	int			ret2;

	get_types_size(arena, the_car, &op_args);
	if (op_args.types[2] == T_REG && op_args.types[1] && op_args.types[0])
	{
		if (get_oparg_values(arena, the_car, &op_args))
		{
			ret1 = op_args.values[0];
			ret2 = op_args.values[1];
			set_first_val(arena, the_car, &op_args, &ret1);
			set_second_value(arena, the_car, &op_args, &ret2);
			set_carry(the_car, (ret1 | ret2));
			the_car->registers[op_args.values[2] - 1] = (ret1 | ret2);
			if (vm->args.verbose & 4)
				ft_printf("P%5d | or %d %d r%d\n", \
				the_car->id, ret1, ret2, op_args.values[2]);
		}
	}
	return (op_args.size[0] + op_args.size[1] + op_args.size[2] + 2);
}

/* 08 */
int	op_xor(t_vm *vm, unsigned char *arena, t_carriage *the_car)
{
	t_op_args	op_args;
	int			ret1;
	int			ret2;

	get_types_size(arena, the_car, &op_args);
	if (op_args.types[2] == T_REG && op_args.types[1] && op_args.types[0])
	{
		if (get_oparg_values(arena, the_car, &op_args))
		{
			ret1 = op_args.values[0];
			ret2 = op_args.values[1];
			set_first_val(arena, the_car, &op_args, &ret1);
			set_second_value(arena, the_car, &op_args, &ret2);
			set_carry(the_car, (ret1 ^ ret2));
			the_car->registers[op_args.values[2] - 1] = (ret1 ^ ret2);
			if (vm->args.verbose & 4)
				ft_printf("P%5d | xor %d %d r%d\n", \
				the_car->id, ret1, ret2, op_args.values[2]);
		}
	}
	return (op_args.size[0] + op_args.size[1] + op_args.size[2] + 2);
}
