/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 15:49:59 by bkandemi          #+#    #+#             */
/*   Updated: 2023/02/19 12:56:54 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/* 03 */
int	op_st(t_vm *vm, unsigned char *arena, t_carriage *the_car)
{
	t_op_args	op_args;
	int			position;

	get_types_size(arena, the_car, &op_args);
	if (op_args.types[0] == T_REG && \
	(op_args.types[1] == T_REG || op_args.types[1] == T_IND))
	{
		if (get_oparg_values(arena, the_car, &op_args))
		{
			if (op_args.types[1] == T_REG)
				the_car->registers[op_args.values[1] - 1] = \
				the_car->registers[op_args.values[0] - 1];
			else
			{
				position = t_ind_position(the_car, op_args.values[1]);
				write_int_to_arena(arena, position, \
				(uint32_t)the_car->registers[op_args.values[0] - 1]);
			}
			if (vm->args.verbose & 4)
				ft_printf("P%5d | st r%d %d\n", \
				the_car->id, op_args.values[0], op_args.values[1]);
		}
	}
	return (op_args.size[0] + op_args.size[1] + 2);
}

static void	set_sti_values(t_vm *vm,
							unsigned char *arena,
							t_carriage *the_car,
							t_op_args *op_args)
{
	int			mod;
	int			position;
	int32_t		ret;

	ret = op_args->values[1];
	if (op_args->types[1] == T_REG)
		ret = the_car->registers[op_args->values[1] - 1];
	if (op_args->types[1] == T_IND)
	{
		position = t_ind_position(the_car, op_args->values[1]);
		ret = (int32_t)bytes_to_int2(arena, position, 4);
	}
	if (op_args->types[2] == T_REG)
		op_args->values[2] = the_car->registers[op_args->values[2] - 1];
	mod = (ret + op_args->values[2]) % IDX_MOD;
	position = new_position(the_car->position, mod);
	write_int_to_arena(arena, position, \
	(uint32_t)the_car->registers[op_args->values[0] - 1]);
	if (vm->args.verbose & 4)
	{
		ft_printf("P%5d | sti r%d %d %d\n", \
		the_car->id, op_args->values[0], ret, op_args->values[2]);
		ft_printf("       | -> store to %d + %d = %d \
(with pc and mod %d)\n", ret, op_args->values[2], \
		ret + op_args->values[2], the_car->position + mod);
	}
}

/* 11 */
int	op_sti(t_vm *vm, unsigned char *arena, t_carriage *the_car)
{
	t_op_args	op_args;

	get_types_size(arena, the_car, &op_args);
	if (op_args.types[0] && op_args.types[1] && op_args.types[2] \
	&& op_args.types[2] != T_IND && op_args.types[0] == T_REG)
	{
		if (get_oparg_values(arena, the_car, &op_args))
			set_sti_values(vm, arena, the_car, &op_args);
	}
	return (op_args.size[0] + op_args.size[1] + op_args.size[2] + 2);
}
