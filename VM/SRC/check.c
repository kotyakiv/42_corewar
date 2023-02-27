/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 14:31:35 by bkandemi          #+#    #+#             */
/*   Updated: 2023/02/19 12:56:03 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	show_death(t_vm *vm, t_carriage *the_car)
{
	if (vm->args.verbose & 8)
	{
		ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n", \
			the_car->id, \
			vm->cycles - the_car->last_live_cycle, \
			vm->cycles_to_die);
	}
}

static void	set_winner(t_vm *vm)
{
	if (vm->last_player_alive)
		vm->winner = vm->last_player_alive;
	else
		vm->winner = vm->champs[vm->args.player_count - 1].id;
}

static void	the_check_cycle(t_vm *vm)
{
	t_dblist	*cars;
	t_carriage	*the_car;
	size_t		elem_count;
	t_dblist	*next_car;

	cars = vm->carriages.head;
	elem_count = 0;
	while (cars)
	{
		the_car = cars->content;
		next_car = cars->next;
		if (the_car->last_live == FALSE || vm->cycles_to_die <= 0)
		{
			show_death(vm, the_car);
			ft_dynlstdelelem(&vm->carriages, elem_count, del_fn);
		}
		else
		{
			the_car->last_live = FALSE;
			elem_count++;
		}
		cars = next_car;
	}
}

/* 
	* Delete dead carriage
	* Reduce cycles_to_die value
	* If there are no carriages anymore, announce the winner
*/
void	check(t_vm *vm)
{
	vm->checks++;
	the_check_cycle(vm);
	if (vm->nb_of_live >= NBR_LIVE || vm->checks >= MAX_CHECKS)
	{
		vm->cycles_to_die -= CYCLE_DELTA;
		if (vm->args.verbose & 2)
			ft_printf("Cycle to die is now %d\n", vm->cycles_to_die);
		vm->checks = 0;
	}
	set_winner(vm);
	if (vm->carriages.size == 0)
		ft_printf("Contestant %d, \"%s\", has won !\n",
			vm->winner, vm->champs[vm->winner - 1].name);
	vm->nb_of_live = 0;
	vm->the_check_cycle += vm->cycles_to_die;
}
