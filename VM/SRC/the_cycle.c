/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_cycle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 15:39:43 by bkandemi          #+#    #+#             */
/*   Updated: 2023/02/19 12:57:16 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	dump(unsigned char *arena, int row_len)
{
	int	i;
	int	row;

	i = 0;
	row = 0;
	ft_printf("0x0000 :");
	while (i < MEM_SIZE)
	{
		if (i != 0 && i % row_len == 0)
		{
			row += row_len;
			ft_printf("\n%#06x :", row);
		}
		if (arena[i] != 0)
			ft_printf(" %02x", arena[i]);
		else
			ft_printf(" %02x", arena[i]);
		i++;
	}
	write(1, "\n", 1);
}

/*
	* Increment the cycle counter
	* Run carriages(execute the opcode or update the carriage struct)
	* Do the check-up
*/
void	the_cycle(t_vm *vm, unsigned char *arena)
{
	while (vm->carriages.size != 0)
	{
		if (vm->args.dump_flag == TRUE && vm->cycles == vm->args.dump_cycle)
		{
			dump(arena, vm->args.row_len);
			return ;
		}
		vm->cycles++;
		if (vm->args.verbose & 2)
			ft_printf("It is now cycle %d\n", vm->cycles);
		run_carriages(vm, arena);
		if (vm->cycles == vm->the_check_cycle || vm->cycles_to_die <= 0)
			check(vm);
	}
}
