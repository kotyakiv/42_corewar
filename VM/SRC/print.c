/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 13:37:08 by bkandemi          #+#    #+#             */
/*   Updated: 2023/02/19 12:57:03 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	print_player_order(t_args args)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		ft_printf("%d-%s\n", args.numbers[i], args.filenames[i]);
		i++;
	}
	ft_printf("\nplayer count: %d\n\n", args.player_count);
}

void	print_carriages(t_vm vm)
{
	t_dblist	*cars;
	t_carriage	*the_car;

	cars = vm.carriages.head;
	while (cars != NULL)
	{
		the_car = cars->content;
		ft_printf("car id: %d pos: %d\n carry: %d reg[0]: %d last_live: \
		%d\n rem_cycles:%d opcode:%#x\n\n",
			the_car->id, the_car->position, the_car->carry,
			the_car->registers[0], the_car->last_live, \
			the_car->remaining_cycles, the_car->opcode);
		cars = cars->next;
	}
}
