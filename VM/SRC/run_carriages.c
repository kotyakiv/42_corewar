/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_carriages.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 14:25:21 by bkandemi          #+#    #+#             */
/*   Updated: 2023/02/19 12:57:10 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	get_remaining_cycles(int opcode)
{
	if (opcode == 1 || opcode == 4 || opcode == 5 || opcode == 13)
		return (10);
	else if (opcode == 2 || opcode == 3)
		return (5);
	else if (opcode == 6 || opcode == 7 || opcode == 8)
		return (6);
	else if (opcode == 9)
		return (20);
	else if (opcode == 10 || opcode == 11)
		return (25);
	else if (opcode == 12)
		return (800);
	else if (opcode == 14)
		return (50);
	else if (opcode == 15)
		return (1000);
	else if (opcode == 16)
		return (2);
	else
		return (1);
}

static const t_dispacht_op_codes	g_opcode_dispacht [16] = {
	op_live,
	op_ld,
	op_st,
	op_add,
	op_sub,
	op_and,
	op_or,
	op_xor,
	op_zjmp,
	op_ldi,
	op_sti,
	op_fork,
	op_lld,
	op_lldi,
	op_lfork,
	op_aff,
};

static int	execute_opcode(t_vm *vm, unsigned char *arena, t_carriage *the_car)
{
	if (the_car->opcode <= 0 || the_car->opcode > 16)
		return (1);
	return (g_opcode_dispacht[the_car->opcode - 1](vm, arena, the_car));
}

static void	execute_and_move_carriage(t_vm *vm, \
							unsigned char *arena, \
							t_carriage *the_car)
{
	int	set_pos;
	int	i;

	set_pos = execute_opcode(vm, arena, the_car);
	if (set_pos > 1 && (vm->args.verbose & 16))
	{
		ft_printf("ADV %d (0x%.4x -> 0x%.4x) ", \
		set_pos, the_car->position, the_car->position + set_pos);
		i = 0;
		while (i < set_pos)
		{
			ft_printf("%.2x ", arena[(the_car->position + i) % MEM_SIZE]);
			i++;
		}
		ft_putchar('\n');
	}
	the_car->position = new_position(the_car->position, set_pos);
	the_car->remaining_cycles--;
}

/*
	* Set the new opcode if it is time
	* Reduce the remaining_cycles
	* Execute the opcode and update the position of the carriage
*/
void	run_carriages(t_vm *vm, unsigned char *arena)
{
	t_dblist	*cars;
	t_carriage	*the_car;

	cars = vm->carriages.head;
	while (cars != NULL)
	{
		the_car = cars->content;
		if (the_car->remaining_cycles < 0)
		{
			the_car->opcode = arena[the_car->position];
			the_car->remaining_cycles = get_remaining_cycles(the_car->opcode);
		}
		if (the_car->remaining_cycles > 0)
			the_car->remaining_cycles--;
		if (the_car->remaining_cycles == 0)
			execute_and_move_carriage(vm, arena, the_car);
		cars = cars->next;
	}
}
