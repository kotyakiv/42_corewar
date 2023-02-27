/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 21:54:53 by bkandemi          #+#    #+#             */
/*   Updated: 2023/02/19 12:56:34 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/* 16 */
int	op_aff(t_vm *vm, unsigned char *arena, t_carriage *the_car)
{
	t_op_args	op_args;

	get_types_size(arena, the_car, &op_args);
	if (op_args.types[0] == T_REG && !op_args.types[1] && !op_args.types[2])
	{
		if (get_oparg_values(arena, the_car, &op_args))
		{
			if (vm->args.verbose & 1)
				ft_printf("Aff: %c\n", \
				(char)the_car->registers[op_args.values[0] - 1]);
		}
	}
	return (op_args.size[0] + 2);
}
