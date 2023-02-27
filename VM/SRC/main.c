/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 09:24:01 by bkandemi          #+#    #+#             */
/*   Updated: 2023/02/19 12:56:27 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	init_vm(t_vm *vm)
{
	ft_bzero(&vm->args, sizeof(vm->args));
	ft_bzero(&vm->champs, sizeof(vm->champs));
	ft_bzero(&vm->carriages, sizeof(vm->carriages));
	vm->winner = 0;
	vm->cycles = 0;
	vm->cycles_to_die = CYCLE_TO_DIE;
	vm->last_player_alive = 0;
	vm->args.verbose = 0;
	vm->nb_of_live = 0;
	vm->checks = 0;
	vm->carriage_count = 0;
	vm->the_check_cycle = CYCLE_TO_DIE;
}

static void	verify_args(t_vm *vm)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		if (vm->args.numbers[i] > vm->args.player_count)
			error_exit("Wrong nbr for -n flag", vm);
		j = i + 1;
		while (j < 4)
		{
			if (vm->args.numbers[i] == vm->args.numbers[j]
				&& vm->args.numbers[i] != 0)
				error_exit("Two players have same number", vm);
			j++;
		}
		i++;
	}
}

void	parse_args(int argc, char **argv, t_vm *vm)
{
	if (argc == 1)
	{
		ft_putendl(USAGE);
		exit (1);
	}
	get_args(argc, argv, vm);
	verify_args(vm);
	set_player_order(vm);
	vm->carriage_count = vm->args.player_count;
}

int	main(int argc, char **argv)
{
	t_vm			vm;
	unsigned char	arena[MEM_SIZE];

	init_vm(&vm);
	parse_args(argc, argv, &vm);
	read_champs(&vm);
	place_champs(arena, &vm);
	init_carriages(&vm);
	the_cycle(&vm, arena);
	ok_exit(&vm);
	return (0);
}
