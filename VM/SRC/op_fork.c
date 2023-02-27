/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 16:07:20 by bkandemi          #+#    #+#             */
/*   Updated: 2023/02/19 12:56:42 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static t_carriage	*copy_car(t_vm *vm, t_carriage *the_car, int16_t value)
{
	t_carriage	*new;
	int			reg_index;

	new = (t_carriage *)ft_memalloc(sizeof(*new));
	if (!new)
		error_exit("Memory allocation", vm);
	new->id = ++vm->carriage_count;
	new->position = t_ind_position(the_car, value);
	new->remaining_cycles = -1;
	new->carry = the_car->carry;
	new->last_live = the_car->last_live;
	new->last_live_cycle = the_car->last_live_cycle;
	reg_index = 0;
	while (reg_index < REG_NUMBER)
	{
		new->registers[reg_index] = the_car->registers[reg_index];
		reg_index++;
	}
	return (new);
}

/* 12 */
int	op_fork(t_vm *vm, unsigned char *arena, t_carriage *the_car)
{
	t_carriage	*new;
	int16_t		value;
	int16_t		temp_value;

	value = (int16_t)bytes_to_int2(arena, the_car->position + 1, 2);
	new = copy_car(vm, the_car, value);
	if (vm->args.verbose & 4)
	{
		temp_value = value;
		if (temp_value < 0)
		{
			temp_value = (-temp_value) % IDX_MOD;
			temp_value = -temp_value;
			ft_printf("P%5d | fork %d (%d)\n", the_car->id, value, \
			(the_car->position + temp_value));
		}
		else
			ft_printf("P%5d | fork %d (%d)\n", the_car->id, \
			value, new->position);
	}
	if (!add_carriage(new, &vm->carriages))
		error_exit("Memory allocation", vm);
	return (1 + IND_SIZE);
}

/* 15 */
int	op_lfork(t_vm *vm, unsigned char *arena, t_carriage *the_car)
{
	t_carriage	*new;
	int16_t		value;

	value = (int16_t)bytes_to_int2(arena, the_car->position + 1, 2);
	new = copy_car(vm, the_car, value);
	if (vm->args.verbose & 4)
		ft_printf("P%5d | lfork %d (%d)\n", the_car->id, value, \
		(the_car->position + value));
	if (!add_carriage(new, &vm->carriages))
		error_exit("Memory allocation", vm);
	return (1 + IND_SIZE);
}
