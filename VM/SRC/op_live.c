/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:16:04 by bkandemi          #+#    #+#             */
/*   Updated: 2023/02/19 12:56:48 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/* 01 */
int	op_live(t_vm *vm, unsigned char *arena, t_carriage *the_car)
{
	int	player;

	player = bytes_to_int2(arena, (the_car->position + 1) % MEM_SIZE, DIR_SIZE);
	if (vm->args.verbose & 4)
		ft_printf("P%5d | live %d\n", the_car->id, player);
	if (player < 0)
	{
		player = player * -1;
		if (player > 0 && player <= vm->args.player_count)
		{
			vm->last_player_alive = player;
			if (vm->args.verbose & 1)
				ft_printf("A process shows that player %d (%s) is alive\n", \
					vm->last_player_alive, \
					vm->champs[vm->last_player_alive - 1].name);
		}
	}
	vm->nb_of_live++;
	the_car->last_live_cycle = vm->cycles;
	the_car->last_live = TRUE;
	return (DIR_SIZE + 1);
}
