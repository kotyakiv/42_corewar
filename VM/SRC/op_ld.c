/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:17:52 by bkandemi          #+#    #+#             */
/*   Updated: 2023/02/19 12:56:45 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	print_ld(t_vm *vm,
					t_carriage *the_car,
					t_op_args op_args,
					int32_t ret)
{
	if (vm->args.verbose & 4)
		ft_printf("P%5d | ld %d r%d\n", \
		the_car->id, ret, op_args.values[1]);
}

/* 02 */
int	op_ld(t_vm *vm, unsigned char *arena, t_carriage *the_car)
{
	t_op_args	op_args;
	int32_t		ret;
	int			position;

	get_types_size(arena, the_car, &op_args);
	if (!op_args.types[2]
		&& op_args.types[0] != T_REG && op_args.types[1] == T_REG)
	{
		if (get_oparg_values(arena, the_car, &op_args))
		{
			if (op_args.types[0] == T_IND)
			{
				position = t_ind_position(the_car, op_args.values[0]);
				ret = (int32_t)bytes_to_int2(arena, position, 4);
			}
			else
				ret = op_args.values[0];
			the_car->registers[op_args.values[1] -1] = ret;
			set_carry(the_car, ret);
			print_ld(vm, the_car, op_args, ret);
		}
	}
	return (op_args.size[0] + op_args.size[1] + 2);
}

static void	set_ldi_values(t_vm *vm,
						unsigned char *arena,
						t_carriage *the_car,
						t_op_args *op_args)
{
	int			mod;
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
	mod = (ret + op_args->values[1]) % IDX_MOD;
	position = new_position(the_car->position, mod);
	the_car->registers[op_args->values[2] - 1] = \
	bytes_to_int2(arena, position, 4);
	if (vm->args.verbose & 4)
	{
		ft_printf("P%5d | ldi %d %d r%d\n", the_car->id, ret, \
		op_args->values[1], op_args->values[2]);
		ft_printf("       | -> load from %d + %d = %d \
(with pc and mod %d)\n", ret, op_args->values[1], ret + \
		op_args->values[1], the_car->position + mod);
	}
}

/*10 */
int	op_ldi(t_vm *vm, unsigned char *arena, t_carriage *the_car)
{
	t_op_args	op_args;

	get_types_size(arena, the_car, &op_args);
	if (op_args.types[0] && op_args.types[1] && op_args.types[2] && \
	op_args.types[1] != T_IND && op_args.types[2] == T_REG)
	{
		if (get_oparg_values(arena, the_car, &op_args))
			set_ldi_values(vm, arena, the_car, &op_args);
	}
	return (op_args.size[0] + op_args.size[1] + op_args.size[2] + 2);
}
