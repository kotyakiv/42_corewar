/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 21:56:51 by bkandemi          #+#    #+#             */
/*   Updated: 2023/02/19 12:56:57 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/* 09 */
int	op_zjmp(t_vm *vm, unsigned char *arena, t_carriage *the_car)
{
	int16_t	position;

	position = (int16_t)bytes_to_int2(arena, the_car->position + 1, 2);
	if (vm->args.verbose & 4)
	{
		ft_printf("P%5d | zjmp %hd ", the_car->id, position);
		if (the_car->carry)
			ft_printf("OK\n");
		else
			ft_printf("FAILED\n");
	}
	if (the_car->carry)
	{
		the_car->position = \
		new_position(the_car->position, (position % IDX_MOD));
		return (0);
	}
	else
		return (1 + IND_SIZE);
}
